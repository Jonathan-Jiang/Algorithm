#include <iostream>
#include <algorithm>
using	namespace	std;

const int MAXSIZE = 3;
int vect[MAXSIZE] = { 1, 2, 3 };


void sub_set( int *bit, int cur ) {
	if (cur == MAXSIZE) {
		for ( int i = 0; i < cur; ++i )
			if (bit[i]) cout << vect[ i ];
		cout << endl;
		return;
	}

	bit[cur] = 1;
	sub_set(bit, cur + 1);
	bit[cur] = 0;
	sub_set(bit, cur + 1);
}

int main() {
	int bit[MAXSIZE];
	memset(bit, 0, sizeof(bit));

	sub_set( bit, 0 );
	return 0;
}
