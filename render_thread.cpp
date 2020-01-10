#include "render_thread.h"

#include <QOpenGLFunctions>
#include <QGuiApplication>
#include <QDebug>

RenderThread::RenderThread(const QSize& size):
    surface(nullptr)
    , context(nullptr)
    , _renderFbo(nullptr)
    , _displayFbo(nullptr)
    , _size(size)
{
}

void RenderThread::renderNext()
{
    context->makeCurrent(surface);

    if (!_renderFbo) {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        _renderFbo = new QOpenGLFramebufferObject(_size, format);
        _displayFbo = new QOpenGLFramebufferObject(_size, format);
    }

    _renderFbo->bind();
    context->functions()->glViewport(0, 0, _size.width(), _size.height());

    //render
    context->functions()->glFlush();

    _renderFbo->bindDefault();
    qSwap(_renderFbo, _displayFbo);

    emit textureReady(_displayFbo->texture(), _size);
}

void RenderThread::shutDown()
{
    context->makeCurrent(surface);
    delete _renderFbo;
    delete _displayFbo;
    context->doneCurrent();
    delete context;

    surface->deleteLater();

    exit();
    moveToThread(QGuiApplication::instance()->thread());
}
