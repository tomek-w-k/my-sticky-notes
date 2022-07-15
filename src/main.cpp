#include "dialog.h"
#include <QApplication>
#include <QList>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationDisplayName(QString("MyStickyNotes"));
    a.setWindowIcon(QIcon(":/new/prefix1/icons/main_icon2.png"));

    QList<QDialog*>* windowList = new QList<QDialog*>;
    Dialog* window = new Dialog(windowList);
    window->show();

    int appExecResult = a.exec();
    delete windowList;

    return appExecResult;
}
