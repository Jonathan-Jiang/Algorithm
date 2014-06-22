#include <iostream>
#include <algorithm>
using	namespace	std;

const int MAXSIZE = 3;
int vect[MAXSIZE] = { 1, 2, 3 };

void print_subset(int bit) {
	for (int i = 0; i < MAXSIZE; ++i)
		if (bit & (1 << i)) cout << vect[i] << " ";
	cout << endl;
}

int main() {
	for (int bit = 0; bit < (1 << MAXSIZE); ++bit)
		print_subset(bit);

	return 0;
}
