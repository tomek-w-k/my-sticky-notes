#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>


const QString COMPANY = "tw";
const QString APP_NAME = "MyStickyNotes";
const QString APP_VERSION = "2.1";
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
const QString DIALOG_POSITIONS_SETTINGS_GROUP = "dialog_positions";
const QString NULL_UUID_STRING = "{00000000-0000-0000-0000-000000000000}";
const QString ARE_YOU_SURE_CLOSE_APP = "All notes will be lost.\nAre you sure?";
const QString ARE_YOU_SURE_TERMINATE_APP = "All notes will be stored in a backup directory. You will be able to restore them in the next session.\n\nAre you sure?";

#endif // CONSTANTS_H
