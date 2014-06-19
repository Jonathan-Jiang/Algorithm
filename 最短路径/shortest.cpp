//
// 最小生成树 ???
//

#include <iostream>
using	namespace	std;

const int MAX = ~ ( 1 << ( sizeof( int ) * 8 - 1 ) );

int main() {
	int i = 0, j = 0;
	int N = -1, M = -1;

	cin >> N >> M;

	int ** matrix = new int * [ N ];

	for ( i = 0; i < N; ++i ) {
		matrix[ i ] = new int[ N ];
	}

	for ( i = 0; i < N; ++i ) {
		for ( j = 0; j < N; ++j ) {
			matrix[ i ][ j ] = MAX;
		}
	}
	
	int * dist = new int[ N ];
	int * v = new int[ N ];

	for ( i = 0; i < N; ++i ) {
		dist[ i ] = MAX;
	}

	int w = 1;
	for ( i = 0; i < M; ++i ) {
		int v1, v2;
		cin >> v1 >> v2;
		matrix[ v1 ][ v2 ] = w;
		matrix[ v2 ][ v1 ] = w;
		if ( 0 == v1) {
			dist[ v2 ] = w;
		} else if ( 0 == v2 ) {
			dist[ v1 ] = w;
		}

		w *= 2;
	}

	for ( i = 0; i < N; ++i ) {
		v[ i ] = i;
	}
	
	bool choosed = true;
	while ( choosed ) {
		int minV = -1, minW = MAX;
		choosed = false;
		for ( i = 0; i < N; ++i ) {
			if ( v[ i ] != 0 ) {
				if ( dist[ i ] < minW ) {
					choosed = true;
					minW = dist[ i ];
					minV = i;
				}
			}
		}

		if ( choosed ) {
			v[ minV ] = 0;
			for ( j = 0; j < N; ++j ) {
				if ( matrix[ minV ][ j ] != MAX) {
					if ( dist[ j ] > dist[ minV ] + matrix[ minV ][ j ] ) {
						dist[ j ] = dist[ minV ] + matrix[ minV ][ j ];
					}
				}
			}

			for ( i = 0; i < N; ++i ) {
				if ( matrix[ i ][ minV ] != MAX) {
					if ( dist[ i ] > dist[ minV ] + matrix[ i ][ minV ] ) {
						dist[ i ] = dist[ minV ] + matrix[ i ][ minV ];
					}
				}
			}
		}
	}

	for ( i = 1; i < N; ++i ) {
		if ( MAX == dist[ i ] ) {
			cout << -1 << endl;
		} else if ( dist[i] > 100000 ) {
			cout << dist[ i ] % 100000 << endl;
		} else {
			cout << dist[ i ] << endl;
		}
	}

	return 0;
}
