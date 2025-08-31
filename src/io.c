#include "io.h"
#include "config.h"

#include <stdio.h>
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