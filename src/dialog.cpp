#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog() : ui(new Ui::Dialog) {
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->dialogInstancePropertiesList = getDialogInstancePropertiesList();
    this->dialogInstanceProperties = new DialogInstanceProperties(this);
    dialogInstancePropertiesList->append(this->dialogInstanceProperties);
    this->graphicsScene = new QGraphicsScene(this);
    this->tempDirOptional = getTempDir();

    setRandomWindowIcon();
    setMainImage();
    saveMainImageToTempDir();
}

Dialog::~Dialog() {    
    this->dialogInstancePropertiesList->removeOne(this->dialogInstanceProperties);

    delete ui;

    QFile imageBackupFile(this->imageBackupFilePath);
    if (!imageBackupFile.remove())
        QMessageBox::warning(this, APP_NAME, CANNOT_REMOVE_IMAGE_BACKUP, QMessageBox::Ok);

    if (this->dialogInstancePropertiesList->isEmpty())
        delete this->dialogInstancePropertiesList;
}

void Dialog::contextMenuEvent(QContextMenuEvent *event) {
    QMenu contextMenu(this);
    contextMenu.addAction(ui->newFromClipboardAction);
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

void Dialog::setMainImage() {
    QPixmap pixmap = QGuiApplication::clipboard()->pixmap();

    this->window()->setFixedSize(pixmap.size());
    this->graphicsScene->addPixmap(pixmap);
    ui->graphicsView->setScene(this->graphicsScene);
}

QList<DialogInstanceProperties*> *Dialog::getDialogInstancePropertiesList() {
    if (!this->dialogInstancePropertiesList)
        return new QList<DialogInstanceProperties*>;

    return this->dialogInstancePropertiesList;
}

optional<QDir> Dialog::getTempDir() {
    QDir tempDir = QDir::home().filePath(MY_STICKY_NOTES_DIR_RELATIVE);
    tempDir = tempDir.filePath(MY_STICKY_NOTES_DIR_TEMP_RELATIVE);

    if (tempDir.mkpath(tempDir.path()))
        return tempDir;
    else return nullopt;
}

void Dialog::saveMainImageToTempDir() {
    if (this->tempDirOptional) {
        QString fileName = this->dialogInstanceProperties->getId().toString(QUuid::WithoutBraces) + ".png";
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
