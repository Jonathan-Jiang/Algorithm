//
// 利用 map 记录下每一个数应该出现的位置(实际上就是有几个数比该数小，则该数排在第几位)
//

#include <iostream>
#include <algorithm>
#include <map>
using	namespace	std;

void c_sort(int s[], int s_sorted[], int n) {
	int i;
	map< int, int > s_map;
	map< int, int >::iterator it;
	for (i = 0; i < n; ++i) {
		s_map.insert(pair< int, int >(s[i], 0));
		//cout << s_map.count << endl;
		for (it = s_map.begin(); it != s_map.end(); ++it) {
			//cout << it->first << "  " << it->second << endl;
			int e = it->first;
			cout << e << " " << s[i] << endl;
			if (s[i] > e) {
				++it->second;
			}
		}
	}

	for (it = s_map.begin(); it != s_map.end(); ++it) {
		s_sorted[it->second] = it->first;
	}
}


int main() {
	int s[10] = { 2, 7, 9, 4, 1, 5, 8, 3, 6, 10 };
	int s_sorted[10];
	c_sort(s, s_sorted, 10);

	for (int i = 0; i < 10; ++i) {
		cout << s_sorted[i] << " ";
	}
	cout << endl;

	return 0;
}
