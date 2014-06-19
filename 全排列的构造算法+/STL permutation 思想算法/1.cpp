//
// 按照 STL next_permutation 算法思想实现的 _next_permutation 算法
// 该算法实现找出一个集合的所有字典序排列
//

#include <stdio.h>
#include <algorithm>
using	namespace	std;

void reverse( int* p, int* q ) {
	int n = q - p;
	for ( int i = 0, j = n - 1; i <= j; ++i, --j ) {
		int tmp = p[ i ];
		p[ i ] = p[ j ];
		p[ j ] = tmp;
	}
}

bool _next_permutation( int* p, int n ) {
	int i;
	for ( i = n - 2; i >= 0; --i )
		if ( p[ i ] < p[ i + 1 ] ) break;
	
	if ( i < 0 ) return false;

	int k;
	for ( k = n - 1; k > i; --k )
		if ( p[ k ] > p[ i ] ) break;

	swap( p[ i ], p[ k ] );

	reverse( p + i + 1, p + n );

	return true;
}

int main( int argc, const char *argv[] ) {
	int p[ 5 ] = { 3, 2, 1, 4, 5 };
	sort( p, p + 5 );

	do {
		for ( int i = 0; i < 5; ++i ) printf( "%d ", p[ i ] );
		printf( "\n" );
		system( "pause" );
	} while ( _next_permutation( p, 5 ) );
	// next_permutation( p, p + n )

	return 0;
}
