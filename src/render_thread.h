#pragma once

#include <QThread>
#include <QOpenGLFramebufferObject>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <bgfx/bgfx.h>

class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(const QSize &size);

    QOffscreenSurface *surface;
    QOpenGLContext *context;

    void bgfxInit();

public slots:
    void renderNext();
    void shutDown();

signals:
    void textureReady(int id, const QSize &size);

private:
    uint16_t m_viewId{0};

    bgfx::FrameBufferHandle m_offscreenFB{bgfx::kInvalidHandle};
    bgfx::TextureHandle m_backBuffer{bgfx::kInvalidHandle};
    bgfx::TextureHandle m_depthBuffer{bgfx::kInvalidHandle};

    QSize _size;
};
