#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <QObject>
#include <QString>
#include <QtMessageHandler>

class LogHandler : public QObject {
    Q_OBJECT
public:
    explicit LogHandler(QObject *parent = nullptr);

    // 自定义消息处理函数
    static void messageHandler(QtMsgType type,
                               const QMessageLogContext &context,
                               const QString &msg);

signals:
    void newMessage(QString message);  // 新日志信号

private:
    static LogHandler *m_instance;  // 静态实例指针
};

#endif // LOGHANDLER_H
