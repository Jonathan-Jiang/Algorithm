#include <iostream>
using    namespace    std;

int a[12] = {
    1, 1, 2, 3, 4, 4, 5, 5, 6, 6, 7, 7,
};

int getBit(int b) {
	for (int i = 0; i < sizeof(int); ++i) {
		if ((b & (1 << i)) != 0) return i;
	}
}

int
main(void) {
    int x = a[0];
    for (int i = 1; i < 12; ++i)   {
        x ^= a[i];
    }

	int bit = getBit(x);

	bool first1 = true;
	bool first2 = true;
	int tmp1;
	int tmp2;
	for (i = 0; i < 12; ++i) {
		if (((a[i] >> bit) & 1) == 1) {
			if (first1) {
				tmp1 = a[i];
				first1 = false;
			} else tmp1 ^= a[i];
		} else if (((a[i] >> bit) & 1) == 0) {
			if (first2) {
				tmp2 = a[i];
				first2 = false;
			} else tmp2 ^= a[i];
		}
	}
	cout << tmp1 << endl;
	cout << tmp2 << endl;

    return 0;
}
