#pragma once

#include <QQuickItem>

class RenderThread;

class BgfxItem : public QQuickItem
{
    Q_OBJECT

public:
    BgfxItem();
signals:

public slots:
    void ready();

protected:
    // QQuickItem interface
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
    RenderThread* _renderThread;
};
