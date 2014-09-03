#include <iostream>
#include <string>
using	namespace	std;

#define BODY_LEN	20

#define MOVE(d, x, y) MOVE_##d(x, y)
#define MOVE_N(x, y) (x, --y)
#define MOVE_S(x, y) (x, ++y)
#define MOVE_W(x, y) (--x, y)
#define MOVE_E(x, y) (++x, y)

#define SUCC		0
#define	RAN_OFF		1
#define	RAN_INTO	2

//²âÊÔÓÃÀý
// 18
// NWWWWWWWWWWSESSSWS
// 20
// SSSWWNENNNNNWWWWSSSS
// 30
// EEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
// 13
// SWWWWWWWWWNEE
// 0

void
backword(int x[], int y[]) {
	for (int i = BODY_LEN - 1; i > 0; --i) {
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
}

int
checkState(int x[], int y[]) {
	if (x[0] < 0 || x[0] > 49 || y[0] < 0 || y[0] > 49)
		return RAN_OFF;
	for (int i = 1; i < BODY_LEN; ++i)
		if (x[0] == x[i] && y[0] == y[i])
			return RAN_INTO;
	return SUCC;
}

void
run(char step[], int n) {
	// (x[0], y[0]) is the position of the head
	int x[BODY_LEN], y[BODY_LEN];
	for (int i = 0; i < BODY_LEN; ++i) {
		x[i] = 29 - i;
		y[i] = 25;
	}

	for (i = 0; i < n; ++i) {
		backword(x, y);
		if (step[i] == 'N') {
			MOVE(N, x[0], y[0]);
		} else if (step[i] == 'S') {
			MOVE(S, x[0], y[0]);
		} else if (step[i] == 'W') {
			MOVE(W, x[0], y[0]);
		} else if (step[i] == 'E') {
			MOVE(E, x[0], y[0]);
		}
		int state = checkState(x, y);
		if (state == RAN_OFF) {
			printf("The worm ran off the board on move %d\n", i + 1);
			return;
		} else if (state == RAN_INTO) {
			printf("The worm ran into itself on move %d\n", i + 1);
			return;
		}
	}
	printf("The worm successfully made all %d moves\n", n);
}

int
main() {
	int n;
	char step[100];
	while (scanf("%d", &n), n != 0) {
		scanf("%s", step);
		run(step, n);
	}

	return 0;
}