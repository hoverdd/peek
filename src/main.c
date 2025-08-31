#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "cli.h"

int main(int argc, char *argv[]) {
    char **files;
    int files_num;

    int result = parse_args(argc, argv, &files, &files_num);
    if (result != 0) {
        return 1;
    }

    for (int i = 0; i < files_num; i++) {
        if (file_exists(files[i])) {
            if (is_dir(files[i])) {
                fprintf(stderr, "'%s': Is a directory\n", files[i]);
                continue;
            }
            io_errors_t err = read_and_print_file(files[i]);
            if (err != SUCCESS) {
                fprintf(stderr, "%s\n", io_error_to_string(err));
            }
        } else {
            fprintf(stderr, "File: '%s' does not exist\n", files[i]);
        }
    }

    cleanup_files(files);

    return 0;
}