#include <iostream>

using namespace std;

const int N = 5;

int binary_map[N][N] = {
	0, 0, 1, 1, 0,
	0, 1, 1, 1, 1,
	1, 0, 1, 1, 1,
	0, 1, 1, 0, 1,
	0, 1, 1, 1, 1,
};

int min(int a, int b) {
	return (a < b) ? a : b;
}

// vist[i][j] 表示从(0,0) 到 (i,j) 出现的最大正方形的大小
int vist[N][N];

int main() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			vist[i][j] = 1;
		}
	}

	// 从 1 开始遍历是因为去除掉边框
	int max_s = -1;
	int ret_x = 0, ret_y = 0;
	for (i = 1; i < N; ++i) {
		for (int j = 1; j < N; ++j) {
			if (binary_map[i][j] && binary_map[i - 1][j] && binary_map[i][j - 1] && binary_map[i - 1][j - 1]) {
				vist[i][j] = min(min(vist[i - 1][j], vist[i][j - 1]), vist[i - 1][j - 1]) + 1;
			}

			if (vist[i][j] > max_s) {
				max_s = vist[i][j];
				ret_x = i;
				ret_y = j;
			}
		}
	}

	cout << max_s << " " << ret_x << " " << ret_y << endl;
	return 0;
}
