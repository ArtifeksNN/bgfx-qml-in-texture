#pragma once

#include <QThread>
#include <QOpenGLFramebufferObject>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include "render_engine.h"

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
    RenderEngine render;

    QOpenGLFramebufferObject *_renderFbo;
    QOpenGLFramebufferObject *_displayFbo;

//    bgfx::FrameBufferHandle _bgfxRenderFbo;
//    bgfx::FrameBufferHandle _bgfxDisplayFbo;
    void *m_texture{nullptr};
    uint16_t m_viewId{0};
    uint64_t m_frameCount{0};

    bgfx::FrameBufferHandle m_offscreenFB{bgfx::kInvalidHandle};
    bgfx::TextureHandle m_backBuffer{bgfx::kInvalidHandle};
    bgfx::TextureHandle m_depthBuffer{bgfx::kInvalidHandle};

    QSize _size;
};
