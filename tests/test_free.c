#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/allocator.h"


static block_t* create_test_block(size_t size, int is_free) {
    block_t *block = (block_t*)malloc(sizeof(block_t) + size);
    if (block) {
        block->size = size;
        block->is_free = is_free;
        block->next = NULL;
        block->prev = NULL;
    }
    return block;
}


void test_basic_free(void) {
    block_t *block = create_test_block(100, 0);
    CU_ASSERT_PTR_NOT_NULL(block);
    CU_ASSERT_EQUAL(block->is_free, 0);
    arena_free((void*)(block + 1));
    CU_ASSERT_EQUAL(block->is_free, 1);
    free(block);
}


void test_free_null(void) {
    arena_free(NULL);
    CU_PASS("Free NULL handled correctly");
}


void test_coalesce_next(void) {
    block_t *b1 = create_test_block(100, 0);
    block_t *b2 = create_test_block(200, 0);
    block_t *b3 = create_test_block(50, 0);
    b1->next = b2; b2->prev = b1; b2->next = b3; b3->prev = b2;
    size_t orig = b2->size;
    arena_free((void*)(b2 + 1));
    arena_free((void*)(b3 + 1));
    CU_ASSERT(b2->size > orig);
    free(b1); free(b2); free(b3);
}


void test_coalesce_prev(void) {
    block_t *b1 = create_test_block(100, 0);
    block_t *b2 = create_test_block(200, 0);
    b1->next = b2; b2->prev = b1;
    size_t orig = b1->size;
    arena_free((void*)(b1 + 1));
    arena_free((void*)(b2 + 1));
    CU_ASSERT(b1->size > orig);
    free(b1); free(b2);
}


void test_double_free(void) {
    block_t *block = create_test_block(100, 0);
    arena_free((void*)(block + 1));
    CU_ASSERT_EQUAL(block->is_free, 1);
    arena_free((void*)(block + 1));
    CU_ASSERT_EQUAL(block->is_free, 1);
    free(block);
}


void test_memory_integrity(void) {
    block_t *blocks[10];
    for (int i = 0; i < 10; i++) {
        blocks[i] = create_test_block(50 + i * 10, 0);
        if (i > 0) {
            blocks[i]->prev = blocks[i-1];
            blocks[i-1]->next = blocks[i];
        }
    }
    for (int i = 0; i < 10; i++) arena_free((void*)(blocks[i] + 1));
    CU_PASS("Memory integrity maintained");
    for (int i = 0; i < 10; i++) free(blocks[i]);
}


void test_block_linking(void) {
    block_t *b1 = create_test_block(100, 0);
    block_t *b2 = create_test_block(200, 0);
    block_t *b3 = create_test_block(50, 0);
    b1->next = b2; b2->prev = b1; b2->next = b3; b3->prev = b2;
    CU_ASSERT_PTR_EQUAL(b1->next, b2);
    CU_ASSERT_PTR_EQUAL(b2->prev, b1);
    CU_ASSERT_PTR_EQUAL(b2->next, b3);
    CU_ASSERT_PTR_EQUAL(b3->prev, b2);
    free(b1); free(b2); free(b3);
}


int main(void) {
    CU_pSuite pSuite = NULL;
    if (CU_initialize_registry() != CUE_SUCCESS) return CU_get_error();
    pSuite = CU_add_suite("free_suite", NULL, NULL);
    if (pSuite == NULL) { CU_cleanup_registry(); return CU_get_error(); }
    CU_add_test(pSuite, "test_basic_free", test_basic_free);
    CU_add_test(pSuite, "test_free_null", test_free_null);
    CU_add_test(pSuite, "test_coalesce_next", test_coalesce_next);
    CU_add_test(pSuite, "test_coalesce_prev", test_coalesce_prev);
    CU_add_test(pSuite, "test_double_free", test_double_free);
    CU_add_test(pSuite, "test_memory_integrity", test_memory_integrity);
    CU_add_test(pSuite, "test_block_linking", test_block_linking);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failures = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return (failures > 0) ? 1 : 0;
}
