//
// 根据完全二叉树的前序遍历序列构建完全二叉树
//

#include <iostream>
using	namespace	std;

void func( string curSeq ) {
	int length = curSeq.length();
	char root = curSeq[ 0 ];
	if ( length > 1 ) {
		string sub1 = curSeq.substr( 1, length / 2 );
		string sub2 = curSeq.substr( length / 2 + 1, length - 1 );
		func( sub1 );
		func( sub2 );
	}
	cout << root;
}

int main() {
	string pre = "1256378";
	func( pre );

	return 0;
}
