//
// 手工模拟计算 n 的阶乘
//

#include <iostream>
#include <stdlib.h>
#include <stack>
using	namespace	std;

const int MAXSIZE = 3000;
int result[ MAXSIZE ];
stack< int > output;

int main() {
	while (1) {
		int i = 0, j = 0;
		int n = 0;
		cout << "n: ";
		cin >> n;

		memset( result, 0, sizeof( result ) );
		result[ 0 ] = 1;

		int digits = 1;
		int upper = 0;
		for ( i = 2; i <= n; ++i ) {
			for ( j = 0; j < MAXSIZE; ++j ) {
				int temp = result[ j ] * i + upper;
				digits = temp % 10;
				upper = temp / 10;
				result[ j ] = digits;
			}
		}

		for ( i = MAXSIZE - 1; i >= 0; --i ) {
			if ( result[ i ] != 0 ) {
				break;
			}
		}

		for ( j = 0; j <= i; ++j ) {
			output.push( result[ j ] );
		}

		while ( ! output.empty() ) {
			cout << output.top();
			output.pop();
		}

		cout << endl;
	}

	return 0;
}
