#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include "../include/allocator.h"

void test_malloc_int_array(void) {
    int *arr = arena_malloc(10 * sizeof(int));
    CU_ASSERT_PTR_NOT_NULL(arr);

    for (int i = 0; i < 10; i++)
        arr[i] = i * 2;

    for (int i = 0; i < 10; i++)
        CU_ASSERT_EQUAL(arr[i], i * 2);

    arena_free(arr);
}

void test_malloc_char_array(void) {
    char *s = arena_malloc(20);
    CU_ASSERT_PTR_NOT_NULL(s);

    for (int i = 0; i < 19; i++)
        s[i] = 'a' + i % 26;
    s[19] = 0;

    for (int i = 0; i < 19; i++)
        CU_ASSERT_EQUAL(s[i], 'a' + i % 26);
    CU_ASSERT_EQUAL(s[19], 0);

    arena_free(s);
}

void test_malloc_small_int_array(void) {
    int *b = arena_malloc(5 * sizeof(int));
    CU_ASSERT_PTR_NOT_NULL(b);

    for (int i = 0; i < 5; i++)
        b[i] = i + 100;

    for (int i = 0; i < 5; i++)
        CU_ASSERT_EQUAL(b[i], i + 100);

    arena_free(b);
}

int main(void) {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("arena_malloc_suite", NULL, NULL);

    CU_add_test(suite, "malloc int array", test_malloc_int_array);
    CU_add_test(suite, "malloc char array", test_malloc_char_array);
    CU_add_test(suite, "malloc small int array", test_malloc_small_int_array);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failures = CU_get_number_of_tests_failed();
    CU_cleanup_registry();

    return (failures > 0) ? 1 : 0;
}
