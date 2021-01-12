#include "bgfx_item2.h"

#include <QQuickWindow>

int WIDTH = 640;
int HEIGHT = 480;

BgfxItem2::BgfxItem2() : _isBgfxInit(false)
{
    startTimer(500);
}

void BgfxItem2::bgfxInit()
{
    bgfx::PlatformData pd;
    pd.ndt = nullptr;
    pd.nwh = reinterpret_cast<void*>(window()->winId());
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

    qDebug() << "bgfx init2" << callback;
}

void BgfxItem2::timerEvent(QTimerEvent *event)
{
    render.render();
//    if (!_isBgfxInit) {
//        bgfxInit();
//        _isBgfxInit = true;
//    }

//    bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC);

//    bgfx::setViewRect(0, 100, 100, uint16_t(800), uint16_t(800));
//    bgfx::setViewClear(0,
//                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
//                       0x443355FF, 1.0f, 0);
//    bgfx::touch(0);
//    bgfx::frame();

//    bool isSave = window()->grabWindow().save("test.png");

//    qDebug() << "save image" << isSave;
//    bgfx::shutdown();
}
