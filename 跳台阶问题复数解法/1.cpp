//
// Ã¯Ã®Ω◊Œ Ã‚
//

#include <iostream>
#include <complex>
using	namespace	std;

complex< double > x1( 1.839286755214161, 0.0 );
complex< double > x2( -0.419643377607081, 0.606290729207199 );
complex< double > x3( -0.419643377607081, -0.606290729207199 );

complex< double > A( 0.618419922319393, 0.0 );
complex< double > B( 0.190790038840305, -0.018700583111741 );
complex< double > C( 0.190790038840304, 0.018700583111740 );

complex< double > f( int n ) {
	return A * pow( x1, n ) + B * pow( x2, n ) + C * pow( x3, n );
}

int main( int argc, const char *argv[] ) {
	for ( int i = 0; i < 5; ++i )
		cout << f( i ).real() << endl;


	return 0;
}
