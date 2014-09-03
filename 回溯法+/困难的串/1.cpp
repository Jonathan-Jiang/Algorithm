#include <iostream>
using    namespace    std;

bool is_difficult(int* already, int last_index) {
    for (int len = 1; 2 * len <= last_index + 1; ++len) {
        bool is_easy = true;
        for (int i = 0; i < len; ++i) {
            if (already[last_index - i] != already[last_index - len - i]) {
                is_easy = false;
				break;
			}
        }
        if (is_easy) return false;
    }
    return true;
}

int dfs(int* already, int cur, int order, int n, int L) {
    if (order == n) {
        for (int i = 0; i < cur; ++i)
            cout << char(already[i] + 'A') << " ";
        cout << endl;
		return 0;
    }

    for (int i = 0; i < L; ++i) {
        already[cur] = i;
        if (is_difficult(already, cur))
            if(!dfs(already, cur + 1, order + 1, n, L))
				return 0;
    }
	return 1;
}

int main(int argc, char* const argv[]) {
	int already[32];
    while (true) {
        int n, L;
        cin >> n >> L;
        dfs(already, 0, 0, n, L);
    }

    return 0;
}
