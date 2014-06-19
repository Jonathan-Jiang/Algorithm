//
// 牛顿下山法求平方根
//

#include <iostream>
#include <math.h>
using	namespace	std;
#define EPS 0.000001

float _sqrt( float root ) {
	float current;
	float last = root;
	do {
		current = ( last + root / last ) / 2;
		last = current;
	} while ( fabs( current * current - root ) > EPS );
	return current;
}

int main() {
	float root = 5;
	cout << _sqrt( root ) << endl;

	system( "pause" );
	return 0;
}
