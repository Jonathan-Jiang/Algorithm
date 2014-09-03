#include <iostream>
#include <vector>
using	namespace	std;

const int INF = ~ (1 << (sizeof(int) * 8 - 1));

const int t = 8;			// �ܽڵ����

typedef struct _edge {
	int weight;				// Ȩ��
	int vertex;				// �ɴ�ڵ�
	_edge* next;

	_edge() {
		weight = vertex = 0;
		next = NULL;
	}
} edge, * ptr_edge;

vector< ptr_edge > graph(t);
int shortest[t];

/* ԭͼ��
 * Դ�ڵ� 0��Ŀ��ڵ� 7
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

// �����ڽӾ�����ಿͼ���ಿͼ�����ڽӱ�洢
void InitGraph(void) {
	// ��ʼ�������ͷ
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

	// �Ӻ���ǰ��
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
