#ifndef MYTESTMODEL_H
#define MYTESTMODEL_H

#include <QObject>
#include <winrt/windows.foundation.h>

class MyTestModel : public QObject
{
    Q_OBJECT
public:
    explicit MyTestModel(QObject *parent = nullptr);
    Q_INVOKABLE void buttonOnClicked(void);
signals:
};

#endif // MYTESTMODEL_H
