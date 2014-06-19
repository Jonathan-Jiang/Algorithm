#include <iostream>
using	namespace	std;

const int cnt = 5;
// A1 A2 A3 A4 A5
// 30 * 15
// 15 * 25
// 25 * 5
// 5 * 10
// 10 * 20
// p0 p1 p2 p3 p4 p5
int p[ cnt + 1 ] = { 30, 15, 25, 5, 10, 20 };

// 递归实现
int less( int i, int j ) {
	if ( i == j ) return 0;
	int min = less( i, i ) + less( i + 1, j ) + p[ i - 1 ] * p[ i ] * p[ j ];
	for ( int k = i + 1; k < j; ++k ) {
		int t = less( i, k ) + less( k + 1, j ) + p[ i - 1 ] * p[ k ] * p[ j ];
		if ( min > t ) min = t;
	}
	return min;
}

// 非递归实现
int v[ cnt + 1 ][ cnt + 1 ];
// 通过 kmap 可以找出计算顺序
int kmap[ cnt + 1 ][ cnt + 1 ];
void less() {
	memset( v, 0, sizeof( v ) );
	memset( kmap, 0, sizeof( kmap ) );
	
	for ( int i = cnt; i >= 1; --i ) {
		for ( int j = 1; j <= cnt; ++j ) {
			if ( i >= j ) v[ i ][ j ] = 0;
			else {
				v[ i ][ j ] = v[ i ][ i ] + v[ i + 1 ][ j ] + p[ i - 1 ] * p[ i ] * p[ j ];
				kmap[ i ][ j ] = i;
				for ( int k = i + 1; k < j; ++k ) {
					int t = v[ i ][ k ] + v[ k + 1 ][ j ] + p[ i - 1 ] * p[ k ] * p[ j ];
					if ( v[ i ][ j ] > t ) {
						v[ i ][ j ] = t;
						kmap[ i ][ j ] = k;
					}
				}
			}
		}
	}
}

// print order
void DPMatrixChain( int i, int j, int s[ ][ cnt + 1 ] ) {
	if ( i != j ) {
		DPMatrixChain( i, s[ i ][ j ], s );
		DPMatrixChain( s[ i ][ j ] + 1, j, s );
		printf( "A[ %d : %d ]: broken: A[ %d : %d ] and A[ %d : %d ]\n", i, j, i, s[ i ][ j ], s[ i ][ j ] + 1, j );
	}
}

int main( int argc, const char *argv[] ) {
	// cout << less( 1, 5 ) << endl;
	less();
	cout << v[ 1 ][ cnt ] << endl;

#define DEBUG
#ifdef DEBUG
	for ( int i = 1; i <= cnt; ++i ) {
		for ( int j = 1; j <= cnt; ++j ) {
			cout << v[ i ][ j ] << "\t";
			if ( j == cnt ) cout << endl;
		}
	}

	cout << endl;

	for ( i = 1; i <= cnt; ++i ) {
		for ( int j = 1; j <= cnt; ++j ) {
			cout << kmap[ i ][ j ] << "\t";
			if ( j == cnt ) cout << endl;
		}
	}
#endif

	DPMatrixChain( 1, 5, kmap );

	return 0;
}
