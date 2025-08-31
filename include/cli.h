#ifndef CLI_H
#define CLI_H

typedef struct {
    int show_line_numbers;
    const char *separator;
    const char **files;
    int num_files;
} Args;

void parse_args(int argc, const char *argv[], Args *args);

void process_files(Args *args);

int validate_file(const char *filename);

void cleanup_files(const char **files);

#endif