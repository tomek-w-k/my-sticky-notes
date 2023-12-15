#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>
#include <QDialog>
#include <QClipboard>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QIcon>
#include <QString>
#include <QContextMenuEvent>
#include <QEvent>
#include <QMenu>
#include <QGraphicsScene>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QTimer>

#include "dialoginstanceproperties.h"
#include "constants.h"
#include "utils.h"


using namespace std;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QFile imageFile = QFile());
    ~Dialog();    
    void contextMenuEvent(QContextMenuEvent* event);
    bool eventFilter(QObject* object, QEvent* event);

private:
    void setRandomWindowIcon();
    void setContent(QPixmap pixmap);
    void setContentFromClipboard();
    void setContentFromBackupFile();
    QList<DialogInstanceProperties*>* getDialogInstancePropertiesList();    
    void saveMainImageToTempDir();
    void saveDialogPosition();

private slots:
    void on_newFromClipboardAction_triggered();
    void on_copyAction_triggered();
    void on_saveAsAction_triggered();
    void on_closeAllAction_triggered();
    void on_terminateApplicationAction_triggered();
    void on_aboutAction_triggered();

    void handleDialogMoveTimeout();

private:
    static QList<DialogInstanceProperties*>* dialogInstancePropertiesList;
    DialogInstanceProperties* dialogInstanceProperties;
    Ui::Dialog *ui;
    Dialog* dialog;
    QGraphicsScene* graphicsScene;
    optional<QDir> tempDirOptional;
    QString imageBackupFilePath;
    QString dialogPositionKey;
    QSettings* settings;
    int lastEvent;
    int dialogMoveEventCounter;
    QTimer* dialogMoveTimer;
};

#endif // DIALOG_H
