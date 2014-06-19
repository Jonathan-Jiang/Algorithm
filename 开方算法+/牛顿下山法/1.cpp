#include <math.h>
#include <iostream>
using	namespace	std;

double _sqrt( double n ) {
	double ret = n;
	while ( fabs( ret * ret - n ) > 0.0000001 ) {
		ret = ( ret * ret + n ) / ret / 2;
	}
	return ret;
}

int main( void ) {
	for ( int i = 0; i < 10; ++i ) {
		cout << _sqrt( i ) << endl;
	}

	return 0;
}
