#include "utils.h"


Utils::Utils() { }

optional<QDir> Utils::getTempDir() {
    QDir tempDir = QDir::home().filePath(MY_STICKY_NOTES_DIR_RELATIVE);
    tempDir = tempDir.filePath(MY_STICKY_NOTES_DIR_TEMP_RELATIVE);

    if (tempDir.mkpath(tempDir.path()))
        return tempDir;
    else return nullopt;
}

QStringList Utils::getBackupFilePaths() {
    optional<QDir> tempDirOptional = Utils::getTempDir();
    QStringList filePathList;

    if (tempDirOptional) {
        QStringList fileNameList = tempDirOptional.value().entryList(QStringList() << QString("*").append(BACKUP_FILE_EXTENSION));
        foreach (QString fileName, fileNameList) {
            QString fileNameUuidCheck = fileName;
            if (!QUuid(fileNameUuidCheck.remove(BACKUP_FILE_EXTENSION)).isNull())
                filePathList.append(tempDirOptional.value().filePath(fileName));
        }
    }
    else QMessageBox::warning(NULL, APP_NAME, CANNOT_ACCESS_TEMP_DIR, QMessageBox::Ok);

    return filePathList;
}

bool Utils::otherApplicationInstanceIsRunning() {
    #ifdef Q_OS_WIN
        QProcess process;
        process.start("tasklist", QStringList() << "/nh" << "/fi" << "Imagename eq " + APP_EXEC_FILE_NAME + APP_EXEC_FILE_EXTENSION);
        process.waitForFinished(-1);

        QString output = process.readAllStandardOutput();

        if (output.count(APP_EXEC_FILE_NAME + APP_EXEC_FILE_EXTENSION) > 1)
            return true;
        else return false;
    #endif

    #ifdef Q_OS_LINUX
        QString command = QString("/bin/sh -c \"ps -A | grep %1\"").arg(APP_EXEC_FILE_NAME);

        QProcess process;
        process.start(command);
        process.waitForFinished(-1);

        QString output = process.readAllStandardOutput();

        if (output.count(APP_EXEC_FILE_NAME) > 1)
            return true;
        else return false;
    #endif

    return true;
}
