#include <iostream>
using	namespace	std;

unsigned char s_max = ~ (1 << (sizeof(unsigned char) * 8 - 1));
unsigned char u_max = s_max | (1 << sizeof(unsigned char) * 8 - 1);

void bin(unsigned char k) {
	for (int i = sizeof(unsigned char) * 8 - 1; i >= 0; --i)
		if (k & (1 << i)) cout << 1;
		else cout << 0;
	cout << endl;
}

void _reverse(unsigned char& k, int size) {
	for (int i = 0, j = size - 1; j >= i; --j, ++i) {
		unsigned char i_bit = (k & (1 << i)) > 0 ? 1 : 0;
		unsigned char j_bit = (k & (1 << j)) > 0 ? 1 : 0;

		if (i_bit == 0) k &= u_max - (1 << j);
		else k |= 1 << j;

		if (j_bit == 0) k &= u_max - (1 << i);
		else k |= 1 << i;
	}
}

void _ror(unsigned char& k, int b) {
	int size = sizeof(unsigned char) * 8;
	b %= size;

	unsigned char low = k & ((1 << b) - 1);
	unsigned char high = k >> b;

	_reverse(low, b);
	_reverse(high, size - b);
	
	k = high << b | low;

	_reverse(k, size);
}

void _rol(unsigned char& k, int b) {
	int size = sizeof(unsigned char) * 8;
	b %= size;

	unsigned char low = k & ((1 << (size - b)) - 1);
	unsigned char high = k >> (size - b);

	_reverse(low, size - b);
	_reverse(high, b);
	
	k = high << (size - b) | low;

	_reverse(k, size);
}

void __ror(unsigned char& k, int b) {
	int size = sizeof(unsigned char) * 8;
	b %= size;

	unsigned char low = k << (size - b);
	unsigned char high = k >> b;

	k = low | high;
}

void __rol(unsigned char& k, int b) {
	int size = sizeof(unsigned char) * 8;
	b %= size;

	unsigned char low = k << b;
	unsigned char high = k >> (size - b);

	k = low | high;
}

int main(int argc, const char* argv[]) {
	for (unsigned char k = 0; k <= 20; ++k) {
		unsigned char r_k, r__k, r_t, l_k, l__k, l_t;
		r_k = r__k = r_t = l_k = l__k = l_t= k;
		_ror(r_k, 10);
		__ror(r__k, 10);
		__asm {
			ror r_t, 10;
		}
		if (r_k == r__k == r_t) ;
		else {
			cout << "k = " << (int) k << endl;
			bin(k);
			bin(r_k);
			bin(r__k);
			bin(r_t);
			system("pause");
		}

		_rol(l_k, 10);
		__rol(l__k, 10);
		__asm {
			rol l_t, 10;
		}
		if (l_k == l__k == l_t) ;
		else {
			cout << "k = " << (int) k << endl;
			bin(k);
			bin(l_k);
			bin(l__k);
			bin(l_t);
			system("pause");
		}
	}

	__asm {
		// rol t, 3;
		// rol t, 3;
	}
	return 0;
}
