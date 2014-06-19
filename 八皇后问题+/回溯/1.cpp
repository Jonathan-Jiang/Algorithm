// *
// * ���û����㷨�������ÿ�����еĿ�����
// * ��ӡ N �ʺ�Ľ�
// *

#include <iostream>
#include <math.h>
using	namespace	std;

int queen[ 4 ];

void print() {
	for ( int i = 0; i < 4; ++i ) {
		for ( int j = 0; j < queen[ i ]; ++j )
			printf( "#" );
		printf( "@" );
		for ( j = queen[ i ] + 1; j < 4; ++j )
			printf( "#" );
		printf( "\n" );
	}
	printf( "\n" );
}

void run() {
	for ( int cur_row = 0; cur_row >= 0 && cur_row < 4; ) {
		for ( int cur_column = 0; cur_column >= 0; ) {
			if ( cur_column > 3 ) {
				if ( cur_row == 0 ) return;
				cur_column = ++queen[ --cur_row ];
			}

			bool conflict = false;

			for ( int pre_row = 0; pre_row < cur_row; ++pre_row )
				// if ( cur_column == queen[ pre_row ] || cur_row - cur_column == pre_row - queen[ pre_row ] || cur_row + cur_column == pre_row + queen[ pre_row ] )
				if ( cur_column == queen[ pre_row ] || abs( cur_row - pre_row ) == abs ( cur_column - queen[ pre_row ] ) )
					conflict = true;

			if ( conflict ) {
				// ����Ѿ���ͻ
				if ( 3 == cur_column ) {
					// ��� cur_column == 3�� ֤���Ѿ���ͷ��
					// ��ʱ��Ҫ������һ�����±���
					cur_column = ++queen[ --cur_row ];

					// �����һ���д�ʱҲ�� 3������ ++ ��������� 4
					// ���´����߼����ִ���
					// ������Ҫ�ڵڶ��� for ������� cur_column > 3 ���жϴ���
				} else {
					// û�е�ͷ��ֱ�ӿ�ʼ��һ�в���
					++cur_column;
				}
			} else {
				// ���δ��ͻ
				// �������ϣ���ʼ��һ��̽��
				if ( 3 == cur_row ) {
					// �Ѿ������һ����
					// ֤���ѵõ�һ����
					// ��ӡ�Ⲣ��ʼ��һ����Ѱ
					queen[ cur_row ] = cur_column++;
					print();
					// next
				} else {
					queen[ cur_row++ ] = cur_column;
					break;
				}
			}
		} // cur_column for
	} // cur_row for
}

int main() {
	run();

	return 0;
}
