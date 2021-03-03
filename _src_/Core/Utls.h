#ifndef UTLS_H
#define UTLS_H

void CreateParentDir(fs::path path);
fs::path RemoveSlashEnd(fs::path path);
fs::path BackupPath(fs::path path);
#endif // !UTLS_H
