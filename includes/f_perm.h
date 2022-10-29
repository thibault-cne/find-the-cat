#ifndef FTC_F_PERM_H
#define FTC_F_PERM_H

#define P_READ 0x4
#define P_WRITE 0x2
#define P_EXEC 0x1

#define PERM_USR 0x64
#define PERM_GRP 0xA
#define PERM_OTH 0x1

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int get_file_perm(const char *path);
int verify_file_perm(const char *path, int perm);

#endif // FTC_F_PERM_H
