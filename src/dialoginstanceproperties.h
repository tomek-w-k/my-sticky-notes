#ifndef DIALOGINSTANCEPROPERTIES_H
#define DIALOGINSTANCEPROPERTIES_H

#include <QObject>
#include <QUuid>
#include <QDialog>


class DialogInstanceProperties : public QObject {

    Q_OBJECT
public:
    DialogInstanceProperties(QObject* parent = nullptr);
    const QUuid &getId() const;
    QDialog *getPtr() const;

private:
    QUuid id;
    QDialog* ptr;
};

#endif // DIALOGINSTANCEPROPERTIES_H
