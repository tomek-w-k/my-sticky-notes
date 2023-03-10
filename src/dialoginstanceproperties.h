#ifndef DIALOGINSTANCEPROPERTIES_H
#define DIALOGINSTANCEPROPERTIES_H

#include <QObject>
#include <QWidget>
#include <QUuid>
#include <QDialog>


class DialogInstanceProperties : public QObject {

    Q_OBJECT
public:
    DialogInstanceProperties(QWidget* parent = nullptr);
    DialogInstanceProperties(QUuid id, QWidget* parent = nullptr);
    const QUuid &getId() const;
    QDialog *getPtr() const;

private:
    QUuid id;
    QDialog* ptr;
};

#endif // DIALOGINSTANCEPROPERTIES_H
