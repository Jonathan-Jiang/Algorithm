#include <iostream>
using	namespace	std;

const int cnt = 4;
const int INF = ~ (1 << sizeof(int) * 8 - 1);

const int graph[cnt][cnt] = {
	INF, 3, 5, 7,
	5, INF, 2, 3,
	6, 4, INF, 2,
	3, 4, 5, INF
};

// �ݹ�ʵ��
unsigned char bitmap = 0x0E;		// 1110b
int path[cnt][0x0F];
int TSP(int cur, unsigned int bitmap) {
	if (!bitmap) {
		path[cur][bitmap] = 0;
		return graph[cur][0];
	}

	int min = INF;
	for (int i = 0; i < cnt; ++i) {
		if (bitmap & (1 << i) && graph[cur][i] != INF) {
			bitmap &= ~ (1 << i);
			int t = graph[cur][i] + TSP(i, bitmap);
			bitmap |= 1 << i;
			if (min > t){
				min = t;
				path[cur][bitmap] = i;
			}
		}
	}

	return min;
}

// �ǵݹ�ʵ��
// d[cur][map] ��ʾ�� cur map bitmap ��ʶ���򼯺�ص�Դ�� 0 �����·��
// map ��ʶ����Ҫͨ�����򼯣�cur ��ʾĿǰ�ĳ�����
// d[cur][map] = min(graph[cur][one_adjacent] + d[one_adjacent][map �޳� one_adjacent]);
int d[cnt][0x0F];
int pre[cnt][0x0F];
void TSP() {
	d[0][0x00] = 0;
	memset(pre, 0, sizeof(pre));
	for (int i = 1; i < cnt; ++i)
		d[i][0x00] = graph[i][0];

	// ע��滮�ķ���
	// �˵ݹ�����Ҷ�ӽڵ�� map һ����ֻ����һ���ڵ����
	// ���Դ��򼯴�С����ķ�������̬�滮
	for (int map = 0x01; map < 0x0F; ++map) {
		for (int cur = 0; cur < cnt; ++cur) {
			// ��Ҫͨ�����򼯰����˵�ǰ�ڵ㣬���ǲ������
			if (map & (1 << cur)) continue;
				
			int min = INF;
			// i stands for one_adjacent
			for (int i = cnt - 1; i >= 0; --i) {
				if (map & (1 << i) && graph[cur][i] != INF) {
					int t = graph[cur][i] + d[i][map & ~ (1 << i)];
					if (min > t) {
						min = t;
						pre[cur][map] = i;
					}
				}
			}

			d[cur][map] = min;
		}
	}
}

int main(int argc, const char* argv[]) {
// #define DEBUG
#ifdef DEBUG
	memset(path, 0, sizeof(path));
	cout << TSP(0, bitmap) << endl;

	int cur = 0;
	int tmpBitmap = 0x0E;
	cout << 0 << " ==> ";
	while (path[cur][tmpBitmap]) {
		cout << (cur = path[cur][tmpBitmap]) << " ==> ";
		tmpBitmap &= ~ (1 << cur);
	}
	cout << 0 << endl;
#endif

	TSP();
// #define DEBUG
#ifdef DEBUG
	for (int i = 0; i < cnt; ++i) {
		for (int j = 0x00; j < 0x0F; ++j) {
			printf("%-5d", d[i][j]);
			if (j == 0x0F - 1) cout << endl;
		}
	}
#endif

	cout << d[0][0x0E] << endl;

	int cur = 0;
	int cur_map = 0x0E;
	cout << "0 ==> ";
	while (pre[cur][cur_map]) {
		cout << pre[cur][cur_map] << " ==> ";
		cur = pre[cur][cur_map];
		cur_map &= ~ (1 << cur);
	}
	cout << "0" << endl;

	return 0x00;
}
