//
// STL ȫ����
// ����ȫ����:
// 1. �������죬����ǰ׺֮��ݹ鹹����һ��
// 2. swap ���취��������ʾ
// 3. STL ��һ�����й��취���㷨˼��� next_permutation
//

#include <iostream>
using	namespace	std;

bool ok( int array[], int cur, int end ) {
	// ֮ѡ֮ǰû�г��ֹ����������滻
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
