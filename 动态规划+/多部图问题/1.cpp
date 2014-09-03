#include <iostream>
#include <vector>
using	namespace	std;

const int INF = ~ (1 << (sizeof(int) * 8 - 1));

const int t = 8;			// 总节点个数

typedef struct _edge {
	int weight;				// 权重
	int vertex;				// 可达节点
	_edge* next;

	_edge() {
		weight = vertex = 0;
		next = NULL;
	}
} edge, * ptr_edge;

vector< ptr_edge > graph(t);
int shortest[t];

/* 原图是
 * 源节点 0，目标节点 7
 *		> 1 --> 4 \
 *    /    \   /    \
 *  /	    / \       \
 * 0 ---> 2      5 ---> 7
 *  \                  /
 *    \              /
 *      > 3 ---> 6 /
 */


int orginalGraph[t][t] = {
	INF, 4, 2, 3, INF, INF, INF, INF,
	INF, INF, INF, INF, 7, 6, INF, INF,
	INF, INF, INF, INF, 5, INF, INF, INF,
	INF, INF, INF, INF, INF, INF, 2, INF,
	INF, INF, INF, INF, INF, INF, INF, 5,
	INF, INF, INF, INF, INF, INF, INF, 4,
	INF, INF, INF, INF, INF, INF, INF, 6,
	INF, INF, INF, INF, INF, INF, INF, INF,
};

// 根据邻接矩阵构造多部图，多部图采用邻接表存储
void InitGraph(void) {
	// 初始化链表的头
	for (vector< ptr_edge >::iterator it = graph.begin(); it != graph.end(); ++it)
		*it = new edge();

	for (int i = 0; i < t; ++i) {
		for (int j = 0; j < t; ++j) {
			if (orginalGraph[i][j] != INF) {
				ptr_edge new_edge = new edge();
				new_edge->weight = orginalGraph[i][j];
				new_edge->vertex = j;

				ptr_edge tmp = graph[i];
				while (tmp->next) tmp = tmp->next;

				tmp->next = new_edge;
			}
		}
	}
}

void PrintPath(int source, int dst, int max) {
	int curSource = source;
	while (curSource != dst) {
		for (int i = 0; i < t; ++ i) {
			if (orginalGraph[curSource][i] != INF && \
				shortest[i] == shortest[curSource] - orginalGraph[curSource][i]) {
				cout << curSource << endl;
				curSource = i;
			}
		}
	}
	cout << dst << endl;
}

int main(int argc, const char* argv[]) {
//	InitGraph();

	// 从后往前推
	for (int i = 0; i < t; ++i) {
		shortest[i] = INF;
	}
	shortest[t - 1] = 0;

	for (i = t - 2; i >= 0; --i) {
		for (int j = 0; j < t; ++j) {
			if (orginalGraph[i][j] != INF)
				if (shortest[i] > shortest[j] + orginalGraph[i][j])
					shortest[i] = shortest[j] + orginalGraph[i][j];
		}
	}

	cout << shortest[0] << endl;

	PrintPath(0, 7, shortest[0]);

	return 0x00; 
}
