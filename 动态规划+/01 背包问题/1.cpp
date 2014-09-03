#include <iostream>
using	namespace	std;

// �� 4 ����Ʒ
const int cnt = 4;
// ������ 5 ����λ�ݻ�
const int h = 5;
const int weight[cnt] = { 2, 1, 3, 2 };
const int value[cnt] = { 12, 10, 20, 15 };

// v(i, j) ��ʾ���� i ����Ʒ��������Ϊ j �ı��������ܻ�õ�����ֵ
// ��
// v(i, j) = v(i - 1, j)						if (w(i) > j)
// 			 = v(i - 1, j - w(i)) + v(i)		if (w(i) < j)
int v[cnt + 1][h + 1];

struct point {
	int i;
	int j;
	int max;

	point() {
		i = j = max = 0;
	}
};

point r_p;

int max(int x, int y) {
	return x > y ? x : y;
}

void _01_back() {
	memset(v, 0, sizeof(v));

	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; j <= h; ++j) {
			// �����ǰ��Ʒ��������������
			if (weight[i - 1] > j) v[i][j] = v[i - 1][j];
			else {
				v[i][j] = max(v[i - 1][j - weight[i - 1]] + value[i - 1], v[i - 1][j]);
				if (v[i][j] > r_p.max) {
					r_p.max = v[i][j];
					r_p.i = i;
					r_p.j = j;
				}
			}
		}
	}
}

int main(int argc, const char* argv[]) {
	_01_back();

	cout << "max: " << r_p.max << endl;

	int _y = r_p.i;
	int _x = r_p.j;
	int remain = h;
	while (_y >= 0 && remain >= 0) {
		if (v[_y][_x] != v[_y - 1][_x]) {
			printf("%d-th is in\n", _y);
			remain -= weight[_y - 1];
		}

		int k = v[_y][_x] - value[_y - 1];
		for (int i = 1; i <= cnt; ++i) {
			if (v[_y - 1][i] == k) {
				--_y;
				_x = i;
			}
		}
	}

// #define DEBUG
#ifdef DEBUG
	for (int i = 0; i < cnt + 1; ++i) {
		for (int j = 0; j < h + 1; ++j) {
			cout << v[i][j] << "  ";
			if (j == h) {
				cout << endl;
			}
		}
	}
#endif

	return 0;
}
