// *
// * vis �����¼�˴�ֱ�������������Խ�������Щ�Ѿ���ռ����
// * queen ������ for ѭ����ԭ����
// * ��ٵ�ǰ�ʺ���Է��õ� 8 ����
// * ͬʱ�ж� vis �������¼������(�����ϲ����ܳ�ͻ)�����Ƿ��ѱ�ռ��
// * ���û��ռ�õݹ���һ��
// * ʵ���� cur ���ǵ�ǰ�ʺ����ڵ�����
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
