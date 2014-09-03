#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using	namespace	std;

int* partion(int* begin, int* end, int guard) {
	int* i = begin, *j = end - 1;
	while (i < j) {
		while (*i < guard && i < j) ++i;
		while (*j > guard && i < j) --j;
		swap(*i, *j);
	}
	return i;
}

int* get_guard(int* begin, int* end) {
	for (int* it = begin + 1; it < end; ++it) {
		if (*it > *begin) return it;
		else if (*it < *begin) return begin;
	}
	return NULL;
}

void
quick_sort(int* begin, int* end) {
	int* guard_it = get_guard(begin, end);
	if (guard_it) {
		int guard = *guard_it;
		int* k = partion(begin, end, guard);
		quick_sort(begin, k);
		quick_sort(k, end);
	}
}

void
print(int i) {
	cout << i << " ";
}

int
main(void) {
	int a[5] = {5, 2, 1, 4, 3};
	quick_sort(a, a + 5);

	for_each(a, a + 5, print);
	cout << endl;

	return 0;
}