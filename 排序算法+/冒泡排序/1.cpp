#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using    namespace    std;

const int SIZE = 10;

void
print(int x) {
	cout << x << " ";
}

template <class RandomAccessIterator, class Comp>
void
bubble_sort(RandomAccessIterator begin, RandomAccessIterator end, Comp cmp) {
    bool exchanged = false;
    for (RandomAccessIterator i = end; i > begin; --i) {
        for (RandomAccessIterator j = begin + 1; j < i; ++j) {
            if (cmp(*(j - 1), *j)) {
                swap(*(j - 1), *j);
                exchanged = true;
            }
        }
        if (!exchanged) return;
    }
}

template <class RandomAccessIterator>
void
bubble_sort(RandomAccessIterator begin, RandomAccessIterator end) {
	bubble_sort(begin, end, less<int>());
}

int main(int argc, char* const argv[]) {
    int array[SIZE] = {
        9, 6, 8, 0, 4, 2, 3, 1, 5, 7
    };
    vector<int> v(array, array + SIZE);
	
	bubble_sort(v.begin(), v.end(), greater<int>());
	for_each(v.begin(), v.end(), ptr_fun(print));
	cout << endl;

	bubble_sort(array, array + SIZE);
	for_each(array, array + SIZE, ptr_fun(print));
	cout << endl;

    return 0;
}
