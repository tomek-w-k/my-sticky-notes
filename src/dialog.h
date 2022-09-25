#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QClipboard>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QIcon>
#include <QString>
#include <QContextMenuEvent>
#include <QMenu>
#include <QGraphicsScene>
#include <QDir>

#include "dialoginstanceproperties.h"


const QString MY_STICKY_NOTES_DIR_RELATIVE = ".my-sticky-notes";
const QString MY_STICKY_NOTES_DIR_TEMP_RELATIVE = "temp";

using namespace std;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog();
    ~Dialog();
    void contextMenuEvent(QContextMenuEvent* event);

private:
    void setRandomWindowIcon();
    void setMainImage();
    QList<DialogInstanceProperties*>* getDialogInstancePropertiesList();
    optional<QDir> getTempDir();

private slots:
    void on_newFromClipboardAction_triggered();

private:
    static QList<DialogInstanceProperties*>* dialogInstancePropertiesList;
    DialogInstanceProperties* dialogInstanceProperties;
    Ui::Dialog *ui;
    QClipboard* clipboard;
    Dialog* dialog;
    QGraphicsScene* graphicsScene;
    optional<QDir> tempDirOptional;
};

#endif // DIALOG_H
