// *
// * 求 N 个实数相邻的数的之间最大的间隙
// * 采用分桶策略
// * 将 N 个数放于 N - 1 个桶中
// * 每个桶大小相同，也就是用 N - 2 个数将 N 个数中最大最小的数之间隔出 N - 1 个区间
// * 根据抽屉原理，必然有一个桶是空的，并且最大的间隙必然出现在空桶的前面桶的最小值和后面桶的最大值之间
// *

#include <iostream>
#include <math.h>
using	namespace	std;

#define	LENGTH	6

double max = 0, min = 0;
const double EPS = 0.0001;
const double data[LENGTH] = {
	1, 2, 3, 5, 6, 7
};

typedef struct node {
	bool is_empty;
	double front;
	double back;
	double from;
	double to;

	node() {
		is_empty = true;
		front = max;
		back = min;
		from = 0.0;
		to = 0.0;
	}

} bucket_node, *ptr_bucket_node;

typedef struct {
	ptr_bucket_node bucket[LENGTH];
} bucket_list;

bucket_list bl;

void find_max_min() {
	max = min = data[0];
	for (int i = 1; i < LENGTH; ++i) {
		if (data[i] - max > EPS) {
			max = data[i];
		}
		if (min - data[i] > EPS) {
			min = data[i];
		}
	}
}

void build_bucket(double bucket_size) {
	double from = min;
	for (int i = 0; i < LENGTH - 1; ++i, from += bucket_size) {
		bl.bucket[i] = new bucket_node();
		bl.bucket[i]->from = from;
		bl.bucket[i]->to = from + bucket_size;
	}
}

void fill_bucket() {
	for (int i = 0; i < LENGTH; ++i) {
		for (int j = 0; j < LENGTH - 1; ++j) {
			if ((data[i] - bl.bucket[j]->from > EPS || fabs(data[i] - bl.bucket[j]->from) < EPS) && bl.bucket[j]->to - data[i] > EPS) {
				bl.bucket[j]->is_empty = false;

				if (bl.bucket[j]->front - data[i] > EPS || fabs(bl.bucket[j]->front - data[i]) < EPS) {
					bl.bucket[j]->front = data[i];
				}

				if (data[i] - bl.bucket[j]->back > EPS) {
					bl.bucket[j]->back = data[i];
				}
			}
		}
	}
}

void find_and_print() {
	for (int i = 0; i < LENGTH - 1; ++i) {
		if (bl.bucket[i]->is_empty) {
			int most_front = bl.bucket[i - 1]->front;
			int most_back = bl.bucket[i + 1]->back;
			cout << most_front << " ==> " << most_back << endl;
			cout << most_back - most_front << endl;
			break;
		}
	}
}

int main(int argc, const char* argv[]) {
	find_max_min();
	double bucket_size = (max - min) / (LENGTH - 1);
	build_bucket(bucket_size);
	fill_bucket();
	find_and_print();

	return 0;
}
