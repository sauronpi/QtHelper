#ifndef MONITORCONTROL_H
#define MONITORCONTROL_H

#include <QObject>
#include <QVector>
#include <QVariantList>
#include <Windows.h>
#include <physicalmonitorenumerationapi.h>
#include <lowlevelmonitorconfigurationapi.h>

class MonitorControl : public QObject
{
    Q_OBJECT
public:
    explicit MonitorControl(QObject *parent = nullptr);
    ~MonitorControl();

    Q_INVOKABLE void refreshMonitors(); // 刷新显示器列表
    Q_INVOKABLE void setBrightness(int index, int value); // 设置亮度

signals:
    void monitorsUpdated(const QVariantList &names); // 发送显示器名到QML

private:
    struct MonitorHandle {
        HMONITOR hMonitor;
        QVector<PHYSICAL_MONITOR> physicalMonitors;
    };

    QVector<MonitorHandle> monitorHandles;

    static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor,
                                         LPRECT lprcMonitor, LPARAM dwData);
};

#endif // MONITORCONTROL_H
