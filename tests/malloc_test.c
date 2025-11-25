#include <stdio.h>
#include "../headers/malloc.h"

int main() {
    int *a = malloc(5 * sizeof(int));
    if (!a) return 1;

    for (int i = 0; i < 5; i++) a[i] = i + 1;
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");

    char *s = malloc(20);
    if (!s) return 1;

    for (int i = 0; i < 19; i++) s[i] = 'A' + (i % 26);
    s[19] = 0;

    printf("%s\n", s);

    return 0;
}
