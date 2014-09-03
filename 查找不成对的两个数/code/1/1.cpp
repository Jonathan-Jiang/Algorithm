#include <iostream>
using    namespace    std;

int a[12] = {
    1, 1, 2, 3, 4, 4, 5, 5, 6, 6, 7, 7,
};

int getBit(int b) {
	for (int i = 0; i < sizeof(int); ++i) {
		if (b & (1 << i) != 0) return i;
	}
}

int
main(void) {
    int x = a[0];
    for (int i = 1; i < 12; ++i)   {
        x ^= a[i];
    }

	int bit = getBit(x);

	bool first = true;
	int tmp;
	for (i = 0; i < 12; ++i) {
		if (a[i] & (1 << bit) != 0) {
			if (first) tmp = a[i];
		} else {
			first = false;
			tmp ^= a[i];
		}
	}
	cout << tmp << endl;
	cout << (tmp ^ x) << endl;

    return 0;
}
