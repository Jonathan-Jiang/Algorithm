// *
// * ������������������
// * ����һ�����飬����Ԫ�������и����ҳ�����һ�����������У�ʹ�����
// * ���������Զ�̬�滮��˼����
// * �� b[ i ] ��ʾ�Ե� i ��Ԫ�� data[ i ] ��β�����������
// * ��ô��Ȼ b[ i + 1 ] = b[ i ] > 0 ? b[ i ] + a[ i + 1 ] : a[ i + 1 ]
// *

#include <iostream>
using	namespace	std;

#define	SIZE	10

const int data[ SIZE ] = {
	-1, 3, 2, -3, 4, -1, 2, -1, 1, 0
};

int main( int argc, const char *argv[] ) {
	int b[ SIZE ];
	memset( b, 0, sizeof( b ) );
	b[ 0 ] = data[ 0 ];
	for ( int i = 0; i < SIZE - 1; ++i ) {
		b[ i + 1 ] = ( b[ i ] > 0 ? b[ i ] + data[ i + 1 ] : data[ i + 1 ] );
	}

	int index = 0;
	int max = b[ index ];
	for ( i = 1; i < SIZE; ++i ) {
		if ( b[ i ] > max ) {
			// ���� b[ i ] >= max, ���������������У���������̵������
			max = b[ i ];
			index = i;
		}
	}

	cout << "max sum: " << max << endl;
	int sum = 0;
	for ( i = index; i >= 0; --i ) {
		sum += data[ i ];
		if ( sum == max ) {
			cout << data[ i ] << " ";
			break;
		}
		cout << data[ i ] << " ";
	}
	cout << endl;
	
	return 0;
}
