// *
// * 利用回溯算法逐行穷举每行所有的可能性
// * 打印 N 皇后的解
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
				// 如果已经冲突
				if ( 3 == cur_column ) {
					// 如果 cur_column == 3， 证明已经到头了
					// 此时需要回溯上一层重新遍历
					cur_column = ++queen[ --cur_row ];

					// 如果上一层列此时也是 3，做过 ++ 操作后会变成 4
					// 导致代码逻辑出现错误
					// 所以需要在第二层 for 下面添加 cur_column > 3 的判断代码
				} else {
					// 没有到头则直接开始下一列测试
					++cur_column;
				}
			} else {
				// 如果未冲突
				// 放置其上，开始下一行探索
				if ( 3 == cur_row ) {
					// 已经到最后一行了
					// 证明已得到一个解
					// 打印解并开始下一轮找寻
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
