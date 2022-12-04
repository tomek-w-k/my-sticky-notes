#include "dialoginstanceproperties.h"


DialogInstanceProperties::DialogInstanceProperties(QWidget* parent) : QObject(parent) {
    this->id = QUuid::createUuid();
    this->ptr = qobject_cast<QDialog*>(parent);
}

DialogInstanceProperties::DialogInstanceProperties(QUuid id, QWidget *parent) {
    this->id = id;
    this->ptr = qobject_cast<QDialog*>(parent);
}

const QUuid &DialogInstanceProperties::getId() const {
    return id;
}

QDialog *DialogInstanceProperties::getPtr() const {
    return ptr;
}


