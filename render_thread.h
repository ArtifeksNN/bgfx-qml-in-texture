#pragma once

#include <QThread>
#include <QOpenGLFramebufferObject>
#include <QOffscreenSurface>
#include <QOpenGLContext>

class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(const QSize &size);

    QOffscreenSurface *surface;
    QOpenGLContext *context;

public slots:
    void renderNext();
    void shutDown();

signals:
    void textureReady(int id, const QSize &size);

private:
    QOpenGLFramebufferObject *_renderFbo;
    QOpenGLFramebufferObject *_displayFbo;

    QSize _size;
};
