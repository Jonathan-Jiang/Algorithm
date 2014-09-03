#include <iostream>
using    namespace    std;

class kmp {
    public:
        int indexKMP(const char* s, const char* p, const int pos = 0);
    private:
        void getNext(const char* p, int next[]);
		void getNext_IM(const char* p, int next[]);
};

int kmp::indexKMP(const char* s, const char* p, const int pos) {
    int len_s = strlen(s);
    int len_p = strlen(p);
    int* next = new int[len_p];
    // getNext(p, next);
	getNext_IM(p, next);

	for (int ii = 0; ii < len_p; ++ii) {
		cout << next[ii] << "\t";
	}
	cout << endl;

    int i = pos, j = 0;
    while (i < len_s && j < len_p) {
        if (j == -1 || s[i] == p[j]) {
            ++i; ++j;
        } else j = next[j];
    }
    if (j >= len_p) return i - len_p;
    else return 0;
}

void kmp::getNext(const char* p, int next[]) {
	int j = 0, k = -1, len_p = strlen(p);
	next[0] = -1;
	while (j < len_p) {
		if (k == -1 || p[j] == p[k]) {
			next[j + 1] = k + 1;
			++j; ++k;
		} else {
			k = next[k];
		}
	}
}

void kmp::getNext_IM(const char* p, int next[]) {
	int j = 0, k = -1, len_p = strlen(p);
	next[0] = -1;
	while (j < len_p) {
		if (k == -1 || p[j] == p[k]) {
			++j; ++k;
			if (p[j] == p[k]) {
				next[j] = next[k];
			} else {
				next[j] = k;
			}
		} else {
			k = next[k];
		}
	}
}

int main(int argc, char* const argv[]) {
	char* s1 = "acabaabaabcacaabc";
	char* p1 = "abaabcac";

	char* s2 = "aaabaaaab";
	char* p2 = "aaaab";

    kmp* pk = new kmp;
    cout << pk->indexKMP(s1, p1) << endl;
	cout << endl;
	cout << pk->indexKMP(s2, p2) << endl;

    return 0;
}
