#include <iostream>
#include <algorithm>
using	namespace	std;

const int INF = ~(1 << (sizeof(int) * 8) - 1);

int get_band_width(int* already, int n) {
    int* bitmap = new int[n];
    for (int i = 0; i < n; ++i)
        bitmap[already[i]] = i;
    int max = 0;
    for (i = 0; i < n; ++i) {
        int d1 = abs(bitmap[i] - bitmap[(i + 1) % n]);
        int d2 = abs(bitmap[i] - bitmap[(i - 1 + n) % n]);
        if (d1 > max) max = d1;
        if (d2 > max) max = d2;
    }
    delete[] bitmap;
    return max;
}

int get_distance(int* already, int cur, int i, int n) {
	int dis = 0, pre = (i - 1 + n) % n, next = (i + 1) % n;
	for (int idx = 0; idx < cur; ++idx)
		if (already[idx] == pre || already[idx] == next)
			if (abs(cur - idx) > dis)
				dis = abs(cur - idx);
	return dis;
}

int get_min_possible_band_width(int* already, int cur, int n) {
    int* bitmap = new int[n];
    memset(bitmap, 0, sizeof(int) * n);
    for (int i = 0; i < cur; ++i)
        bitmap[already[i]] = 1;
    int len = 0, m1 = 0, m2 = 0;
    for (i = cur - 1; i >= 0; --i)
        if (!bitmap[i]) ++m1;
        else break;
    for (i = cur + 1; i < n; ++i)
        if (!bitmap[i]) ++m2;
        else break;
    delete[] bitmap;
    if (m1 > m2) len = m1;
    else len = m2;
    return len;
}

int cur_min = INF;
int result[32];
void dfs(int* already, int cur, int n) {
    if (cur == n) {
        int band_width = get_band_width(already, n);
        if (band_width < cur_min) {
            cur_min = band_width;
            memcpy(result, already, n * sizeof(int));
        }
        return;
    }
    for (int i = 0; i < n; ++i) {
        bool ok = true;
		for (int j = 0; j < cur; ++j) {
            if (already[j] == i) {
                ok = false;
                break;
            }
        }
        if (ok) {
            already[cur] = i;
            // 剪枝
			int dis = get_distance(already, cur, i, n);
            int m = get_min_possible_band_width(already, cur, n);
			if (dis >= cur_min || m >= cur_min) return;
            else dfs(already, cur + 1, n);
        }
    }
}
int main() {
    int already[32];
    while (true) {
		int n;
		cur_min = INF;
        cin >> n;
        dfs(already, 0, n);
		cout << "****************" << endl;
        cout << cur_min << endl;
		for (int i = 0; i < n; ++i)
			cout << result[i] << " ";
		cout << endl;
		cout << "****************" << endl << endl;
    }

    return 0;
}
