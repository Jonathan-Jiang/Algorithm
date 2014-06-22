#include <iostream>
#include <algorithm>
using	namespace	std;

const int MAXSIZE = 3;
int vect[MAXSIZE] = { 1, 2, 3 };

void sub_set( int *already, int cur ) {
	for ( int i = 0; i < cur; ++i )
		cout << already[ i ];
	cout << endl;

	for (int j = 0; j < MAXSIZE; ++j) {
		bool ok = true;
		for (int i = 0; i < cur; ++i)
			if (vect[j] == already[i])
				ok = false;

		if (ok) {
			already[cur] = vect[j];
			sub_set(already, cur + 1);
		}
	}
}

int main() {
	int already[ MAXSIZE ];

	sub_set( already, 0 );
	return 0;
}
