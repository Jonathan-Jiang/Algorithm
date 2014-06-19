#include <iostream>
using	namespace	std;

int main() {
	int c, n, tower[ 100 ][ 100 ];
	cin >> c;
	while ( c-- ) {
		cin >> n;
		for ( int i = 0; i < n; ++i ) {
			for ( int j = 0; j <=i; ++j ) {
				cin >> tower[ i ][ j ];
			}
		}
		for ( i = n - 2; i >= 0; --i ) {
			for ( int j = 0; j <= i; ++j ) {
				tower[ i ][ j ] += tower[ i + 1 ][ j ] > tower[ i + 1 ][ j + 1 ] ? \
					tower[ i + 1 ][ j ] : tower[ i + 1 ][ j + 1 ];
			}
		}

		cout << tower[ 0 ][ 0 ] << endl;
	}

	return 0;
}
