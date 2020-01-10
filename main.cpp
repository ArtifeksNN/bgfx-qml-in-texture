#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <bgfx/bgfx.h>
#include <QDebug>
#include "bgfx_item.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<BgfxItem>("BgfxItemExample", 1, 0, "BgfxItem");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    bool init = bgfx::init();

    qDebug() << "init bgfx" << init;
    return app.exec();
}
