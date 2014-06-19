#include <iostream>
using	namespace	std;

void merge( int SR[], int TR[], int i, int m, int n ) {
    // ������� SR[ i..m ] �� SR[ m + 1..n ] �鲢Ϊ����� TR[ i..n ]
    for ( int j = m + 1, k = i; i <= m && j <= n; ++k ) {
        // �� SR �еļ�¼��С����ز��� TR
        if ( SR[ i ] < SR[ j ] ) TR[ k ] = SR[ i++ ];
        else TR[ k ] = SR[ j++ ];
    }
    // ��ʣ��� SR[ i..m ] ���Ƶ� TR
    if ( i <= m ) {
		/*
	    for ( ; i <= m; ++i ) {
            TR[ k++ ] = SR[ i ];
        }
		*/
		memcpy( TR + k, SR + i, ( m - i + 1 ) * sizeof( int ) );
	}
    // ��ʣ��� SR[ j..n ] ���Ƶ� TR
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
    // �� SR[ s..t ] �鲢����Ϊ TR1[ s..t ]
    if ( s == t ) TR1[ s ] = SR[ s ];
    else {
        // �� SR[ s..t ] ƽ��Ϊ SR[ s..m ] �� SR[ m + 1..t ]
        int m = ( s + t ) / 2;
		int* TR2 = new int[ 10 ];
        // �ݹ�ؽ� SR[ s..m ] �鲢Ϊ����� TR2[ s..m ]
        m_sort( SR, TR2, s, m );
        // �ݹ�ؽ� SR[ m + 1..t ] �鲢Ϊ����� TR2[ m + 1..t ]
        m_sort( SR, TR2, m + 1, t );
        // �� TR2[ s..m ] �� TR2[ m + 1..t ] �鲢�� TR1[ s..t ]
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
