#include <stdio.h>
#include "../include/allocator.h"

int main() {
    int *arr = arena_malloc(10 * sizeof(int));
    for (int i=0;i<10;i++) arr[i]=i*2;
    for (int i=0;i<10;i++) printf("%d ", arr[i]);
    printf("\n");

    char *s = arena_malloc(20);
    for (int i=0;i<19;i++) s[i]='a'+i%26;
    s[19]=0;
    printf("%s\n", s);

    int *b = arena_malloc(5*sizeof(int));
    for (int i=0;i<5;i++) b[i]=i+100;
    for (int i=0;i<5;i++) printf("%d ", b[i]);
    printf("\n");

    return 0;
}
