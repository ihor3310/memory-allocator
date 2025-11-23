#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include "allocator.h"

void test_calloc_normal(void) {
    size_t nmemb = 10, size = 4;
    void *ptr = arena_calloc(nmemb, size);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    if (ptr) {
        unsigned char *data = (unsigned char*)ptr;
        for (size_t i = 0; i < nmemb * size; i++)
            CU_ASSERT_EQUAL(data[i], 0);
    }
    arena_free(ptr);
}

void test_calloc_zero_nmemb(void) {
    void *ptr = arena_calloc(0, 4);
    CU_ASSERT_PTR_NULL(ptr);
}

void test_calloc_zero_size(void) {
    void *ptr = arena_calloc(10, 0);
    CU_ASSERT_PTR_NULL(ptr);
}

void test_calloc_overflow(void) {
    size_t nmemb = SIZE_MAX;
    size_t size = 2;
    void *ptr = arena_calloc(nmemb, size);
    CU_ASSERT_PTR_NULL(ptr);
}

int main(void) {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("arena_calloc_suite", NULL, NULL);

    CU_add_test(suite, "calloc normal", test_calloc_normal);
    CU_add_test(suite, "calloc zero nmemb", test_calloc_zero_nmemb);
    CU_add_test(suite, "calloc zero size", test_calloc_zero_size);
    CU_add_test(suite, "calloc overflow", test_calloc_overflow);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failures = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return (failures > 0) ? 1 : 0;
}
