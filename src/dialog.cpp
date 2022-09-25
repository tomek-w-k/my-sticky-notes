#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog() : ui(new Ui::Dialog) {
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->windowList = getWindowList();
    windowList->append(this);
    this->graphicsScene = new QGraphicsScene(this);

    setRandomWindowIcon();
    setMainImage();
}

Dialog::~Dialog() {    
    this->windowList->removeOne(this);

    delete ui;

    if (this->windowList->isEmpty())
        delete this->windowList;
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

QList<QDialog*>* Dialog::getWindowList() {
    if (!this->windowList)
        return new QList<QDialog*>;

    return this->windowList;
}

void Dialog::on_newFromClipboardAction_triggered() {
    dialog = new Dialog;
    dialog->show();
}


