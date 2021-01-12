#pragma once

#include <QObject>
#include <QQuickItem>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <QQuickWindow>

#include "render_engine.h"

class BgfxItem2 : public QQuickItem
{
    Q_OBJECT
public:
    BgfxItem2();

    void bgfxInit();

signals:

public slots:

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);

private:
    bool _isBgfxInit;

//    QQuickWindow render_window;
    RenderEngine render;

};

