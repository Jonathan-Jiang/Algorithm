#include <iostream>
#include <algorithm>
using	namespace	std;

int index_of(int e, int* elements, int n) {
	for (int i = 0; i < n; ++i)
		if (elements[i] == e) return i;
	return 0;
}

void sub_set(int* already, int* elements, int cur, int n) {
    for (int i = 0; i < cur; ++i)
        cout << already[i];
    cout << endl;
	int s = cur ? index_of(already[cur - 1], elements, n) : 0;
    for (int j = s; j < n; ++j) {
        bool ok = true;
        for (int i = 0; i < cur; ++i)
            if (elements[j] == already[i])
                ok = false;
        if (ok) {
            already[cur] = elements[j];
            sub_set(already, elements, cur + 1, n);
        }
    }
}
int main() {
	const int MAXSIZE = 3;
	int elements[MAXSIZE] = {1, 2, 3};
	sort(elements, elements + 3);
    int already[MAXSIZE];
    sub_set(already, elements, 0, MAXSIZE);
    return 0;
}
