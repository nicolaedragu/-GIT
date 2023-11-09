#pragma once

#define MAX_SIZE 1024

struct file_t {
    char name[MAX_SIZE];
    char *content;
    int size; 
};

/**
 * Create a new file entry
 * @param filename
 *  The name of the file entry.
 * @param num_bytes
 *  Number of bytes of the content.
 * @param content
 *  A byte array containing the data of the file.
*/
struct file_t* create_file(const char *filename, const int num_bytes, const char *content);

/**
 * Print content of a file.
 * @param file
 *  The file entry to print information from.
*/
void print_file(struct file_t *file);