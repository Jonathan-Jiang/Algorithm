// *
// * dijkstra 单源最短路径算法
// * 每次在所有未标记的结点中，选出 dis 值最小的结点 index
// * 对从 index 出发的所有结点进行松弛操作
// *

#include <iostream>
using	namespace	std;

const int INF = ~ ( 1 << ( sizeof( int ) * 8 - 1 ) );

const int SIZE = 6;
const int graph[ SIZE ][ SIZE ] = {
	0, 6, 3, INF, INF, INF,
	6, 0, 2, 5, INF, INF,
	3, 2, 0, 3, 4, INF,
	INF, 5, 3, 0, 2, 3,
	INF, INF, 4, 2, 0, 5,
	INF, INF, INF, 3, 5, 0
};

int pre[ SIZE ];
int dis[ SIZE ];
int set[ SIZE ];
int cur_set = 0;

void init() {
	memset( set, 0, sizeof( set ) );
	for ( int i = 0; i < SIZE; ++i ) {
		// 以下两种初始化都可以
		// 错误！
		// 下面注释的这种初始化方法不对，会导致打印路径时出现错误
		// dis[ i ] = graph[ 0 ][ i ];
		dis[ i ] = ( i == 0 ? 0 : INF );
		pre[ i ] = ( i == 0 ? 0 : -1 );
	}
}

void dijkstra() {
	for ( int i = 0; i < SIZE; ++i ) {
		int index, min = INF;
		for ( int j = 0; j < SIZE; ++j ) if ( !set[ j ] && dis[ j ] <= min ) {
			min = dis[ index = j ];
		}

		set[ index ] = 1;

		for ( j = 0; j < SIZE; ++j ) if ( dis[ index ] != INF && graph[ index ][ j ] != INF ) {
			if( dis[ j ] > dis[ index ] + graph[ index ][ j ] ) {
				dis[ j ] = dis[ index ] + graph[ index ][ j ];
				pre[ j ] = index;
			}
		}
	}
}

void print_path( int i ) {
	if ( pre[ i ] == i ) {
		printf( "%c\n", i + 'a' );
	} else {
		printf( "%c <== ", i + 'a' );
		print_path( pre[ i ] );
	}
}

int main( int argc, const char *argv[] ) {
	init();
	dijkstra();

	for ( int i = 0; i < SIZE; ++i ) {
		cout << dis[ i ] << endl;
	}

	cout << endl;

	for ( i = 0; i < SIZE; ++i ) {
		print_path( i );
	}

	return 0;
}
