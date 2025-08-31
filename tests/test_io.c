#include <check.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#include "io.h"
#include "config.h"

size_t capture_stdout_from_file(const char *filename, char *out_buffer, size_t buf_size) {
    FILE *tmp = tmpfile();
    int old_stdout = dup(STDOUT_FILENO);
    int tmp_fd = fileno(tmp);
    dup2(tmp_fd, STDOUT_FILENO);

    int err = read_and_print_file(filename); 

    fflush(stdout);
    rewind(tmp);

    size_t n = fread(out_buffer, 1, buf_size, tmp);

    // restore stdout
    dup2(old_stdout, STDOUT_FILENO);
    close(old_stdout);
    fclose(tmp);

    return n; 
}

START_TEST(test_file_exists) {
    ck_assert_int_eq(file_exists("tests/fixtures/hello.txt"), 1);
    ck_assert_int_eq(file_exists("tests/fixtures/empty.txt"), 1);
    ck_assert_int_eq(file_exists("tests/fixtures/doesnt_exist.txt"), 0);
}
END_TEST

START_TEST(test_is_dir) {
    ck_assert_int_eq(is_dir("tests"), 1);
    ck_assert_int_eq(is_dir("include"), 1);
    ck_assert_int_eq(is_dir("src"), 1);
    ck_assert_int_eq(is_dir("notdir"), 0);
}
END_TEST

START_TEST(test_read_and_print_file) {
    ck_assert_int_eq(read_and_print_file("tests/fixtures/hello.txt"), SUCCESS);
    ck_assert_int_eq(read_and_print_file("tests/fixtures/multiline.txt"), SUCCESS);
    ck_assert_int_eq(read_and_print_file("tests/fixtures/empty.txt"), SUCCESS);
    ck_assert_int_eq(read_and_print_file("tests/fixtures/bin.dat"), SUCCESS);
    ck_assert_int_eq(read_and_print_file("tests/fixtures/bin.bin"), SUCCESS);
    
}

START_TEST(test_read_and_print_binary_file) {
    char buffer[BUF_SIZE];
    size_t n = capture_stdout_from_file("tests/fixtures/bin.dat", buffer, sizeof(buffer));

    char expected[BUF_SIZE];
    FILE *bin_file = fopen("tests/fixtures/bin.dat", "rb");
    size_t expected_len = fread(expected, 1, sizeof(expected), bin_file);
    fclose(bin_file);

    ck_assert_int_eq(n, expected_len);
    ck_assert_mem_eq(buffer, expected, n);
}
END_TEST

START_TEST(test_read_and_print_text_file) {
    char buffer[BUF_SIZE];
    size_t n = capture_stdout_from_file("tests/fixtures/hello.txt", buffer, sizeof(buffer));

    char expected[BUF_SIZE];
    FILE *txt_file = fopen("tests/fixtures/hello.txt", "rb");
    size_t expected_len = fread(expected, 1, sizeof(expected), txt_file);
    fclose(txt_file);

    ck_assert_int_eq(n, expected_len);
    ck_assert_str_eq(buffer, expected);
}
END_TEST

Suite *io_suite(void) {
    Suite *s = suite_create("IO");
    TCase *tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_file_exists);
    tcase_add_test(tc_core, test_is_dir);
    tcase_add_test(tc_core, test_read_and_print_file);
    tcase_add_test(tc_core, test_read_and_print_binary_file);
    tcase_add_test(tc_core, test_read_and_print_text_file);

    suite_add_tcase(s, tc_core);
    return s;
}