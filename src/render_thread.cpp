#include "render_thread.h"

#include <QOpenGLFunctions>
#include <QGuiApplication>
#include <QDebug>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

RenderThread::RenderThread(const QSize& size):
    surface(nullptr)
    , context(nullptr)
    , _size(size)
{
}

void RenderThread::bgfxInit()
{
    bgfx::PlatformData pd;
    pd.ndt = nullptr;
    pd.nwh = nullptr;
    pd.context      =  nullptr;
    pd.backBuffer   = nullptr;
    pd.backBufferDS = nullptr;
    bgfx::setPlatformData(pd);
    bgfx::renderFrame();

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::OpenGL;
    bgfxInit.resolution.width = _size.width();
    bgfxInit.resolution.height = _size.height();
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

    bool callback =  bgfx::init(bgfxInit);

    qDebug() << "bgfx init2" << callback;
}

void RenderThread::renderNext()
{
    context->makeCurrent(surface);

    if (!bgfx::isValid(m_backBuffer)) {
        qDebug() << "check valid buffer";
        bgfxInit();
        m_backBuffer = bgfx::createTexture2D(_size.width(), _size.height(), false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT, NULL);
        m_depthBuffer = bgfx::createTexture2D(_size.width(), _size.height(), false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT, NULL);
    }
     bgfx::frame();

     std::array<bgfx::Attachment, 2> m_attachments{};
     auto &[colorAttachment, depthAttachment] = m_attachments;
     colorAttachment.init(m_backBuffer, bgfx::Access::Write, 0);
     depthAttachment.init(m_depthBuffer, bgfx::Access::Write, 0);

     if(bgfx::isValid(m_offscreenFB))
     {
         bgfx::destroy(m_offscreenFB);
     }
     m_offscreenFB = bgfx::createFrameBuffer(m_attachments.size(), m_attachments.data(), false);

     bgfx::setViewFrameBuffer(m_viewId, m_offscreenFB);

     bgfx::setViewRect(m_viewId, 0, 0, _size.width(), _size.height());
     bgfx::setViewClear(0,
                        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                        0x443355FF, 1.0f, 0);

     bgfx::touch(0);
     bgfx::frame();
     int textureID = bgfx::getInternal(m_backBuffer);

     emit textureReady(textureID, _size);
}

void RenderThread::shutDown()
{
    bgfx::shutdown();

    context->makeCurrent(surface);
    context->doneCurrent();
    delete context;

    surface->deleteLater();

    exit();
    moveToThread(QGuiApplication::instance()->thread());
}
