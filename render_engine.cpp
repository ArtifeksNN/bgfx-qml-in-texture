#include "render_engine.h"

QQuickRenderControl *RenderEngine::createRenderControl()
{
    return ( m_renderControl = new QQuickRenderControl );
}

RenderEngine::RenderEngine() :
    QQuickWindow( createRenderControl()),
    m_offscreenSurface(new QOffscreenSurface())
{

}

void RenderEngine::init()
{
    bgfx::PlatformData pd;
    pd.ndt = nullptr;
    pd.nwh = reinterpret_cast<void*>(m_offscreenSurface->nativeHandle());
    pd.context      =  nullptr;
    pd.backBuffer   = nullptr;
    pd.backBufferDS = nullptr;
    bgfx::setPlatformData(pd);
    bgfx::renderFrame();

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count;
    bgfxInit.resolution.width = 640;
    bgfxInit.resolution.height = 480;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

    bool callback =  bgfx::init(bgfxInit);

    bgfx::setViewClear(0
                       , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
                       , 0x303030ff
                       , 1.0f
                       , 0
                       );

    qDebug() << "bgfx init" << callback;
}

void RenderEngine::render()
{
    if (!_isBgfxInit) {
        init();
        _isBgfxInit = true;
    }

    bgfx::reset(640, 480, BGFX_RESET_VSYNC);

    bgfx::setViewRect(0, 100, 100, uint16_t(200), uint16_t(200));
    bgfx::setViewClear(0,
                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                       0x443355FF, 1.0f, 0);
    bgfx::touch(0);
    bgfx::frame();

//    bool status = this->grabWindow().save("render_test0.png");
//    qDebug() << "save image" << status;
}

