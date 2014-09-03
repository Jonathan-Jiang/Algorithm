#include <stdio.h>
#include <stdlib.h>

int (*paf())[20];

int (*paf())[20] {
    int i = 0;
    int (*pear)[20];
    pear = calloc(20, sizeof(int));
    for (i = 0; i < 20; ++i) {
        (*pear)[i] = i;
    }
    return pear;
}

int main(int argc, const char* argv[]) {
    int i = 0;
    int (*result)[20];
    result = paf();
    for (i = 0; i < 20; ++i) {
        printf("%d\t", (*result)[i]);
    }
    printf("\n");

    return 0;
}
