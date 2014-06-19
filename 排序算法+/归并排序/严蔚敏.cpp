#include <iostream>
using	namespace	std;

void merge( int SR[], int TR[], int i, int m, int n ) {
    // 将有序的 SR[ i..m ] 和 SR[ m + 1..n ] 归并为有序的 TR[ i..n ]
    for ( int j = m + 1, k = i; i <= m && j <= n; ++k ) {
        // 将 SR 中的记录由小到大地并入 TR
        if ( SR[ i ] < SR[ j ] ) TR[ k ] = SR[ i++ ];
        else TR[ k ] = SR[ j++ ];
    }
    // 将剩余的 SR[ i..m ] 复制到 TR
    if ( i <= m ) {
		/*
	    for ( ; i <= m; ++i ) {
            TR[ k++ ] = SR[ i ];
        }
		*/
		memcpy( TR + k, SR + i, ( m - i + 1 ) * sizeof( int ) );
	}
    // 将剩余的 SR[ j..n ] 复制到 TR
    if ( j <= n ) {
		/*
	    for ( ; j <= n; ++j ) {
            TR[ k++ ] = SR[ j ];
        }
		*/
		memcpy( TR + k, SR + j, ( n - j + 1 ) * sizeof( int ) );
	}
}

void m_sort( int SR[], int TR1[], int s, int t ) {
    // 将 SR[ s..t ] 归并排序为 TR1[ s..t ]
    if ( s == t ) TR1[ s ] = SR[ s ];
    else {
        // 将 SR[ s..t ] 平分为 SR[ s..m ] 和 SR[ m + 1..t ]
        int m = ( s + t ) / 2;
		int* TR2 = new int[ 10 ];
        // 递归地将 SR[ s..m ] 归并为有序的 TR2[ s..m ]
        m_sort( SR, TR2, s, m );
        // 递归地将 SR[ m + 1..t ] 归并为有序的 TR2[ m + 1..t ]
        m_sort( SR, TR2, m + 1, t );
        // 将 TR2[ s..m ] 和 TR2[ m + 1..t ] 归并到 TR1[ s..t ]
        merge( TR2, TR1, s, m, t );
    }
}

void merge_sort( int L[], int length ) {
    m_sort( L, L, 0, length - 1 );
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
