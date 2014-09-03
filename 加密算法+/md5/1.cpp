#include <iostream>
#include <string.h>

using	namespace	std;

#ifdef __GNUC__
typedef long long	INT64;
#elif __MINGW32__
typedef long long	INT64;
#elif _MSC_VER
typedef	__int64		INT64;
#endif

#define	MAXLEN	1024

unsigned int A = 0x01234567;
unsigned int B = 0x89abcdef;
unsigned int C = 0xfedcba98;
unsigned int D = 0x76543210;

unsigned int _md5[4];

#define F(X, Y, Z) ((X & Y) | ((~X) & Z))
#define G(X, Y, Z) ((X & Z) | (Y & (~Z)))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | (~Z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define FF(a, b, c, d, Mj, s, ti) a = b + ROTATE_LEFT(a + F(b, c, d) + Mj + ti, s)
#define GG(a, b, c, d, Mj, s, ti) a = b + ROTATE_LEFT(a + G(b, c, d) + Mj + ti, s)
#define HH(a, b, c, d, Mj, s, ti) a = b + ROTATE_LEFT(a + H(b, c, d) + Mj + ti, s)
#define II(a, b, c, d, Mj, s, ti) a = b + ROTATE_LEFT(a + I(b, c, d) + Mj + ti, s)

class md5 {
	public:
		char* encrypt(char*);

	private:
		void fill(char*);
		void roll(char*);
		void output(char*, void*, int);
		INT64 N;
		char* filled;
};

void
md5::fill(char* buffer) {
	INT64 byte_len_before_fill = strlen(buffer);
	INT64 bit_len_before_fill = byte_len_before_fill * 8;
	N = byte_len_before_fill / 64;
	int re = byte_len_before_fill % 64;
	int byte_len_to_fill = 0;
	if (re > 56) {
		N += 1;
		byte_len_to_fill = 64;
	}
	N += 1;
    byte_len_to_fill += 56 - re;
    __int64 byte_len_after_fill = N * 64;

	filled = new char[byte_len_after_fill];
	memset(filled, 0, sizeof(char) * byte_len_after_fill);
	memcpy(filled, buffer, sizeof(char) * byte_len_before_fill);
	filled[byte_len_before_fill] = (char)0x80;
	memcpy(filled + byte_len_after_fill - sizeof(INT64), &bit_len_before_fill, sizeof(INT64));
}

void
md5::roll(char* filled_start) {
	unsigned int* m= (unsigned int*)filled_start;

	int a = _md5[0];
	int b = _md5[1];
	int c = _md5[2];
	int d = _md5[3];
	// round 1
	FF(a, b, c, d, m[0], 7, 0xd76aa478);
	FF(d, a, b, c, m[1], 12, 0xe8c7b756);
	FF(c, d, a, b, m[2], 17, 0x242070db);
	FF(b, c, d, a, m[3], 22, 0xc1bdceee);
	FF(a, b, c, d, m[4], 7, 0xf57c0faf);
	FF(d, a, b, c, m[5], 12, 0x4787c62a);
	FF(c, d, a, b, m[6], 17, 0xa8304613);
	FF(b, c, d, a, m[7], 22, 0xfd469501);
	FF(a, b, c, d, m[8], 7, 0x698098d8);
	FF(d, a, b, c, m[9], 12, 0x8b44f7af);
	FF(c, d, a, b, m[10], 17, 0xffff5bb1);
	FF(b, c, d, a, m[11], 22, 0x895cd7be);
	FF(a, b, c, d, m[12], 7, 0x6b901122);
	FF(d, a, b, c, m[13], 12, 0xfd987193);
	FF(c, d, a, b, m[14], 17, 0xa679438e);
	FF(b, c, d, a, m[15], 22, 0x49b40821);

	// round 2
	GG(a, b, c, d, m[1], 5, 0xf61e2562);
	GG(d, a, b, c, m[6], 9, 0xc040b340);
	GG(c, d, a, b, m[11], 14, 0x265e5a51);
	GG(b, c, d, a, m[0], 20, 0xe9b6c7aa);
	GG(a, b, c, d, m[5], 5, 0xd62f105d);
	GG(d, a, b, c, m[10], 9, 0x02441453);
	GG(c, d, a, b, m[15], 14, 0xd8a1e681);
	GG(b, c, d, a, m[4], 20, 0xe7d3fbc8);
	GG(a, b, c, d, m[9], 5, 0x21e1cde6);
	GG(d, a, b, c, m[14], 9, 0xc33707d6);
	GG(c, d, a, b, m[3], 14, 0xf4d50d87);
	GG(b, c, d, a, m[8], 20, 0x455a14ed);
	GG(a, b, c, d, m[13], 5, 0xa9e3e905);
	GG(d, a, b, c, m[2], 9, 0xfcefa3f8);
	GG(c, d, a, b, m[7], 14, 0x676f02d9);
	GG(b, c, d, a, m[12], 20, 0x8d2a4c8a);

	// round 3
	HH(a, b, c, d, m[5], 4, 0xfffa3942);
	HH(d, a, b, c, m[8], 11, 0x8771f681);
	HH(c, d, a, b, m[11], 16, 0x6d9d6122);
	HH(b, c, d, a, m[14], 23, 0xfde5380c);
	HH(a, b, c, d, m[1], 4, 0xa4beea44);
	HH(d, a, b, c, m[4], 11, 0x4bdecfa9);
	HH(c, d, a, b, m[7], 16, 0xf6bb4b60);
	HH(b, c, d, a, m[10], 23, 0xbebfbc70);
	HH(a, b, c, d, m[13], 4, 0x289b7ec6);
	HH(d, a, b, c, m[0], 11, 0xeaa127fa);
	HH(c, d, a, b, m[3], 16, 0xd4ef3085);
	HH(b, c, d, a, m[6], 23, 0x04881d05);
	HH(a, b, c, d, m[9], 4, 0xd9d4d039);
	HH(d, a, b, c, m[12], 11, 0xe6db99e5);
	HH(c, d, a, b, m[15], 16, 0x1fa27cf8);
	HH(b, c, d, a, m[2], 23, 0xc4ac5665);

	// round 4
	II(a, b, c, d, m[0], 6, 0xf4292244);
	II(d, a, b, c, m[7], 10, 0x432aff97);
	II(c, d, a, b, m[14], 15, 0xab9423a7);
	II(b, c, d, a, m[5], 21, 0xfc93a039);
	II(a, b, c, d, m[12], 6, 0x655b59c3);
	II(d, a, b, c, m[3], 10, 0x8f0ccc92);
	II(c, d, a, b, m[10], 15, 0xffeff47d);
	II(b, c, d, a, m[1], 21, 0x85845dd1);
	II(a, b, c, d, m[8], 6, 0x6fa87e4f);
	II(d, a, b, c, m[15], 10, 0xfe2ce6e0);
	II(c, d, a, b, m[6], 15, 0xa3014314);
	II(b, c, d, a, m[13], 21, 0x4e0811a1);
	II(a, b, c, d, m[4], 6, 0xf7537e82);
	II(d, a, b, c, m[11], 10, 0xbd3af235);
	II(c, d, a, b, m[2], 15, 0x2ad7d2bb);
	II(b, c, d, a, m[9], 21, 0xeb86d391);

	_md5[0] += a;
	_md5[1] += b;
	_md5[2] += c;
	_md5[3] += d;
}
	
void
md5::output(char* buf, void* pbytes, int n) {
     for (int i = 0, j = 0; i < 2 * n; i += 2, ++j) {
          buf[i] = (char)(((unsigned char*)pbytes)[j] >> 4);
     }
     for (i = 1, j = 0; i < 2 * n; i += 2, ++j) {
          buf[i] = (char)(((unsigned char*)pbytes)[j] & 0xF);
     }
     
     for (i = 0; i < 2 * n; ++i) {
          if (buf[i] <= 9) buf[i] += '0';
          else buf[i] += 'a' - 10;
     }
     buf[i] = '\0';
}

char*
md5::encrypt(char* buffer) {
	_md5[0] = 0x67452301;
	_md5[1] = 0xefcdab89;
	_md5[2] = 0x98badcfe;
	_md5[3] = 0x10325476;

	fill(buffer);
	for (int i = 0; i < N; ++i) {
		roll(filled + 64 * i);
	}

	char* output_buffer = new char[256];
	output(output_buffer, _md5, sizeof(_md5));
	return output_buffer;
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

		md5 ins_md5;
		
		char* st = ins_md5.encrypt(buffer);
		cout << st << endl;
		delete st;
	}

	return 0;
}
