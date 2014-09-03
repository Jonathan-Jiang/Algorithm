//
// 手工模拟计算 n 的阶乘
//

#include <iostream>
#include <stdlib.h>
using	namespace	std;

const int MAXSIZE = 100000;
int result[MAXSIZE];

int main() {
	int i = 0, j = 0;
	int n = 0;
	while (scanf("%d", &n) != EOF) {

		memset(result, 0, sizeof(result));
		result[0] = 1;

		int valid = 1;
		for (i = 2; i <= n; ++i) {
			int carry = 0;
			for (j = 0; j < valid; ++j) {
				int temp = result[j] * i + carry;
				result[j] = temp % 10;
				carry = temp / 10;
			}

			while (carry != 0) {
				result[valid++] = carry % 10;
				carry /= 10;
			}
		}

		for (j = 0; j < valid; ++j) {
			if (result[j] != 0) {
				cout << result[j] << endl;
				break;
			}
		}
	}

	return 0;
}
