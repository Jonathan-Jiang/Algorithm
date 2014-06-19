#include <iostream>
#include <bitset>
#include <math.h>
using    namespace    std;

const int INF = ~ ( 1 << ( sizeof( int ) * 8 - 1 ) );

const int C = 1;
const double a = 0.2;
const double b = 1 - a;
const int RAW = 0.8;
const int NCMAX = 100;
const int Q = 1;

const int N = 31;
const int M = N;

typedef struct point {
    int x;
    int y;
} city;

const city citys[ N ] = {
    { 13.04, 23.12 }, { 36.39, 13.15 }, { 41.77, 22.44 }, { 37.12, 13.99 },
	{ 34.88, 15.35 }, { 33.26, 15.56 }, { 32.38, 12.29 }, { 41.96, 10.04 },
	{ 43.12, 79.0  }, { 43.86, 5.70  }, { 30.07, 19.70 }, { 25.62, 17.56 },
	{ 27.88, 14.91 }, { 23.81, 16.76 }, { 13.32, 6.95  }, { 37.15, 16.78 }, 
	{ 39.18, 21.79 }, { 40.61, 23.70 }, { 37.80, 22.12 }, { 36.76, 25.78 },
	{ 40.29, 28.38 }, { 42.63, 29.31 }, { 34.29, 19.08 }, { 35.07, 23.67 },
	{ 33.94, 26.43 }, { 34.39, 32.01 }, { 29.35, 32.40 }, { 31.40, 35.50 },
	{ 25.45, 23.57 }, { 27.78, 28.26 }, { 23.70, 29.75 },
};

int main( int argc, char *const argv[] ) {
	// use bits denote the citys the k-th ant has covered
	typedef bitset< N > citySet;
	citySet tabu[ M ];
	// the current city which the k-th ant in
	int s[ M ];
	int t = 0;
	int NC = 0;
	double minL = INF;
	double L[ M ];
	double T[ N ][ N ];
	double deta_T[ N ][ N ];

	int i, j, k;

	memset( s, 0, sizeof( s ) );
	memset( L, 0, sizeof( L ) );
	memset( T, C, sizeof( T ) );
	memset( deta_T, 0, sizeof( deta_T ) );
	// set the original citys
	for ( k = 0; k < M; ++k ) {
		s[ k ] = k;
		tabu[ k ] |= 1 << k;
	}

	while ( NC <= NCMAX ) {
		memset( tabu, 0, sizeof( tabu ) );
		for ( i = 0; i < N - 1; ++i ) {
			for ( k = 0; k < M; ++k ) {
				// for each ant, find the p-max city
				// index denote for the serial number of the p-max city
				double p_max = 0.0;
				int index = 0;
				for ( j = 0; j < N; ++j ) {
					if ( ( tabu[ k ].to_ulong() & ( unsigned long )( 1 << j ) ) == 0 ) {
						// the j-th city is in the allow list
						double tij = T[ s[ k ] ][ j ];
						double dij = sqrt( pow( ( citys[ s[ k ] ].x - citys[ j ].x ), 2 ) + pow( ( citys[ s[ k ] ].y - citys[ j ].y ), 2 ) );
						double nij = 1 / dij;
						double p = pow( tij, a ) * pow( nij, b );

						double sum = 0.0;
						for ( int sigmaJ = 0; sigmaJ < N; ++sigmaJ ) {
							if ( ( tabu[ k ].to_ulong() & ( unsigned long )( 1 << sigmaJ ) ) == 0 && sigmaJ != j) {
								double tis = T[ s[ k ] ][ sigmaJ ];
								double dis = sqrt( pow( ( citys[ s[ k ] ].x - citys[ sigmaJ ].x ), 2 ) + pow( ( citys[ s[ k ] ].y - citys[ sigmaJ ].y ), 2 ) );
								double nis = 1 / dis;
								sum += pow( tis, a ) * pow( nis, b );
							}
						}
						p /= sum;
						if ( p - p_max >= 0 ) {
							p_max = p;
							index = j;
						}
					}
				} // for

				L[ k ] += sqrt( pow( ( citys[ s[ k ] ].x - citys[ index ].x ), 2 ) + pow( ( citys[ s[ k ] ].y - citys[ index ].y ), 2 ) );
				s[ k ] = index;
				tabu[ k ] |= 1 << index;
			}
		}

		for ( k = 0; k < M; ++k ) {
			L[ k ] += sqrt( pow( ( citys[ s[ k ] ].x - citys[ k ].x ), 2 ) + pow( ( citys[ s[ k ] ].y - citys[ k ].y ), 2 ) );
			if ( minL - L[ k ] >= 0 ) {
				minL = L[ k ];
			}
		}

		for ( i = 0; i < N; ++i ) {
			for ( j = 0; j < N && j != i; ++j ) {
				for ( k = 0; k < M; ++k ) {
					deta_T[ i ][ j ] += Q / L[ k ];
				}
				T[ i ][ j ] = RAW * T[ i ][ j ] + deta_T[ i ][ j ];
			}
		}

		++NC;
		memset( deta_T, 0, sizeof( deta_T ) );
	}

	cout << minL << endl;

    return 0;
}
