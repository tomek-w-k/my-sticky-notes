#ifndef UTILS_H
#define UTILS_H

#include <QDir>
#include <QMessageBox>
#include <QStringList>
#include <QUuid>
#include <QProcess>

#include "constants.h"


using namespace std;

class Utils {

    Utils();

public:
    static optional<QDir> getTempDir();
    static QStringList getBackupFilePaths();
    static bool otherApplicationInstanceIsRunning();
};

#endif // UTILS_H
