#pragma once

#include "file.h"

struct directory_t {
    char name[MAX_SIZE];
    int num_files;
    int num_directories;
    struct file_t **files;
    struct directory_t **directories;
};

/**
 * Add a directory entry as subdirectory.
 * @param directory
 *  The directory which will contain a new subdirectory.
 * @param subdirectory
 *  The subdirectory to be added.
 * 
*/
void add_directory_in_a_directory(struct directory_t *directory, struct directory_t *subdirectory);


/**
 * Add a file entry into the directory.
 * @param directory
 *  The directory which will contain the new file.
 * @param subdirectory
 *  The file to be added.
 * 
*/
void add_file_in_a_directory(struct directory_t *directory, struct file_t *file);

/**
 * Print the current contents of the directory.
 * @param directory
 *  The directory to prints contents from.
*/
void print_directory(struct directory_t *directory);

/**
 * TODO: Perform a deep copy of source directory.
 * @param source
 *  The directory to perform copy on.
 * @return 
 *  A deep copy of the directory.
 * 
*/
struct directory_t *copy_directory(struct directory_t *source);


