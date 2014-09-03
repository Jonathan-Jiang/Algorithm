#include <stdio.h>
#include <iostream>
#include <string>
using	namespace	std;

#define	MAXLEN 1024	

const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

class base64 {
    public:
        char* encode(char*);
        char* decode(char*);

	private:
		unsigned short getIndex(char);
};

char*
base64::encode(char* buffer) {
	int len = strlen(buffer);
	int cnt = len % 3;
    if (1 == cnt) {
        buffer[len] = 0;
        buffer[len + 1] = 0;
        buffer[len + 2] = '\0';
    } else if (2 == cnt) {
        buffer[len] = 0;
        buffer[len + 1] = '\0';
    }

	char* ret = new char[MAXLEN * 2];
    for (int i = 0, ret_i = 0; i < 8 * len; i += 6, ++ret_i) {
        int byte_index = i / 8;
        int bit_index = i % 8;
        unsigned char t[2];
        t[0] = buffer[byte_index + 1];
        t[1] = buffer[byte_index];
        unsigned short k = *(unsigned short*)(t);
		ret[ret_i] = table[(k <<= bit_index) >> 10];
    }
    if (1 == cnt) {
		ret[ret_i++] = '=';
		ret[ret_i++] = '=';
		ret[ret_i] = '\0';
    } else if (2 == cnt) {
		ret[ret_i++] = '=';
		ret[ret_i] = '\0';
    } else {
		ret[ret_i] = '\0';
	}
	return ret;
}

unsigned short
base64::getIndex(char ch) {
	for (unsigned short i = 0; i < strlen(table); ++i) {
		if (table[i] == ch) return i;
	}
	return -1;
}

char*
base64::decode(char* buffer) {
	int len = strlen(buffer);
	int cnt = 0;
	if ('=' == buffer[len - 2]) ++cnt;
	if ('=' == buffer[len - 1]) ++cnt;

	char* ret = new char[MAXLEN];
	int ret_len = 0;
	memset(ret, 0, sizeof(char) * MAXLEN);
	for (int i = 0, ret_i = 0; i < len; ++i, ret_i += 6) {
		unsigned short index = getIndex(buffer[i]);
		if (-1 == index) exit(1);
		
		int byte_index = ret_i / 8;
		int bit_index = ret_i % 8;
		
		unsigned char t[2];
        t[0] = ret[byte_index + 1];
        t[1] = ret[byte_index];
        unsigned short k = *(unsigned short*)(t);
		k |= index << (10 - bit_index);
		ret[byte_index] |= k >> 8;
		ret[ret_len = byte_index + 1] |= (k <<= 8) >> 8;
	}
	ret[ret_len - 1] = '\0';

	return ret;
}

int
main(void) {
	while (1) {
		char buffer[MAXLEN];
		fgets(buffer, MAXLEN, stdin);

	#ifdef WIN32
		int len = strlen(buffer) - 1;
	#else
		int len = strlen(buffer);
	#endif
		buffer[len] = '\0';

		base64 ins_base64;
		
		char* ret_en = ins_base64.encode(buffer);
		puts(ret_en);
		char* ret_de = ins_base64.decode(ret_en);
		puts(ret_de);
		delete ret_en;
		delete ret_de;
	}

    return 0;
}