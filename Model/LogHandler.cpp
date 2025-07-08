#include "LogHandler.h"

#include <iostream>
#include <qdatetime.h>

// 初始化静态成员
LogHandler* LogHandler::m_instance = nullptr;

LogHandler::LogHandler(QObject *parent)
    : QObject(parent)
{
    m_instance = this;  // 设置静态实例
    qInstallMessageHandler(messageHandler);  // 安装消息处理器
}

void LogHandler::messageHandler(QtMsgType type,
                                const QMessageLogContext &context,
                                const QString &msg)
{
    Q_UNUSED(context);

    // 格式化日志消息 (可选添加消息类型)
    QString formattedMsg = QString("[%1] %2")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"))
                               .arg(msg);

    // 转发到控制台 (可选)
    std::cerr << formattedMsg.toStdString() << std::endl;

    // 通过实例发送信号
    if (m_instance) {
        emit m_instance->newMessage(formattedMsg);
    }
}
