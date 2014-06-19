#include <iostream>
using    namespace    std;

void merge( int B[], int C[], int A[], int m, int n ) {
    // 实现将有序数组 B[ 0 : m - 1 ] 和 C[ 0 : n - 1 ] 合并到 A 中
    int i, j, k;
	i = j = k = 0;
    while ( i < m && j < n ) {
        if ( B[ i ] < C[ j ] ) {
            A[ k++ ] = B[ i++ ];
        } else {
            A[ k++ ] = C[ j++ ];
        }
    }
    if ( i == m ) {
        for ( ; j < n; ++j ) {
            A[ k++ ] = C[ j ];
        }
    } else {
        for ( ; i < m; ++i ) {
            A[ k++ ] = B[ i ];
        }
    }
}

void merge_sort( int A[], int n ) {
    int* B = new int[ n ];
    int* C = new int[ n ];
    if ( n > 1 ) {
        int mid = n / 2;
        for ( int i = 0; i < mid; ++i ) {
            B[ i ] =  A[ i ];
        }
        for ( i = 0; i < n - mid; ++i ) {
            C[ i ] = A[ mid + i ];
        }
        merge_sort( B, mid );
        merge_sort( C, n - mid );
        merge( B, C, A, mid, n - mid );
    }
}

int
main( void ) {
    int n[] = {
		5, 7, 1, 9, 10,
		3, 4, 6, 2, 8
	};

    merge_sort( n, 10 );
    for ( int i = 0; i < 10; ++i ) {
        cout << n[ i ] << " ";
    }
    cout << endl;

    return 0;
}
