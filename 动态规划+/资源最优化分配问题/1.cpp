#include <iostream>
using	namespace	std;

const int r_count = 4;
const int p_count = 3;

const int p[p_count][r_count + 1] = {
	0, 41, 48, 60, 66,
	0, 42, 50, 60, 66,
	0, 64, 68, 78, 78
};

inline int max(int a, int b) {
	return a > b ? a : b;
}

// 利润表
int f[p_count][r_count + 1];
// 分配表
int d[p_count][r_count + 1];

struct point {
	int max;
	int i;
	int j;

	point() {
		max = i = j = 0;
	}
};

point r_p;

int r_allocate() {
	memset(f, 0, sizeof(f));
	memset(d, 0, sizeof(d));
	for (int i = 0; i <= r_count; ++i) {
		f[0][i] = p[0][i];
		d[0][i] = i;
	}

	// i 是前 i 个工程
	// j 是资源数
	// 将 j 个资源分配给前 i 个工程
	// 最大利润等于
	// 将 k 个资源分配给第 i 个工程的利润，加上将 j - k 个资源分配给前 i - 1 个工程所得的利润
	// 即 f(j, i) = max(f(j - k, i - 1) + p[i][k]);
	// 其中, k = 0 -> j
	int i_max = 0;
	for (i = 1; i < p_count ; ++i) {
		for (int j = 1; j <= r_count; ++j) {
			for (int k = 0; k <= j; ++k) {
				if (f[i - 1][j - k] + p[i][k] > f[i][j]) {
					r_p.max = f[i][j] = f[i - 1][j - k] + p[i][k];
					r_p.i = i;
					r_p.j = j;
					d[i][j] = k;
				}
			}
		}
	}
	return i_max;
}

int main(int argc, const char* argv[]) {
	cout << r_allocate() << endl;

	int _y = r_p.i;
	int _x = r_p.j;
	int resource_remain = r_count;
	while (resource_remain >= 0 && _y >= 0) {
		int resource_gain = d[_y][_x];
		resource_remain -= resource_gain;
		printf("%d-th project gains:\t%d resource(s)\n", _y, resource_gain);

		int uplevelmax = f[_y][_x] - p[_y][resource_gain];
		--_y;
		for(int i = 0; i <= r_count; ++i) {
			if (f[_y][i] == uplevelmax) {
				_x = i;
				break;
			}
		}
	}

	return 0;
}