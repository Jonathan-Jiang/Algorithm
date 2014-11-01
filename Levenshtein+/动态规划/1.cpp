#include <iostream>
#include <algorithm>
using	namespace	std;

int min(int a, int b, int c) {
	int t[] = {a, b, c};
	sort(t, t + 3);
	return t[0];
}

int func(char *s, int n, char *t, int m) {
	if (n == 0) return m;
	if (m == 0) return n;

    int *v0 = new int[m + 1];
    int *v1 = new int[m + 1];
    for (int i = 0; i < m + 1; ++i) {
        v0[i] = i;
    }

    for (i = 0; i < n; ++i) {
		v1[0] = i + 1;
        for (int j = 0; j < m; ++j) {
            int cost = (s[i] != t[j]);
            v1[j + 1] = min(v1[j] + 1,
                    v0[j + 1] + 1,
                    v0[j] + cost);
        }
		memcpy(v0, v1, sizeof(int) * (m + 1));
    }
    return v1[m];
}

int main() {
	int n = strlen("GUMBO");
	int m = strlen("GAMBOL");
	cout << func("GUMBO", n, "GAMBOL", m) << endl;
	
	return 0;
}
