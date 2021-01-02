#include "render_thread.h"

#include <QOpenGLFunctions>
#include <QGuiApplication>
#include <QDebug>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

RenderThread::RenderThread(const QSize& size):
    surface(nullptr)
    , context(nullptr)
    , _renderFbo(nullptr)
    , _displayFbo(nullptr)
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
    bgfxInit.type = bgfx::RendererType::Direct3D9;
    bgfxInit.resolution.width = _size.width();
    bgfxInit.resolution.height = _size.height();
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

    bool callback =  bgfx::init(bgfxInit);

//    bgfx::setViewClear(0
//                       , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
//                       , 0x303030ff
//                       , 1.0f
//                       , 0
//                       );

    qDebug() << "bgfx init2" << callback;
}

void RenderThread::renderNext()
{
    context->makeCurrent(surface);

    if (!bgfx::isValid(m_backBuffer)) {
        //        QOpenGLFramebufferObjectFormat format;
        //        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        bgfxInit();
        m_backBuffer = bgfx::createTexture2D(_size.width(), _size.height(), false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT, NULL);
        m_depthBuffer = bgfx::createTexture2D(_size.width(), _size.height(), false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT, NULL);
//        _bgfxRenderFbo = bgfx::createFrameBuffer(_size.width(), _size.height(), bgfx::TextureFormat::BGRA8);
//        _bgfxDisplayFbo = bgfx::createFrameBuffer(_size.width(), _size.height(), bgfx::TextureFormat::BGRA8);

        //        _renderFbo = new QOpenGLFramebufferObject(_size, format);
        //        _displayFbo = new QOpenGLFramebufferObject(_size, format);
    }
//    bgfx::setViewFrameBuffer(0, _bgfxRenderFbo);
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

//     m_texture = (void*)bgfx::getInternal(m_backBuffer);

     QSGTexture* qsgtexture{nullptr};

//     bgfx::TextureHandle
//     qsgtexture = (void*)bgfx::getTexture(m_backBuffer);

//     emit textureReady(qsgtexture, _size);

//    bgfx::setViewClear(0
//                       , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
//                       , 0x303030ff
//                       , 1.0f
//                       , 0
//                       );

//    bgfx::reset(_size.width(), _size.height(), BGFX_RESET_VSYNC);

//    bgfx::setViewRect(0, 100, 100, uint16_t(200), uint16_t(200));
//    bgfx::setViewClear(0,
//                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
//                       0x443355FF, 1.0f, 0);
//    bgfx::touch(0);
//    bgfx::frame();

//    m_texture = (void*)bgfx::getInternal(m_backBuffer);

    //    _renderFbo->bind();

    //    bgfx::reset(640, 480, BGFX_RESET_VSYNC);

    //    bgfx::setViewRect(0, 0, 0, uint16_t(200), uint16_t(200));
    //    bgfx::setViewClear(0,
    //                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
    //                       0x443355FF, 1.0f, 0);
    //    bgfx::touch(0);
    //    bgfx::frame();
    //    context->functions()->glViewport(0, 0, _size.width(), _size.height());

    //    context->functions()->glClearColor(1.0, 0, 0, 0);
    //    context->functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    //render
    //    context->functions()->glFlush();

    //    _renderFbo->bindDefault();
//    qSwap(_bgfxRenderFbo, _bgfxDisplayFbo);

//    emit textureReady(_bgfxRenderFbo, _size);
}

void RenderThread::shutDown()
{
//    bgfx::destroy(_bgfxRenderFbo);
//    bgfx::destroy(_bgfxDisplayFbo);

    bgfx::shutdown();

    context->makeCurrent(surface);
    delete _renderFbo;
    delete _displayFbo;
    context->doneCurrent();
    delete context;

    surface->deleteLater();

    //    exit();
    moveToThread(QGuiApplication::instance()->thread());
}
