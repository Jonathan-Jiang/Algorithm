#include <iostream>
#include <algorithm>
using	namespace	std;

int min(int a, int b, int c) {
	int t[] = {a, b, c};
	sort(t, t + 3);
	return t[0];
}

int func(char *str1, int n1, char *str2, int n2) {
	if (n1 == 0) return n2;
	if (n2 == 0) return n1;
	if (*str1 == *str2) return func(str1 + 1, n1 - 1, str2 + 1, n2 - 1);
	else return 1 + min(func(str1 + 1, n1 - 1, str2 + 1, n2 - 1), func(str1 + 1, n1 - 1, str2, n2), func(str1, n1, str2 + 1, n2 - 1));
}

int main() {
	cout << func("GUMBO", strlen("GUMBO"), "GAMBOL", strlen("GAMBOL")) << endl;
	
	return 0;
}