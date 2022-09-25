#include "dialoginstanceproperties.h"


DialogInstanceProperties::DialogInstanceProperties(QObject* parent) : QObject(parent) {
    this->id = QUuid::createUuid();
}

const QUuid &DialogInstanceProperties::getId() const {
    return id;
}

QDialog *DialogInstanceProperties::getPtr() const {
    return ptr;
}


