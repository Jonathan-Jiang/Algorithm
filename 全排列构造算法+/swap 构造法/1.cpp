//
// STL 全排列
// 构造全排列:
// 1. 增量构造，构造前缀之后递归构造下一个
// 2. swap 构造法，如下所示
// 3. STL 下一个排列构造法，算法思想见 next_permutation
//

#include <iostream>
using	namespace	std;

bool ok( int array[], int cur, int end ) {
	// 之选之前没有出现过的数进行替换
	for ( int i = cur; i < end; ++i ) if ( array[ i ] == array[ end ] )
		return false;
	return true;
}

void func( int array[], int cur, int num ) {
	if ( cur == num ) { for ( int i = 0; i <= num; ++i )
		cout << array[ i ] << " ";
		cout << endl;
	}
	
	for ( int i = cur; i <= num; ++i ) {
		if ( ok( array, cur, i ) ) {
			swap( array[ cur ], array[ i ] );
			func( array, cur + 1, num );
			swap( array[ cur ], array[ i ] );
		}
	}
}

int main( int argc, const char *argv[] ) {
	int data[ 3 ] = { 1, 2, 2 };
	func( data, 0, 2 );

	cout << endl;

	return 0;
}
