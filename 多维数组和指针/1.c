#include <stdio.h>

char ga[] = "abcdefg";

void my_array_func(char ca[10]) {
    // 当数组作为形参传进来的时候
    // 数组就已经退化成为指针
    // 编译器的符号表具有一个 ca
    // ca 的地址假设为 4624
    // 则，4624 这个地址中中存放的内容，实际上就是数组的起始地址
    printf("ca = %#x\n", ca);

    printf("&ca = %#x\n", &ca);

    printf("&(ca[0] = %#x\n", &(ca[0]));
    printf("&(ca[1]) = %#x\n", &(ca[1]));
    printf("++ca = %#x\n\n", ++ca);
}

void my_pointer_func(char*  pa) {
    printf("%#x\n", &(*pa));

    printf("%#x\n", &pa);
    printf("%#x\n", &(pa[0]));
    printf("%#x\n", &(pa[1]));
    printf("%#x\n\n", ++pa);
}

void print(int argc, char*  argv[]) {
    int i = 0;
    for (i = 0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }
}

void xxx(int argc, char (* p)[]) {
    int i;
    for (i = 0; i < argc; ++i) {
        printf("%s\n", *p);
        p += sizeof(char) * 5;
    }
}

int main() {
    char*  p[] = {
        "hello",
        "world",
        "kitty"
    };

    char k[][5] = {
        "xxx",
        "y",
        "zz"
    };
    char (*xp)[] = &k[0];
    xxx(3, xp);

    printf("%#x\n", ga);

    printf("%#x\n", &ga);
    printf("%#x\n", &(ga[0]));
    printf("%#x\n\n", &(ga[1]));

    my_array_func(ga);
    my_pointer_func(ga);

    print(3, p);
    
    return 0;
}
