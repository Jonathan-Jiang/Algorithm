#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>
using	namespace	std;

const int INF = ~ (1 << (sizeof(int) * 8 - 1));

const double e = 2.718281828;
const double r = 0.9;
const int N = 31;

typedef struct point {
    int x;
    int y;
} city;

const city citys[N] = {
    { 13.04, 23.12 }, { 36.39, 13.15 }, { 41.77, 22.44 }, { 37.12, 13.99 },
	{ 34.88, 15.35 }, { 33.26, 15.56 }, { 32.38, 12.29 }, { 41.96, 10.04 },
	{ 43.12, 79.0  }, { 43.86, 5.70  }, { 30.07, 19.70 }, { 25.62, 17.56 },
	{ 27.88, 14.91 }, { 23.81, 16.76 }, { 13.32, 6.95  }, { 37.15, 16.78 }, 
	{ 39.18, 21.79 }, { 40.61, 23.70 }, { 37.80, 22.12 }, { 36.76, 25.78 },
	{ 40.29, 28.38 }, { 42.63, 29.31 }, { 34.29, 19.08 }, { 35.07, 23.67 },
	{ 33.94, 26.43 }, { 34.39, 32.01 }, { 29.35, 32.40 }, { 31.40, 35.50 },
	{ 25.45, 23.57 }, { 27.78, 28.26 }, { 23.70, 29.75 },
};

int
main(void) {
	int path[N];
	for (int i = 0; i < N; ++i) {
		path[i] = i;
	}

	double T = 100.0;
	double T_min = 0;
	double lastL = INF;
	double L = 0.0;
	srand((unsigned)time(NULL));
	do {
		for (int i = 0; i < N - 1; ++i) {
			double d = sqrt(pow((citys[path[i]].x - citys[path[i + 1]].x), 2) + pow((citys[path[i]].y - citys[path[i + 1]].y), 2));
			L += d;
		}
		L += sqrt(pow((citys[path[N - 1]].x - citys[path[0]].x), 2) + pow((citys[path[N - 1]].y - citys[path[0]].y), 2));

		double dE = lastL - L;
		if (dE >= 0) {
			lastL = L;
		} else {
			double p = rand() % 101;
			p /= 100;
			if (pow(e, dE / T) >= p) {
				lastL = L;
			}
		}
		T *= r;
	} while (next_permutation(path, path + 4) && (T - T_min) > 0);

	cout << lastL << endl;

	return 0;
}
