#include "io.h"
#include "config.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


io_errors_t read_and_print_file(const char *filename) {
    char buffer[BUF_SIZE];
    
    FILE *file = fopen(filename, "rb"); // open a file in read-binary mode
    if (!file) return ERR_OPENNING_FILE; 

    size_t n; // bytes already read
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        size_t written = fwrite(buffer, 1, n, stdout); // print only n bytes
        if (written != n) {
            fclose(file); 
            return ERR_OUTPUT; // output error
        }
    }
    if (ferror(file)) {
        fclose(file);
        return ERR_READ; // read error
    }
    int err = fclose(file);
    if (err != 0) {
        return ERR_CLOSE; // close error
    }

    return SUCCESS;
}

io_errors_t print_file_numbered(const char *filename) {
    char buffer[BUF_SIZE];

    FILE *file = fopen(filename, "rb");
    if (!file) return ERR_OPENNING_FILE;

    int line = 1;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        fprintf(stdout, "%6d  %s", line, buffer);
        line++;
    }
    
    if (ferror(file)) {
        fclose(file);
        return ERR_READ; // read error
    }

    int err = fclose(file);
    if (err != 0) {
        return ERR_CLOSE;
    }
    return SUCCESS;
}

io_errors_t print_file_with_separator(const char *filename, const char *sep) {
    FILE *file = fopen(filename, "rb");
    if (!file) return ERR_OPENNING_FILE;

    char buffer[BUF_SIZE];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        trim_new_line(buffer);
        fprintf(stdout, "%s", buffer);
        fprintf(stdout, "%s\n", sep);
    }

    fprintf(stdout, "\n");

    if (ferror(file)) {
        fclose(file);
        return ERR_READ; // read error
    }

    int err = fclose(file);
    if (err != 0) {
        return ERR_CLOSE;
    }
    return SUCCESS;
}

void trim_new_line(char *s) {
    ssize_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

int file_exists(const char *filename) {
    int is_exist = 0;

    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        is_exist = 1;
        fclose(file);   
    }
    return is_exist;
}

int is_dir(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);

    return S_ISDIR(path_stat.st_mode);
}

void io_print_file(const char *filename) {
    io_errors_t err = read_and_print_file(filename);
    if (err != SUCCESS) {
        fprintf(stderr, "%s\n", io_error_to_string(err));
    }
}

void io_print_file_numbered(const char *filename) {
    io_errors_t err = print_file_numbered(filename);
    if (err != SUCCESS) {
        fprintf(stderr, "%s\n", io_error_to_string(err));
    }
}

void io_print_file_with_separator(const char *filename, const char *sep) {
    io_errors_t err = print_file_with_separator(filename, sep);
    if (err != SUCCESS) {
        fprintf(stderr, "%s\n", io_error_to_string(err));
    }
}

char *io_error_to_string(io_errors_t error) {
    char *error_str = "";
    switch (error) {
        case SUCCESS:
        case ERR_OUTPUT: { error_str = "Output error"; break; }
        case ERR_OPENNING_FILE: { error_str = "Error opening file"; break; }
        case ERR_READ: { error_str = "Error reading from file"; break; }
        case ERR_CLOSE: { error_str = "Error closing the file"; break; }
        default: { error_str = "Undefined error"; break; }
    }
    return error_str;
}