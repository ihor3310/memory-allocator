#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include "allocator.h"

void test_realloc_null(void) {
    void *ptr = arena_realloc(NULL, 100);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    arena_free(ptr);
}

void test_realloc_zero(void) {
    void *ptr = arena_malloc(50);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    void *res = arena_realloc(ptr, 0);
    CU_ASSERT_PTR_NULL(res);
}

void test_realloc_shrink(void) {
    void *ptr = arena_malloc(100);
    CU_ASSERT_PTR_NOT_NULL(ptr);

    block_t *block = (block_t*)ptr - 1;
    size_t old_size = block->size;

    void *res = arena_realloc(ptr, 50);
    CU_ASSERT_PTR_EQUAL(res, ptr);
    CU_ASSERT(block->size >= 50 && block->size <= old_size);

    arena_free(ptr);
}

void test_realloc_grow(void) {
    void *ptr = arena_malloc(50);
    CU_ASSERT_PTR_NOT_NULL(ptr);

    memset(ptr, 0xAB, 50);

    void *res = arena_realloc(ptr, 100);
    CU_ASSERT_PTR_NOT_NULL(res);
    if (res != NULL) {
        unsigned char *data = (unsigned char*)res;
        for (int i = 0; i < 50; i++)
            CU_ASSERT_EQUAL(data[i], 0xAB);
    }

    arena_free(res);
}

int main(void) {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("arena_realloc_suite", NULL, NULL);

    CU_add_test(suite, "realloc NULL ptr", test_realloc_null);
    CU_add_test(suite, "realloc size 0", test_realloc_zero);
    CU_add_test(suite, "realloc shrink", test_realloc_shrink);
    CU_add_test(suite, "realloc grow", test_realloc_grow);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failures = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return (failures > 0) ? 1 : 0;
}
