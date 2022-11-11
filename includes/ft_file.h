#ifndef FTC_FT_FILES_H
#define FTC_FT_FILES_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

#endif // FTC_FT_FILES_H
