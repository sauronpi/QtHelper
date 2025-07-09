#include "MonitorControl.h"
#include <QDebug>
#include <QVector>

MonitorControl::MonitorControl(QObject *parent) : QObject(parent)
{
    // 在构造时刷新显示器列表
    refreshMonitors();
}

MonitorControl::~MonitorControl()
{
    // 清理物理显示器句柄
    for (auto &handle : monitorHandles) {
        if (!handle.physicalMonitors.isEmpty()) {
            DestroyPhysicalMonitors(handle.physicalMonitors.size(), handle.physicalMonitors.data());
        }
    }
}

void MonitorControl::refreshMonitors()
{
    // 清理之前的句柄
    for (auto &handle : monitorHandles) {
        if (!handle.physicalMonitors.isEmpty()) {
            DestroyPhysicalMonitors(handle.physicalMonitors.size(), handle.physicalMonitors.data());
            handle.physicalMonitors.clear();
        }
    }
    monitorHandles.clear();

    // 枚举显示器
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(this));

    // 获取显示器名称
    QVariantList monitorNames;
    for (auto &handle : monitorHandles) {
        MONITORINFOEX monitorInfo;
        monitorInfo.cbSize = sizeof(monitorInfo);
        if (GetMonitorInfo(handle.hMonitor, &monitorInfo)) {
            monitorNames.append(QString::fromWCharArray(monitorInfo.szDevice));
        }
    }

    emit monitorsUpdated(monitorNames);
}

BOOL CALLBACK MonitorControl::MonitorEnumProc(HMONITOR hMonitor, HDC /*hdcMonitor*/,
                                              LPRECT /*lprcMonitor*/, LPARAM dwData)
{
    MonitorControl *controller = reinterpret_cast<MonitorControl*>(dwData);
    if (!controller) {
        return FALSE;
    }

    DWORD numPhysicalMonitors = 0;
    // 获取物理显示器数量
    if (!GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &numPhysicalMonitors)) {
        qWarning() << "GetNumberOfPhysicalMonitorsFromHMONITOR failed. Error code:" << GetLastError();
        return TRUE; // 继续枚举
    }

    // 分配物理显示器数组
    QVector<PHYSICAL_MONITOR> physicalMonitors;
    physicalMonitors.resize(numPhysicalMonitors);

    if (!GetPhysicalMonitorsFromHMONITOR(hMonitor, numPhysicalMonitors, physicalMonitors.data())) {
        qWarning() << "GetPhysicalMonitorsFromHMONITOR failed. Error code:" << GetLastError();
        return TRUE;
    }

    // 保存到控制器
    MonitorControl::MonitorHandle handle;
    handle.hMonitor = hMonitor;
    handle.physicalMonitors = physicalMonitors;
    controller->monitorHandles.append(handle);

    return TRUE;
}

void MonitorControl::setBrightness(int index, int value)
{
    if (index < 0 || index >= monitorHandles.size()) {
        qWarning() << "Invalid monitor index:" << index;
        return;
    }

    MonitorHandle &handle = monitorHandles[index];
    for (auto &physical : handle.physicalMonitors) {
        // 0x10 是亮度控制码，值范围0-100
        if (!SetVCPFeature(physical.hPhysicalMonitor, 0x10, static_cast<DWORD>(value))) {
            DWORD error = GetLastError();
            qWarning() << "SetVCPFeature failed. Error code:" << error;
        } else {
            qDebug() << "Successfully set brightness to" << value << "for monitor" << index;
        }
    }
}
