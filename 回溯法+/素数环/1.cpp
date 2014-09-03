#include <iostream>
using    namespace    std;

bool is_prime(int n) {
    if (n == 2) return true;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

void dfs(int* already, int cur, int n, bool* isp) {
    if (cur == n && isp[already[0] + already[n - 1]]) {
        for (int i = 0; i < n; ++i)
            cout << already[i] << " ";
        cout << endl;
    }

    for (int i = 1; i <= n; ++i) {
        bool ok = true;
        for (int j = 0; j < cur; ++j) {
            if (i == already[j]) {
                ok = false;
                break;
            }
        }
        if (ok && isp[already[cur - 1] + i]) {
            already[cur] = i;
            dfs(already, cur + 1, n, isp);
        }
    }
}

int main(int argc, char* const argv[]) {
    bool isp[32];
	int already[32];
	already[0] = 1;
    for (int i = 2; i <= 32; ++i)
        isp[i] = is_prime(i);
    while (true) {
        int n;
        cin >> n;
        dfs(already, 1, n, isp);
    }

    return 0;
}
