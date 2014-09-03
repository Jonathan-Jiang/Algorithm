#include <iostream>
using	namespace	std;

const int size = 10;
const char src[size] = "zxyxyz";
const char dst[size] = "xyyzx";

inline int max(int x, int y) {
	return x > y ? x : y;
}

// 递归实现
int lcs(const char src[], const char dst[]) {
	if (src[0] && dst[0])
		if (src[0] == dst[0]) return lcs(src + 1, dst + 1) + 1;
		else return max(lcs(src + 1, dst), lcs(src, dst + 1));
	else return 0;
}

// 非递归实现
struct point {
	int max;
	int i;
	int j;

	point() {
		max = i = j = 0;
	}
};
point max_point;

int graph[size][size];
void lcs(void) {
	for (int i = 0; i < size; ++i) {
		graph[0][i] = 0;
		graph[i][0] = 0;
	}

	for (i = 1; i <= strlen(dst); ++i) {
		for (int j = 1; j <= strlen(src); ++j) {
			if (src[j - 1] == dst[i - 1]) graph[i][j] = graph[i - 1][j - 1] + 1;
			else graph[i][j] = max(graph[i - 1][j], graph[i][j - 1]);

			if (graph[i][j] > max_point.max) {
				max_point.max = graph[i][j];
				max_point.i = i;
				max_point.j = j;
			}
		}
	}
}

int main(int argc, const char* argv[]) {
//	cout << lcs(src, dst) << endl;

	lcs();

#define DEBUG

#ifdef DEBUG
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << graph[i][j] << "   ";
			if (j == size - 1) cout << endl;
		}
	}
#endif

	// 找最长序列
	int _x = max_point.j;
	int _y = max_point.i;
	while (_x >= 0 && _y >= 0) {
		if (src[_x - 1] == dst[_y - 1]) {
			cout << src[_x - 1] << "  ";
			--_x;
			--_y;
		} else {
			if (graph[_y][_x - 1] == graph[_y][_x])
				--_x;
			else
				--_y;
		}
	}

	cout << endl;


	return 0x00;
}
