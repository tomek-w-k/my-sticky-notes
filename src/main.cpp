#include <QApplication>
#include <QList>
#include <QMessageBox>

#include "dialog.h"
#include "utils.h"
#include "constants.h"

QList<DialogInstanceProperties*>* Dialog::dialogInstancePropertiesList = 0;


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationDisplayName(QString(APP_NAME));
    a.setWindowIcon(QIcon(":/new/prefix1/icons/main_icon2.png"));

    Dialog* window;
    QStringList backupFilePathList = Utils::getBackupFilePaths();

    if (backupFilePathList.isEmpty() || Utils::otherApplicationInstanceIsRunning())
        window = new Dialog;
    else {
        QMessageBox msgBox(QMessageBox::Question, APP_NAME, RESTORE_LAST_SESSION, QMessageBox::Yes | QMessageBox::No);

        switch (msgBox.exec()) {
            case QMessageBox::Yes:
                foreach (QString filePath, backupFilePathList) {
                    window = new Dialog(QFile(filePath));
                    window->show();
                }
                break;

            case QMessageBox::No:
                QSettings settings(COMPANY, APP_NAME);
                settings.remove(DIALOG_POSITIONS_SETTINGS_GROUP);

                foreach (QString filePath, backupFilePathList) {
                    QFile imageBackupFile(filePath);

                    if (imageBackupFile.exists() && !imageBackupFile.remove())
                        QMessageBox::warning(nullptr, APP_NAME, CANNOT_REMOVE_IMAGE_BACKUP, QMessageBox::Ok);
                }

                window = new Dialog();
                window->show();
                break;
        }
    }

    return a.exec();
}
