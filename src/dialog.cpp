#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QList<QDialog*>* windowList, QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->windowList = windowList;
    windowList->append(this);

    setRandomWindowIcon();
    setMainImage();
}

Dialog::~Dialog() {
    int itemNo = this->windowList->indexOf(this);
    this->windowList->remove(itemNo);

    delete ui;
}

void Dialog::contextMenuEvent(QContextMenuEvent *event) {
    QMenu contextMenu(this);
    contextMenu.addAction(ui->newFromClipboardAction);
    contextMenu.exec(event->globalPos());
}

void Dialog::setRandomWindowIcon()
{
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

void Dialog::setMainImage()
{
    QImage image = QGuiApplication::clipboard()->image();
    ui->imageFromClipboardLabel->setPixmap(QPixmap::fromImage(image));

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void Dialog::on_newFromClipboardAction_triggered() {
    dialog = new Dialog(this->windowList);
    dialog->show();
}


