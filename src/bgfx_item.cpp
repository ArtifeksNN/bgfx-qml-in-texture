#include "bgfx_item.h"

#include "render_thread.h"
#include "texture_node.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>


BgfxItem::BgfxItem() : _renderThread(nullptr)
{
    setFlag(ItemHasContents, true);
    _renderThread = new RenderThread(QSize(512, 512));
}

void BgfxItem::ready()
{
    _renderThread->surface = new QOffscreenSurface();
    _renderThread->surface->setFormat(_renderThread->context->format());
    _renderThread->surface->create();

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
        QOpenGLContext *current = QOpenGLContext::currentContext();
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
