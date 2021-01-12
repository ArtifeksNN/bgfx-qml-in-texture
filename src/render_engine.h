#pragma once

#include <QQuickWindow>
#include <QQuickRenderControl>
#include <QOffscreenSurface>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

class RenderEngine : public QQuickWindow
{
public:
    RenderEngine();

    void init();

    void render();

private:
     QQuickRenderControl* createRenderControl();

 private:
     QQuickRenderControl* m_renderControl;
     QOffscreenSurface* m_offscreenSurface;

     bool _isBgfxInit = false;
};

