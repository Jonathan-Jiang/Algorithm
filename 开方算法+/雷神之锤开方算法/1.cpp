//
// 雷神之锤源代码中的开方函数
//

#include <iostream>
using	namespace	std;

float InvSqrt( float x ) {
	float xhalf = 0.5f * x;
	int i = * ( int* ) &x; // get bits for floating VALUE
	i = 0x5f375a86 - ( i>> 1 ); // gives initial guess y0
	x = * ( float* ) &i; // convert bits BACK to float
	x = x * ( 1.5f - xhalf * x * x ); // Newton step, repeating increases accuracy
	return x;
}  

int main() {
	float k = 2;
	cout << InvSqrt( k ) << endl;
	system( "pause" );

	return 0x000;
}
