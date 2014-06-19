/****************************************************/
/** 功能:	将汉字数字转化为阿拉伯数字		**/
/** Author:	daishengdong						   **/
/** School:	HDU									   **/
/** Email:	daishengdong@gmail.com				   **/
/****************************************************/

#include <iostream>
#include <string>
#include <stack>
#include <map>
using	namespace	std;

class convert {
public:
	void start();
	void print();

private:
	void init();

	map< string, int > chineseNum;
	map< string, int > priority;
	stack< int > num;
	
	int summary;
	unsigned int sizeOfSummary;
	string source;
};

void convert::init() {
	cout << "now: " << endl;
	cin >> source;

	summary = sizeOfSummary = 0;
	chineseNum.insert( pair< string, int > ( "一", 1 ) );
	chineseNum.insert( pair< string, int > ( "二", 2 ) );
	chineseNum.insert( pair< string, int > ( "三", 3 ) );
	chineseNum.insert( pair< string, int > ( "四", 4 ) );
	chineseNum.insert( pair< string, int > ( "五", 5 ) );
	chineseNum.insert( pair< string, int > ( "六", 6 ) );
	chineseNum.insert( pair< string, int > ( "七", 7 ) );
	chineseNum.insert( pair< string, int > ( "八", 8 ) );
	chineseNum.insert( pair< string, int > ( "九", 9 ) );

	priority.insert( pair< string, int > ( "亿", 8 ) );
	priority.insert( pair< string, int > ( "万", 4 ) );
	priority.insert( pair< string, int > ( "千", 3 ) );
	priority.insert( pair< string, int > ( "百", 2 ) );
	priority.insert( pair< string, int > ( "十", 1 ) );
	priority.insert( pair< string, int > ( "零", 0 ) );
}

void convert::start() {
	init();

	char tempChinese[ 3 ];
	int curPriority = -1;
	int lastPriority = 10;
	bool lastIsNumber = false;
	for ( unsigned int i = 0; i < source.length() - 1; i += 2 ) {
		tempChinese[ 0 ] = source[ i ];
		tempChinese[ 1 ] = source[ i + 1 ];
		tempChinese[ 2 ] = '\0';

		map< string, int >::iterator it = chineseNum.find( tempChinese ); 
		if ( it == chineseNum.end() ) {
			// 不是数字
			curPriority = priority[ tempChinese ];

			if ( curPriority < lastPriority ) {
				if ( curPriority ) {
					// 如果单位开始递减
					summary |= ( 1 << curPriority );
				}
			} else {
				// 如果单位开始递增
				// 连续左移

				// 在这里加了手脚
				// 防止出现  一百零三万  这类 bug
				if ( lastIsNumber ) {
					summary |= 1;
				}
				summary <<= curPriority;
			}
			
			if ( curPriority ) {
				lastPriority = curPriority;
			}
			lastIsNumber = false;
		} else {
			// 是数字，入栈
			lastIsNumber = true;
			if ( i == source.length() - 2 ) {
				// 如果最后一个是数字
				if ( curPriority ) {
					// curPriority 虽然是 curPriority，但实际上是 lastPriority
					// 最后一次的单位不是零
					summary |= ( 1 << ( curPriority - 1 ) );
				} else {
					summary |= 1;
				}
			}
			num.push( chineseNum[ tempChinese ] );
			++sizeOfSummary;
		}
	}
}

void convert::print() {
	stack< int > out;
	unsigned int count = 0;
	for ( unsigned int i = 0; count < sizeOfSummary; ++i ) {
		if ( summary & ( 1 << i ) ) {
			// 此位是 1
			out.push( num.top() );
			num.pop();
			++count;
		} else {
			out.push( 0 );
		}
	}

	while ( ! out.empty() ) {
		cout << out.top();
		out.pop();
	}
	cout << endl;
}

int main() {
	convert converter;
	while ( 1 ) {
		converter.start();
		converter.print();
	}

	system("pause");
	return 0;
}
