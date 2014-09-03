#include <iostream>
using    namespace    std;

#define MAX_CHAR    256
#define SIZE        256
#define MAX(x, y)   (x) > (y) ? (x) : (y)

void boyer_moore(char* pattern, int m, char* text, int n);

int main(int argc, char* const argv[]) {
    char text[MAX_CHAR], pattern[MAX_CHAR];

    while (true) {
        scanf("%s%s", text, pattern);
        if (text == 0 || pattern == 0) break;

        boyer_moore(pattern, strlen(pattern), text, strlen(text));
        printf("\n");
    }

    return 0;
}

void print(int* array, int n, char* array_name) {
    printf("%s: ", array_name);
    for (int i = 0; i < n; ++i) {
        printf("%d", array[i]);
    }
    printf("\n");
}

void get_suffix_old(char* pattern, int m, int suff[]) {
    suff[m - 1] = m;
    for (int i = m - 2; i >= 0; --i) {
        int j = i;
        while (j >= 0 && pattern[j] == pattern[m - 1 - i + j]) 
            --j;

        suff[i] = i - j;
    }
}

void get_suffix(char* pattern, int m, int suff[]) {
    int f, g;
    suff[m - 1] = m;
    g = m - 1;
    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 -f];
        else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

void get_step_bad_character(char* pattern, int m, int step_bc[]) {
    for (int i = 0; i < MAX_CHAR; ++i) {
        step_bc[i] = m;
    }
    for (i = 0; i < m - 1; ++i) {
        step_bc[pattern[i]] = m - 1 - i;
    }
}

void get_step_good_suffix(char* pattern, int m, int step_gs[]) {
    int suff[SIZE];

    // 计算后缀数组
    get_suffix(pattern, m, suff);

    // 先全部赋值为 m，包含 case 3
    for (int i = 0; i < m; ++i) {
        step_gs[i] = m;
    }

    // case 2
    for (i = m - 1; i >= 0; --i) {
        if (suff[i] == i + 1) {
            for (int j = 0; j < m - 1 - i; ++j)
                if (step_gs[j] == m) step_gs[j] = m - 1 - i;
        }
    }

    // case 1
    for (i = 0; i <= m - 2; ++i)
        step_gs[m - 1 - suff[i]] = m - 1 - i;
}

void boyer_moore(char* pattern, int m, char* text, int n) {
	int step_bc[MAX_CHAR], step_gs[MAX_CHAR];
	get_step_bad_character(pattern, m, step_bc);
	get_step_good_suffix(pattern, m, step_gs);

	int j = 0;
	while (j <= n - m) {
		for (int i = m - 1; i >= 0 && pattern[i] == text[i + j]; --i);
		if (i < 0) {
			printf("Find it, the position is %d\n", j);
			j += step_gs[0];
			return;
		} else
			j += MAX(step_bc[text[i + j]] - m + 1 + i, step_gs[i]);
	}
	printf("No Find.\n");
}