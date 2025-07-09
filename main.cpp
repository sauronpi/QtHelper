#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include "Model/MyTestModel.h"
#include "Model/Loghandler.h"
#include "Model/DisplayMonitorInfo.h"
#include "Model/MonitorControl.h"

int main(int argc, char *argv[])
{
    winrt::init_apartment();
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
    qmlRegisterType<DisplayMonitorInfo>("QtHelper.DisplayMonitorInfo", 1, 0, "DisplayMonitorInfo");
    qmlRegisterType<MonitorControl>("QtHelper.MonitorControl", 1, 0, "MonitorControl");
    engine.loadFromModule("QtHelper", "Main");
    // 清理 WinRT
    winrt::uninit_apartment();
    return app.exec();
}
