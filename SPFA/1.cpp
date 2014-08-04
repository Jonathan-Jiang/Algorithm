#include <iostream>
#include <queue>
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

int fa[ SIZE ];
int dist[ SIZE ];
int set[ SIZE ];
int cur_set = 0;

void init() {
	memset( set, 0, sizeof( set ) );
	for ( int i = 0; i < SIZE; ++i ) {
		dist[ i ] = ( i == 0 ? 0 : INF );
		fa[ i ] = ( i == 0 ? 0 : -1 );
	}
}

void SPFA() {
    queue<int> q;
	q.push(0);
	set[0] = 1;
    while (!q.empty()) {
		int v = q.front();
		set[v] = 0;
		q.pop();
		for (int u = 0; u < SIZE; ++u) {
			if (u == v) continue;
			if (graph[u][v] == INF) continue;
			if (dist[v] + graph[u][v] < dist[u]) {
				dist[u] = dist[v] + graph[u][v];
				fa[u] = v;
				if (!set[u]) {
					q.push(u);
					set[u] = 1;
				}
			}
		}
    }
}

void print_path( int i ) {
	if ( fa[ i ] == i ) {
		printf( "%c\n", i + 'a' );
	} else {
		printf( "%c <== ", i + 'a' );
		print_path( fa[ i ] );
	}
}

int main( int argc, const char *argv[] ) {
	init();
	SPFA();

	for ( int i = 0; i < SIZE; ++i ) {
		cout << dist[ i ] << endl;
	}

	cout << endl;

	for ( i = 0; i < SIZE; ++i ) {
		print_path( i );
	}

	return 0;
}
