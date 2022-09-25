#include "dialog.h"
#include <QApplication>
#include <QList>


QList<QDialog*>* Dialog::windowList = 0;


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationDisplayName(QString("MyStickyNotes"));
    a.setWindowIcon(QIcon(":/new/prefix1/icons/main_icon2.png"));   

    Dialog* window = new Dialog;
    window->show();

    return a.exec();
}
