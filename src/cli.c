#include "cli.h"

#include <stdlib.h>
#include <stdio.h>

int parse_args(int argc, char *argv[], char ***files, int *num_files) {
    if (argc < 2) return -1;

    *num_files = argc - 1; // number of files without program name

    // allocate array of pointers to files strings
    *files = malloc(sizeof(char *) * (*num_files));
    for (int i = 0; i < *num_files; i++) {
        (*files)[i] = argv[i + 1]; // copy pointers to strings from argv
    }

    return 0;
}

void cleanup_files(char **files) {
    if (!files) return;

    free(files);
}