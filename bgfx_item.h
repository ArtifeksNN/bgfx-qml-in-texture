#pragma once

#include <QQuickItem>

class RenderThread;

class BgfxItem : public QQuickItem
{
    Q_OBJECT

public:
    BgfxItem();

    void bgfxInit();
signals:

public slots:
    void ready();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
    RenderThread* _renderThread;
    bool _isBgfxInit;
};
