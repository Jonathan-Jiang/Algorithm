#include <iostream>
using    namespace    std;

char cn1[10000], cn2[10000];
int n1[10000], n2[10000], result[10000];

int convert(int n[], int len, char cn[], int jinzhi) {
    int index = 0;
    for (int i = len - 1; i >= 0; --i) {
        if (cn[i] >= '0' && cn[i] <= '9')
            n[index] = cn[i] - '0';
        else n[index] = cn[i] - 'a' + 10;
		if (n[index] >= jinzhi)
			return -1;
        ++index;
    }
	return 0;
}

int main(int argc, char* const argv[]) {
    int jinzhi, i = 0, max;
    while (cin >> jinzhi >> cn1 >> cn2) {
		if (jinzhi < 2 || jinzhi > 35) {
			cout << -1 << endl;
			continue;
		}
        memset(n1, 0, sizeof(n1));
        memset(n2, 0, sizeof(n2));
        int len1 = strlen(cn1);
        int len2 = strlen(cn2);
        if (len1 > len2)
            max = len1;
        else
            max = len2;
        if (convert(n1, len1, cn1, jinzhi) == -1) {
			cout << -1 << endl;
			continue;
		}
        if (convert(n2, len2, cn2, jinzhi) == -1) {
			cout << -1 << endl;
			continue;
		}

        int sig = 0;
        for (i = 0; i < max; ++i) {
            result[i] = n1[i] + n2[i] + sig;
            if (result[i] >= jinzhi) {
                sig = 1;
                result[i] -= jinzhi;
            } else sig = 0;
        }
        if (sig == 1)
            cout << 1;

        for (i = max - 1; i >= 0; --i)
			if (result[i] >= 10)
				cout << (char)(result[i] - 10 + 'a');
			else
				cout << result[i];
        cout << endl;
    }

    return 0;
}
