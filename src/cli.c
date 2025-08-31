#include "cli.h"
#include "io.h"

#include <stdlib.h>
#include <stdio.h>
#include "argparse.h"

static const char *const usage[] = {
    "peek [options] [files...]",
    NULL
};

void parse_args(int argc, const char *argv[], Args *args) {
    // init struct
    args->show_line_numbers = 0;
    args->separator = NULL;
    args->num_files = 0;

    // options list
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_BOOLEAN('n', "number", &args->show_line_numbers, "show line numbers", NULL, 0, 0),
        OPT_STRING('s', "sep", &args->separator, "set output separator", NULL, 0, 0),
        OPT_END()
    };

    // create parser
    struct argparse parser;
    argparse_init(&parser, options, usage, 0);
    argparse_describe(&parser, "peek is a simple cat-like utility.\n", NULL);

    // parse args
    argc = argparse_parse(&parser, argc, argv);
    args->num_files = argc;

    // allocate array of pointers to files strings
    args->files = malloc(sizeof(char *) * argc);
    for (int i = 0; i < argc; i++) {
        args->files[i] = argv[i]; // copy pointers to **files from argv
    }
}

int validate_file(const char *filename) {
    int exists = file_exists(filename);
    if (!exists) {
        fprintf(stderr, "File: '%s' does not exist\n", filename);
        return 0;
    }
    if (exists && is_dir(filename)) {
        fprintf(stderr, "'%s': Is a directory\n", filename);
        return 0;
    }
    return 1;
}

void process_files(Args *args) {
    for (int i = 0; i < args->num_files; i++) {
        const char *filename = args->files[i];
        if (!validate_file(filename)) continue;

        if (args->show_line_numbers) {
            io_print_file_numbered(filename);
        } else if (args->separator) {
            io_print_file_with_separator(filename, args->separator);
        } else {
            io_print_file(filename);
        }
    }
}

void cleanup_files(const char **files) {
    if (!files) return;

    free(files);
}