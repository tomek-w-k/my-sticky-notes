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
}

Dialog::~Dialog() {    
    this->dialogInstancePropertiesList->removeOne(this->dialogInstanceProperties);

    delete ui;

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
    this->graphicsScene->addPixmap(QGuiApplication::clipboard()->pixmap());
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

void Dialog::on_newFromClipboardAction_triggered() {
    dialog = new Dialog;
    dialog->show();
}


