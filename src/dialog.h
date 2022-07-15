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


namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QList<QDialog*>* windowList, QWidget *parent = 0);
    ~Dialog();
    void contextMenuEvent(QContextMenuEvent* event);

private:
    void setRandomWindowIcon();
    void setMainImage();

private slots:
    void on_newFromClipboardAction_triggered();

private:
    QList<QDialog*>* windowList;
    Ui::Dialog *ui;
    QClipboard* clipboard;
    Dialog* dialog;
};

#endif // DIALOG_H
