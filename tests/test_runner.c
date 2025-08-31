#include <check.h>

#include <stdlib.h>

Suite *io_suite(void);

int main() {
    int number_failed;
    SRunner *sr = srunner_create(io_suite());

    // srunner_add_suite(sr, suite)
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}