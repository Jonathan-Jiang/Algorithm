// *
// * 利用全排列生成算法穷举所有的可能性
// * 打印所有 N 皇后的解
// *

#include <iostream>
using	namespace	std;

int cnt = 0;

void queen(int n, int array[], int cur) {
	if (n == cur) {
		++cnt;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < array[i]; ++j)
				printf("#");
			printf("@");
			for (j = array[i] + 1; j < n; ++j)
				printf("#");
			printf("\n");
		}
		printf("\n");

		system("pause");
	}

	for (int i = 0; i < n; ++i) {
		bool ok = true;
		for (int j = 0; j < cur; ++j) {
			if (i == array[j] || abs(cur - j) == abs(array[j] - i)) {
				ok = false;
				break;
			}
		}

		if (ok) {
			array[cur] = i;
			queen(n, array, cur + 1);
		}
	}
}

int main() {
	int array[4];
	queen(4, array, 0);
	printf("%d\n", cnt);

	return 0;
}
