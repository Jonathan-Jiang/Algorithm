/* ===========================================
 * 堆排序实现
 * 功能：实现堆排序，同时利用堆的原理实现提取 TOP 10
 * Date: 2012.9.11   
 * Author: daishengdong
 * School: HDU
 * Email: daishengdong@gmail.com
 ===========================================*/

#include <iostream>
#include <fstream>
#include <algorithm>
using	namespace	std;

const int TOP = 1;
const int MAXSIZE = 14;
const int TOPSIZE = 10;

inline void swap( int* x, int* y ) {
	int temp = * x;
	* x = * y;
	* y = temp;
}

class heap {
public:
	// the heap array's index start from 1
	int array[ MAXSIZE + 1];
	int sort_heap[ MAXSIZE + 1 ];
	int top_10_heap[ TOPSIZE + 1 ];

	heap();
	void _heap_sort();
	void get_top_10();

private:
	void load_array();
	void build_heap( int heap_to_build[], int max_size );
	void shift_down( int heap_to_shift[], int cur_node_index, int max_size );
};

heap::heap() {
	load_array();
	memcpy( top_10_heap, array, sizeof( top_10_heap ) );
	memcpy( sort_heap, array, sizeof( sort_heap ) );
}

void heap::_heap_sort() {
	/* ===============================
	cout << "sort_heap:" << endl;
	for ( int j = 1; j <= TOPSIZE; ++j ) {
		cout << sort_heap[ j ] << endl;
	}
	cout << "==============" << endl;
	=============================== */

	cout << "heap sort" << endl;
	// build the heap first
	build_heap( sort_heap, MAXSIZE );

	int size = MAXSIZE;
	while ( size ) {
		cout << sort_heap[ TOP ] << endl;
		sort_heap[ TOP ] = sort_heap[ size-- ];
		shift_down( sort_heap, 1, size );
	}
	cout << "==============" << endl;
}

void heap::get_top_10() {
	build_heap( top_10_heap, TOPSIZE );

	/* ===============================
	cout << "top_10_heap:" << endl;
	for ( int j = 1; j <= TOPSIZE; ++j ) {
		cout << top_10_heap[ j ] << endl;
	}
	cout << "==============" << endl;
	 =============================== */
	
	for ( int i = 11; i <= MAXSIZE; ++i ) {
		if ( array[ i ] > top_10_heap[ TOP ] ) {
			top_10_heap[ TOP ] = array[ i ];
			shift_down( top_10_heap, 1, TOPSIZE );
		}
	}

	sort( top_10_heap + 1, top_10_heap + TOPSIZE + 1 );

	cout << "get top 10:" << endl;
	for ( i = 1; i <= 10; ++i ) {
		cout << top_10_heap[ i ] << endl;
	}
	cout << "==============" << endl;
}

void heap::build_heap( int heap_to_build[], int max_size ) {
	int cur_node_index = max_size / 2;
	while ( cur_node_index ) {
		// if the father is greater than any of the children
		// swap the value of the father and his min child
		shift_down( heap_to_build, cur_node_index--, max_size );
	}
}

void heap::shift_down( int heap_to_shift[], int cur_node_index, int max_size ) {
	int min_index = cur_node_index * 2;
	if ( min_index > max_size && min_index + 1 > max_size ) {
		return;
	}
	if ( min_index + 1 <= max_size ) {
		if ( heap_to_shift[ min_index ] > heap_to_shift[ min_index + 1 ] ) {
			min_index = min_index + 1;
		}
	}
	int* min = &heap_to_shift[ min_index ];
	int* root = &heap_to_shift[ cur_node_index ];

	if ( * root > * min ) {
		// if the root is greater than the min child
		swap( root, min );
		shift_down( heap_to_shift, min_index, max_size );
	}
}

void heap::load_array() {
	int* p = array + 1;
	ifstream ifs( "num.txt" );

	if ( !ifs ) {
		cerr << "cannot open num.txt" << endl;
		exit( 1 );
	}

	while ( ifs.peek() != -1 ) {
		ifs >> * ( p++ );
	}
	ifs.close();

	cout << "load array complete!" << endl;
	cout << "==============" << endl;
}

int main( void ) {
	heap insHeap;
	insHeap._heap_sort();
	insHeap.get_top_10();

	return 0;
}
