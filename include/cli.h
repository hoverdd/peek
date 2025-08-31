#ifndef CLI_H
#define CLI_H

int parse_args(int argc, char *argv[], char ***files, int *files_num);

void cleanup_files(char **files);

#endif