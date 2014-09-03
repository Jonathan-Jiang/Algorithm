//
// 构造全排列
//

#include <iostream>
#include <algorithm>
using	namespace	std;

const int MAXSIZE = 6;
int vect[MAXSIZE] = { 1, 2, 3, 2, 4, 5 };

void permutation(int* already, int cur) {
	int i = 0, j = 0;
	if (cur == MAXSIZE) {
		for (i = 0; i < MAXSIZE; ++i)
			cout << already[i];
		cout << endl;
		return;
	} else {
		for (i = 0; i < MAXSIZE; ++i) if (!i || vect[i] != vect[i - 1]) {
			int c1 = 0, c2 = 0;
			for (j = 0; j < cur; ++j)
				if (vect[i] == already[j]) ++c1;
			for (j = 0; j < MAXSIZE; ++j)
				if (vect[i] == vect[j]) ++c2;
			if (c1 < c2) {
				already[cur] = vect[i];
				permutation(already, cur + 1);
			}
		}
	}
}

int main() {
	int already[MAXSIZE];

	sort(vect, vect + MAXSIZE);
	permutation(already, 0);
	return 0;
}
