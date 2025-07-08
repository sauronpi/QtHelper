#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include "Model/MyTestModel.h"
#include "Model/Loghandler.h"
#include "Model/DisplayMonitorInfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 创建日志处理器并暴露给QML
    LogHandler logHandler;
    engine.rootContext()->setContextProperty("logHandler", &logHandler);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    qmlRegisterType<MyTestModel>("QtHelper.MyTestModel", 1, 0, "MyTestModel");
    qmlRegisterType<DisplayMonitorInfo>("QtHelper.MyTestModel", 1, 0, "DisplayMonitorInfo");
    engine.loadFromModule("QtHelper", "Main");
    return app.exec();
}
