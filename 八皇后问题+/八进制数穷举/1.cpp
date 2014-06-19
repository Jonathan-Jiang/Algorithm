// *
// * 利用八进制数穷举的思路
// * 类似于全排列穷举
// *

#include <iostream>
#include <windows.h>
using	namespace	std;

bool test( int i ) {
	int array[ 8 ];
	for ( int j = 0; j < 8; ++j ) {
		array[ j ] = i % 8;

		for ( int k = 0; k < j; ++k ) {
			// 纵向
			if ( array[ j ] == array[ k ] )  {
				return false;
			}

			// 正对角线
			if ( array[ j ] + j == array[ k ] + k ) {
				return false;
			}

			// 副对角线
			if ( array[ j ] - j == array[ k ] - k ) {
				return false;
			}
		}

		i /= 8;
	}
	return true;
}

void print( int i ) {
	while ( i > 0 ) {
		int sig = i % 8;
		i /= 8;
		for ( int j = 0; j < sig; ++j ) {
			printf( "%c", '#' );
		}
		printf( "%c", 'Q' );
		for ( j = sig; j < 8; ++j ) {
			printf( "%c", '#' );
		}
		printf( "\n" );
	}
	printf( "\n\n" );
}

int main( int argc, const char *argv[] ) {
	for ( int i = 076543210 - 1, cnt = 0; i > 001234567 ; --i ) {
		if ( test( i ) ) {
			++cnt;
			print( i );
		}
	}
	printf( "%d\n", cnt );

	return 0;
}
