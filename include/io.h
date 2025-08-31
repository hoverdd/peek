#ifndef IO_H
#define IO_H

typedef enum {
    SUCCESS = 0,
    ERR_OUTPUT,
    ERR_OPENNING_FILE,
    ERR_READ,
    ERR_CLOSE
} io_errors_t;

io_errors_t read_and_print_file(const char *filename);

int file_exists(const char *filename);

int is_dir(const char *filename);

char *io_error_to_string(io_errors_t error);

#endif