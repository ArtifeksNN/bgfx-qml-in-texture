#include "bgfx_item.h"

#include "render_thread.h"
#include "texture_node.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>


BgfxItem::BgfxItem() : _renderThread(nullptr), _isBgfxInit(false)
{
    setFlag(ItemHasContents, true);
    _renderThread = new RenderThread(QSize(512, 512));
}

void BgfxItem::bgfxInit()
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

    qDebug() << "bgfx init" << callback;
}

void BgfxItem::ready()
{
    _renderThread->surface = new QOffscreenSurface();
    _renderThread->surface->setFormat(_renderThread->context->format());
    _renderThread->surface->create();

//    if (!_isBgfxInit) {
//        bgfxInit();
//        _isBgfxInit = true;
//    }

//    bgfx::reset(640, 480, BGFX_RESET_VSYNC);

//    bgfx::setViewRect(0, 100, 100, uint16_t(200), uint16_t(200));
//    bgfx::setViewClear(0,
//                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
//                       0x443355FF, 1.0f, 0);
//    bgfx::touch(0);
//    bgfx::frame();

    _renderThread->moveToThread(_renderThread);

    connect(window(), &QQuickWindow::sceneGraphInvalidated,
            _renderThread, &RenderThread::shutDown, Qt::QueuedConnection);

    _renderThread->start();
    update();
}

QSGNode *BgfxItem::updatePaintNode(QSGNode * oldNode, QQuickItem::UpdatePaintNodeData *)
{
    TextureNode *node = static_cast<TextureNode *>(oldNode);

    if (!_renderThread->context) {
        QOpenGLContext *current = window()->openglContext();
        current->doneCurrent();

        _renderThread->context = new QOpenGLContext();
        _renderThread->context->setFormat(current->format());
        _renderThread->context->setShareContext(current);
        _renderThread->context->create();
        _renderThread->context->moveToThread(_renderThread);

        current->makeCurrent(window());

        QMetaObject::invokeMethod(this, "ready");
        return nullptr;
    }

    if (!node) {
        node = new TextureNode(window());

        connect(_renderThread, &RenderThread::textureReady, node, &TextureNode::newTexture, Qt::DirectConnection);
        connect(node, &TextureNode::pendingNewTexture, window(), &QQuickWindow::update, Qt::QueuedConnection);
        connect(window(), &QQuickWindow::beforeRendering, node, &TextureNode::prepareNode, Qt::DirectConnection);
        connect(node, &TextureNode::textureInUse, _renderThread, &RenderThread::renderNext, Qt::QueuedConnection);

        // Get the production of FBO textures started..
        QMetaObject::invokeMethod(_renderThread, "renderNext", Qt::QueuedConnection);
    }

    node->setRect(boundingRect());
    node->setTextureCoordinatesTransform(QSGSimpleTextureNode::NoTransform);
    node->setFiltering(QSGTexture::Linear);

    return node;
}
