#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>


const QString APP_NAME = "MyStickyNotes";
const QString APP_VERSION = "2.0";
const QString APP_EXEC_FILE_NAME = "my-sticky-notes";
const QString APP_EXEC_FILE_EXTENSION = ".exe";
const QString MY_STICKY_NOTES_DIR_RELATIVE = ".my-sticky-notes";
const QString MY_STICKY_NOTES_DIR_TEMP_RELATIVE = "temp";
const QString CANNOT_CREATE_TEMP_DIR = "Cannot create temp directory.\nImage backup will not be saved.";
const QString CANNOT_ACCESS_TEMP_DIR = "Cannot access temp directory.\nBackup images will not be restored.";
const QString CANNOT_SAVE_IMAGE_BACKUP = "An error has occurred.\nImage backup cannot be saved.";
const QString CANNOT_REMOVE_IMAGE_BACKUP = "An error has occurred.\nImage backup file cannot be removed.";
const QString NO_IMAGE_IN_CLIPBOARD = "No image in clipboard";
const QString BACKUP_FILE_EXTENSION = ".png";
const QString LOCK_FILE = ".my-sticky-notes";
const QString RESTORE_LAST_SESSION = "This application has been closed unexpectedly.\nRestore last session?";
const QString SAVE_NOTE_DIALOG_TITLE = "Save note as";

#endif // CONSTANTS_H
