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
#include <QFile>
#include <QMessageBox>

#include "dialoginstanceproperties.h"


const QString APP_NAME = "MyStickyNotes";
const QString MY_STICKY_NOTES_DIR_RELATIVE = ".my-sticky-notes";
const QString MY_STICKY_NOTES_DIR_TEMP_RELATIVE = "temp";
const QString CANNOT_CREATE_TEMP_DIR = "Cannot create temp directory. Image backup will not be saved.";
const QString CANNOT_SAVE_IMAGE_BACKUP = "An error has occurred. Image backup cannot be saved.";
const QString CANNOT_REMOVE_IMAGE_BACKUP = "An error has occurred. Image backup file cannot be removed.";
const QString NO_IMAGE_IN_CLIPBOARD = "No image in clipboard";

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
    void setContent();
    void setImageFromClipboard();    
    QList<DialogInstanceProperties*>* getDialogInstancePropertiesList();
    optional<QDir> getTempDir();
    void saveMainImageToTempDir();

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
    QString imageBackupFilePath;
};

#endif // DIALOG_H
