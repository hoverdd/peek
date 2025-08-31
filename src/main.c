#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "cli.h"

int main(int argc, const char *argv[]) {
    Args args;
    parse_args(argc, argv, &args); 

    process_files(&args);

    cleanup_files(args.files);
    return 0;
}