#ifndef FTC_FT_FILES_H
#define FTC_FT_FILES_H

#define P_READ 0x4
#define P_WRITE 0x2
#define P_EXEC 0x1

#define PERM_USR 0x64
#define PERM_GRP 0xA
#define PERM_OTH 0x1

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <regex.h>

#include "mime.h"
#include "options.h"
#include "utils.h"

/* Size functions */

// Verify if the file size is valid regarding the given size
// @param path the path to the file
// @param size the size to compare
// @return 1 if the file size is valid, 0 otherwise
int verify_files_by_size(const char *path, char *size);

// Get the size from the size option
// @param size the size option parameter
// @return the size
off_t get_size(char *size);

// Get the multiplier from the size option
// @param size the size option parameter
// @return the multiplier
int get_multiplier(char s);

// Get the size of a file
// @param path the path to the file
// @return the size of the file
off_t get_file_size(const char *file_path);

/* Date functions */

// Verify if the file modification date is valid regarding the given date
// @param path the path to the file
// @param date the date to compare
// @return 1 if the file modification date is valid, 0 otherwise
int verify_files_by_date(const char *path, char *date);

// Get the time from the date option
// @param date the date option parameter
// @return the time
double get_time(char *time);

// Get the multiplier from the date option
// @param date the date option parameter
// @return the multiplier
int get_time_multiplier(char s);

// Get the last modification time of a file in seconds
// @param path the path to the file
// @return the last modification time of the file in seconds
double get_seconds_from_last_modification(const char *file_path);

/* Name functions */

// Verify if the name of a file is valid
// @param f_name the name of the file
// @param name the name to compare or a pattern(regex)
// @return 1 if the name is valid, 0 otherwise
int verify_files_by_name(const char *f_name, char *name);

// Check the match between a string and a pattern
// @param str the string to match
// @param pattern the pattern to match
// @return 0 if the string matches the pattern, 1 otherwise
int regex_match(const char *str, const char *pattern);

/* Dir functions */

// Verify if the name of a directory is valid
// @param path the path to the file
// @param name the name of the file
// @return 1 if the name is valid, 0 otherwise
int verify_directories_by_name(const char *path, const char *name);

/* Grep functions */

// Verify if the file content contains the given string
// @param path the path to the file
// @param pattern the string to search
// @return 1 if the file content contains the given string, 0 otherwise
int verify_files_by_content_pattern(const char *path, const char *pattern);

// Read ascii files
// @param path the path to the file
// @return the content of the file
char *read_ascii_file(const char *path);

// Check if a file contains a given string
// @param path the path to the file
// @param pattern the string to search
// @return 1 if the file contains the given string, 0 otherwise
int file_contains_pattern(const char *path, const char *pattern);

/* Mime functions */

// Verify if the file mime type is valid regarding the given mime type.
// We verify mime type by extension
// @param path the path to the file
// @param mime the mime type to compare
// @return 1 if the file mime type is valid, 0 otherwise
int verify_files_by_mime(const char *path, char *mime);

/* Perm functions */

// Get the file permission
// @param path the path to the file
int get_file_perm(const char *path);

// Verify if the file permission is valid
// @param path the path to the file
// @param perm the permission to compare
// @return 1 if the file permission is valid, 0 otherwise
int verify_file_perm(const char *path, int perm);

#endif // FTC_FT_FILES_H
