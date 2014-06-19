//
// 构造全排列
//

#include <iostream>
using	namespace	std;

const int MAXSIZE = 5;
const int vect[ MAXSIZE ] = { 1, 2, 3, 4, 5 };

void shengcheng( int * already, int cur ) {
	int i = 0, j = 0;
	if ( cur == MAXSIZE ) {
		for ( i = 0; i < MAXSIZE; ++i ) {
			cout << already[ i ];
		}
		cout << endl;
		return;
	} else {
		for ( i = 0; i < MAXSIZE; ++i ) {
			bool in = false;
			for ( j = 0; j < cur; ++j ) {
				if ( vect[ i ] == already[ j ] ) {
					in = !in;
				}
			}
			if ( !in ) {
				already[ cur ] = vect[ i ];
				shengcheng( already, cur + 1 );
			}
		}
	}
}

int main() {
	int already[ MAXSIZE ];

	shengcheng( already, 0 );
	return 0;
}
