#include <iostream>
using    namespace    std;

int a[10] = {4, 1, 3, -2, 2, 4, 5, 4, 3, 6};

int main(int argc, char *const argv[]) {
    int n[10], pre[10];
    n[0] = 1;
    pre[0] = -1;
    int final_max = 1, final_index = 0;
    for (int i = 1; i < 10; ++i) {
        int max = 0;
        for (int j = i - 1; j >= 0; --j) {
            if (a[i] > a[j] && n[j] > max) {
				max = n[j];
                n[i] = n[j] + 1;
                pre[i] = j;
            }
        }
        if (max == 0) {
            n[i] = 1;
            pre[i] = -1;
        }
        if (max + 1 > final_max) {
            final_max = max + 1;
            final_index = i;
        }
    }
    cout << final_max << endl;
    while (final_index != -1) {
        cout << a[final_index] << " ";
        final_index = pre[final_index];
    }
    cout << endl;

    return 0;
}
