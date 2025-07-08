#ifndef DISPLAYMONITORINFO_H
#define DISPLAYMONITORINFO_H

#include <QObject>
#include <QVector>
#include <QVariantMap>
#include <winrt/Windows.Devices.Display.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.Streams.h>

namespace winrt {
using namespace Windows::Devices::Display;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
}

class DisplayMonitorInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<QVariantMap> monitors READ monitors NOTIFY monitorsChanged)

public:
    explicit DisplayMonitorInfo(QObject* parent = nullptr);

    QVector<QVariantMap> monitors() const;
    Q_INVOKABLE void refresh();

signals:
    void monitorsChanged();

private:
    QVector<QVariantMap> m_monitors;

    static QByteArray bufferToByteArray(const winrt::IBuffer& buffer);
    static QString formatEdidHex(const QByteArray& data);
};

#endif // DISPLAYMONITORINFO_H
