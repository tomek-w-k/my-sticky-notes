#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName(QString("MyStickyNotes"));
    a.setWindowIcon(QIcon(":/new/prefix1/icons/main_icon2.png"));

    Dialog w;
    w.show();

    return a.exec();
}