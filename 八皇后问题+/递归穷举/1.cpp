// *
// * vis 数组记录了垂直方向、两条正负对角线有哪些已经被占用了
// * queen 函数中 for 循环的原理是
// * 穷举当前皇后可以放置的 8 个列
// * 同时判断 vis 数组里记录的三个(横向上不可能冲突)方向是否已被占用
// * 如果没被占用递归下一个
// * 实际上 cur 就是当前皇后所在的行数
// *

#include <iostream>
using	namespace	std;

int n = 8;
int cnt = 0;
int vis[3][20];

void queen(int cur) {
	if (n == cur) ++cnt;
	else for (int i = 0; i < n; ++i) {
		if (!vis[0][i] && !vis[1][cur + i] && !vis[2][cur - i + n]) {
			vis[0][i] = vis[1][cur + i] = vis[2][cur - i + n] = 1;
			queen(cur + 1);
			vis[0][i] = vis[1][cur + i] = vis[2][cur - i + n] = 0;
		}
	}
}

int main() {
	memset(vis, 0, sizeof(vis));
	queen(0);
	printf("%d\n", cnt);

	return 0;
}
