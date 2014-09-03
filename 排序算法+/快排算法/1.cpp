//
// ¿ìÅÅ´úÂë
//

#include <iostream>
#include <assert.h>
using	namespace	std;

const int len = 8;
int n[len] = {
	49, 38, 65, 97,
	76, 13, 27, 49
};

int partion(int n[], int low, int high) {
	int cursor = n[low];

	while (low < high) {
		while (n[high] >= cursor && low < high) --high;
		n[low] = n[high];
		while (n[low] <= cursor && low < high) ++low;
		n[high] = n[low];
	}

	n[low] = cursor;
	return low;
}

void quick_sort(int n[], int low, int high) {
	if (low < high) {
		int pivotloc = partion(n, low, high);
		quick_sort(n, low, pivotloc - 1);
		quick_sort(n, pivotloc + 1, high);
	}
}

int main() {
	quick_sort(n, 0, len - 1);

	for (int i = 0; i < len; ++i) cout << n[i] << " ";
	cout << endl;

	return 0;
}
