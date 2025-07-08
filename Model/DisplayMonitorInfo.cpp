#include "DisplayMonitorInfo.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <QtCore/qdebug.h>

using namespace winrt;
using namespace Windows::Devices::Display;
using namespace Windows::Foundation;

DisplayMonitorInfo::DisplayMonitorInfo(QObject* parent)
    : QObject(parent)
{
    refresh();
}

QVector<QVariantMap> DisplayMonitorInfo::monitors() const
{
    return m_monitors;
}

void DisplayMonitorInfo::refresh()
{
    try {
        m_monitors.clear();

        // 获取所有显示器
        auto selector = DisplayMonitor::GetDeviceSelector();
        auto devices = winrt::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(selector).get();

        for (const auto& device : devices) {
            QVariantMap monitorInfo;
            monitorInfo["deviceId"] = QString::fromWCharArray(device.Id().c_str());
            monitorInfo["name"] = QString::fromWCharArray(device.Name().c_str());

            try {
                // 获取显示器实例
                auto monitor = DisplayMonitor::FromInterfaceIdAsync(device.Id()).get();

                // 获取 EDID 数据
                auto edidBuffer = monitor.GetDescriptor(DisplayMonitorDescriptorKind::Edid);

                // 检查是否有 EDID 数据
                if (!edidBuffer.empty()) {
                    // 将 com_array<byte> 转换为 QByteArray
                    QByteArray edidData(
                        reinterpret_cast<const char*>(edidBuffer.data()),
                        static_cast<int>(edidBuffer.size())
                        );

                    monitorInfo["edid"] = formatEdidHex(edidData);
                    monitorInfo["edidRaw"] = QString(edidData.toHex());
                } else {
                    monitorInfo["edid"] = "无EDID数据";
                    monitorInfo["edidRaw"] = "";
                }

                // 添加物理尺寸信息 - 修复这部分
                auto physicalSize = monitor.PhysicalSizeInInches();
                if (physicalSize) {
                    // 正确调用 Value() 方法
                    auto size = physicalSize.Value();
                    monitorInfo["width"] = size.Width;
                    monitorInfo["height"] = size.Height;
                } else {
                    monitorInfo["width"] = 0.0;
                    monitorInfo["height"] = 0.0;
                }

            } catch (const winrt::hresult_error& e) {
                qWarning() << "Error getting monitor info:" << e.message().c_str();
                monitorInfo["error"] = QString::fromWCharArray(e.message().c_str());
            }

            m_monitors.append(monitorInfo);
        }

        emit monitorsChanged();

    } catch (const winrt::hresult_error& e) {
        qCritical() << "WinRT error:" << e.message().c_str();
    }
}

QString DisplayMonitorInfo::formatEdidHex(const QByteArray& data)
{
    QString result;
    constexpr int bytesPerLine = 16;

    for (int i = 0; i < data.size(); ++i) {
        if (i % bytesPerLine == 0 && i > 0) {
            result += '\n';
        }
        result += QString("%1 ").arg(static_cast<uint8_t>(data[i]), 2, 16, QChar('0')).toUpper();
    }

    return result.trimmed();
}
