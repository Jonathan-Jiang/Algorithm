/****************************************************/
/** ����:	����������ת��Ϊ����������		**/
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
	chineseNum.insert( pair< string, int > ( "һ", 1 ) );
	chineseNum.insert( pair< string, int > ( "��", 2 ) );
	chineseNum.insert( pair< string, int > ( "��", 3 ) );
	chineseNum.insert( pair< string, int > ( "��", 4 ) );
	chineseNum.insert( pair< string, int > ( "��", 5 ) );
	chineseNum.insert( pair< string, int > ( "��", 6 ) );
	chineseNum.insert( pair< string, int > ( "��", 7 ) );
	chineseNum.insert( pair< string, int > ( "��", 8 ) );
	chineseNum.insert( pair< string, int > ( "��", 9 ) );

	priority.insert( pair< string, int > ( "��", 8 ) );
	priority.insert( pair< string, int > ( "��", 4 ) );
	priority.insert( pair< string, int > ( "ǧ", 3 ) );
	priority.insert( pair< string, int > ( "��", 2 ) );
	priority.insert( pair< string, int > ( "ʮ", 1 ) );
	priority.insert( pair< string, int > ( "��", 0 ) );
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
			// ��������
			curPriority = priority[ tempChinese ];

			if ( curPriority < lastPriority ) {
				if ( curPriority ) {
					// �����λ��ʼ�ݼ�
					summary |= ( 1 << curPriority );
				}
			} else {
				// �����λ��ʼ����
				// ��������

				// ����������ֽ�
				// ��ֹ����  һ��������  ���� bug
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
			// �����֣���ջ
			lastIsNumber = true;
			if ( i == source.length() - 2 ) {
				// ������һ��������
				if ( curPriority ) {
					// curPriority ��Ȼ�� curPriority����ʵ������ lastPriority
					// ���һ�εĵ�λ������
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
			// ��λ�� 1
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
