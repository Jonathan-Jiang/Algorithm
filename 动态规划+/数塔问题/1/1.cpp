#include <iostream>
using	namespace	std;

int main() {
	int c, n, tower[100][100];
	cin >> c;
	while (c--) {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				cin >> tower[i][j];
			}
		}
		for (i = 1; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				if (j == 0) {
					tower[i][j] += tower[i - 1][j];
				} else if (j == i) {
					tower[i][j] += tower[i - 1][j - 1];
				}else {
					tower[i][j] += tower[i - 1][j] > tower[i - 1][j - 1] ? \
						tower[i - 1][j] : tower[i - 1][j - 1];
				}
			}
		}
		int max = tower[n - 1][0];
		for (i = 1; i < n; ++i) {
			if (tower[n - 1][i] > max) {
				max = tower[n - 1][i];
			}
		}
		cout << max << endl;
	}

	return 0;
}
