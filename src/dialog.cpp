#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QFile imageFile) : ui(new Ui::Dialog) {
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->graphicsScene = new QGraphicsScene(this);
    this->tempDirOptional = Utils::getTempDir();
    this->dialogInstanceProperties = nullptr;
    this->dialogInstancePropertiesList = getDialogInstancePropertiesList();

    this->installEventFilter(this);

    setRandomWindowIcon();          

    if (imageFile.fileName().isNull())
        setContentFromClipboard();
    else {
        QString simpleFileName = QFileInfo(imageFile.fileName()).fileName().remove(BACKUP_FILE_EXTENSION);

        this->dialogInstanceProperties = new DialogInstanceProperties(QUuid(simpleFileName), this);
        this->imageBackupFilePath = imageFile.fileName();

        setContentFromBackupFile();
    }

    dialogInstancePropertiesList->append(this->dialogInstanceProperties);
}

Dialog::~Dialog() {    
    this->dialogInstancePropertiesList->removeOne(this->dialogInstanceProperties);
    delete ui;

    QFile imageBackupFile(this->imageBackupFilePath);

    if (imageBackupFile.exists() && !imageBackupFile.remove())
        QMessageBox::warning(this, APP_NAME, CANNOT_REMOVE_IMAGE_BACKUP, QMessageBox::Ok);

    if (this->dialogInstancePropertiesList->isEmpty())
        delete this->dialogInstancePropertiesList;
}

void Dialog::contextMenuEvent(QContextMenuEvent *event) {
    QMenu contextMenu(this);
    contextMenu.addAction(ui->newFromClipboardAction);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->copyAction);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->saveAsAction);
    contextMenu.addSeparator();
    contextMenu.addAction(ui->aboutAction);

    if (this->dialogInstanceProperties == nullptr) {
        ui->saveAsAction->setDisabled(true);
        ui->copyAction->setDisabled(true);
    }

    contextMenu.exec(event->globalPos());
}

void Dialog::setRandomWindowIcon() {
    int iconNo = rand() % ((6 + 1) - 1) + 1;
    static int prevIconNo = iconNo;

    if (iconNo == prevIconNo)
        while (iconNo == prevIconNo)
            iconNo = rand() % ((6 + 1) - 1) + 1;

    prevIconNo = iconNo;

    switch (iconNo) {
    case 1:
        this->setWindowIcon(QIcon(":/new/prefix1/icons/blue_sticky_note.png"));
        break;
    case 2:
        this->setWindowIcon(QIcon(":/new/prefix1/icons/green_sticky_note.png"));
        break;
    case 3:
        this->setWindowIcon(QIcon(":/new/prefix1/icons/orange_sticky_note.png"));
        break;
    case 4:
        this->setWindowIcon(QIcon(":/new/prefix1/icons/purple_sticky_note.png"));
        break;
    case 5:
        this->setWindowIcon(QIcon(":/new/prefix1/icons/red_sticky_note.png"));
        break;
    case 6:
        this->setWindowIcon(QIcon(":/new/prefix1/icons/yellow_sticky_note.png"));
        break;
    }
}

void Dialog::setContent(QPixmap pixmap) {
    this->window()->setFixedSize(pixmap.size());
    this->graphicsScene->addPixmap(pixmap);
    ui->graphicsView->setScene(this->graphicsScene);
}

void Dialog::setContentFromClipboard() {
    if (!QGuiApplication::clipboard()->pixmap().isNull()) {
        this->dialogInstanceProperties = new DialogInstanceProperties(this);
        setContent(QGuiApplication::clipboard()->pixmap());
        saveMainImageToTempDir();
    }
    else {
        this->graphicsScene->addSimpleText(NO_IMAGE_IN_CLIPBOARD);

        int graphicsViewWidth = this->graphicsScene->sceneRect().width() + 200;
        int graphicsViewHeight = this->graphicsScene->sceneRect().height() + 100;

        this->window()->setFixedSize(graphicsViewWidth, graphicsViewHeight);
        ui->graphicsView->setScene(this->graphicsScene);
    }
}

void Dialog::setContentFromBackupFile() {
    setContent(QPixmap(this->imageBackupFilePath));
}

QList<DialogInstanceProperties*> *Dialog::getDialogInstancePropertiesList() {
    if (!this->dialogInstancePropertiesList)
        return new QList<DialogInstanceProperties*>;

    return this->dialogInstancePropertiesList;
}

void Dialog::saveMainImageToTempDir() {
    if (this->tempDirOptional) {
        QString fileName = this->dialogInstanceProperties->getId().toString(QUuid::WithoutBraces) + BACKUP_FILE_EXTENSION;
        this->imageBackupFilePath = tempDirOptional.value().filePath(fileName);
        QPixmap pixmap = ui->graphicsView->grab();

        if (!pixmap.save(this->imageBackupFilePath))
            QMessageBox::warning(this, APP_NAME, CANNOT_SAVE_IMAGE_BACKUP, QMessageBox::Ok);
    }
    else QMessageBox::warning(this, APP_NAME, CANNOT_CREATE_TEMP_DIR, QMessageBox::Ok);
}

void Dialog::on_newFromClipboardAction_triggered() {
    dialog = new Dialog;
    dialog->show();
}

void Dialog::on_copyAction_triggered() {
    QImage image = ui->graphicsView->grab().toImage();
    QGuiApplication::clipboard()->setImage(image);
}

void Dialog::on_saveAsAction_triggered() {
    QImage image = ui->graphicsView->grab().toImage();
    QString fileName = QDir::home().filePath(QDateTime::currentDateTime().toString("yyyy-MM-dd-HHmmsszzz"));
    QString filePath = QFileDialog::getSaveFileName(this, SAVE_NOTE_DIALOG_TITLE, fileName, "Images (*.png)");

    if (!filePath.isEmpty())
        image.save(filePath);
}

void Dialog::on_aboutAction_triggered() {
    QString buildDateTime = QString("%1 %2").arg(__DATE__).arg(__TIME__);
    QString content = QString("<b>%1 %2</b><br><br>%3<br><br>%4<br><br><br>%5")
                          .arg(APP_NAME)
                          .arg(APP_VERSION)
                          .arg("Based on Qt 6.2.4")
                          .arg("Built on " + buildDateTime)
                          .arg("Copyright 2022 T. W??sik. All rights reserved.");

    QMessageBox msgBox = QMessageBox();
    msgBox.setIconPixmap(QPixmap(":/new/prefix1/icons/main_icon2.png").scaledToHeight(64, Qt::SmoothTransformation));
    msgBox.setWindowTitle("About");
    msgBox.setText(content);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.exec();
}

