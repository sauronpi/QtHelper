#include "MyTestModel.h"
#include <iostream>
#include <QDebug>

MyTestModel::MyTestModel(QObject *parent)
    : QObject{parent}
{}

void MyTestModel::buttonOnClicked(void) {
    qDebug() << "qDebug";
    std::cout << "cout";
}
