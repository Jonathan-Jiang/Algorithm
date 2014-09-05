#include <iostream>
#include <algorithm>
#include <stack>
#include <math.h>
using	namespace	std;

int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

#define EQUAL   0
#define NEGATIVE   -1 
#define POSITIVE    1 

const int INF = ~(1 << (sizeof(int) * 8 - 1));

struct answer {
    int n;
    // 下一个状态节点应该在后面加上的数
    // 如 (2, 3) 节点
    // 第一次的后继节点应该是 (2, 3, 4)
    // 第二次的后继节点应该是 (2, 3, 5)
    int next;
    int denominator[100];

	answer() {}

    answer(const answer& p_a) {
        this->n = p_a.n;
        for (int i = 0; i < n; ++i)
            this->denominator[i] = p_a.denominator[i];
        this->next = this->denominator[n - 1] + 1;
    }

    answer(int p_d) {
        denominator[0] = p_d;
        this->n = 1;
        this->next = p_d + 1;
    }

    // 每一次扩展时的后继结点
    answer get_next() {
        answer a(*this);
        a.denominator[a.n++] = this->next;
        a.next = a.denominator[a.n - 1] + 1;
		++this->next;
        return a;
    }

    double get_sum() {
        double sum = 0.0;
        for (int i = 0; i < n; ++i)
            sum += 1.0 / this->denominator[i];
        return sum;
    }

    // 如果当前分数之和大于 a/b，返回 NEGATIVE
    // 如果当前分数之和等于 a/b，返回 EQUAL
    // 如果当前分数之和小于 a/b，返回 POSITIVE
    int test(int a, int b) {
        // 最简约化后分数和的分子 nume
        // 最简约化后分数和的分母 deno
        int nume = 0, deno = 1;

        if (n == 1 && a == 1 && b == this->denominator[0])
            return EQUAL;
        else if (n == 1) {
            nume = 1;
            deno = this->denominator[0];
        } else {
            // c 为所有分母的最大公约数
            int c = gcd(this->denominator[0], this->denominator[1]);
            for (int i = 2; i < n; ++i)
                c = gcd(c, this->denominator[i]);

            for (i = 0; i < n; ++i)
                deno *= this->denominator[i] / c;
            deno *= c;
            for (i = 0; i < n; ++i)
                nume += deno / this->denominator[i];

            // 分子分母的最大公约数
            c = gcd(nume, deno);
            nume /= c;
            deno /= c;
        }
        if (a == nume && b == deno) return EQUAL;
        int tmp = deno / gcd(deno, b) * b;
        if (tmp / deno * nume - tmp / b * a > 0) return NEGATIVE;
        else return POSITIVE;
    }

    void print() {
        for (int i = 0; i < n - 1; ++i)
            cout << 1 << "/" << this->denominator[i] << " + ";
        cout << 1 << "/" << this->denominator[n - 1] << endl;
    }
};

int dfs(int d, int a, int b, answer** ans) {
    // cur_depth_min 记录了可行解的最小层，也就是分数个数最少的解
    // cur_min 记录了当前层所找到的末尾数最小的数
    // find = 1 表示未找到可行解
    // find = 0 表示找到了至少一组可行解
    int cur_depth_min = INF, cur_min = INF, find = 1;
    for (int r = 2;; ++r) {
        int cur_depth = 1;
        stack<answer*> s;
        answer* root = new answer(r);

		int next_min_number = r + 1;
		double total_sum = static_cast<double>(a) / b;
        // negative 表示，当前状态节点的分数之和已经大于 a/b 了
        // 这个状态节点及其之和的子树都可以直接剪掉了
		int negative = root->test(a, b);
		int remain = ceil((total_sum - 1.0 / r) * next_min_number);

		if (negative == NEGATIVE) continue;
		else if (remain + cur_depth > d) return find;

        s.push(root);
        while (!s.empty()) {
            answer* cur_node = s.top();
			answer* next_node = new answer();
			*next_node = cur_node->get_next();

            next_min_number = next_node->denominator[next_node->n - 1] + 1;
			negative = next_node->test(a, b);
            remain = ceil((total_sum - next_node->get_sum()) * next_min_number);

			if (negative == NEGATIVE) continue;
			else if (remain + cur_depth > d)
                // 剪枝
				if (cur_depth == 1) return find;
				else break;
            else if (next_node->test(a, b) == EQUAL) {
                if (cur_depth <= cur_depth_min && next_node->denominator[next_node->n - 1] < cur_min) {
					cur_depth_min = cur_depth;
					cur_min = next_node->denominator[next_node->n - 1];
                    *ans = next_node;
                    find = 0;
				}
            } else s.push(next_node);
            ++cur_depth;
            if (cur_depth > d) {
                s.pop();
                --cur_depth;
            }
        }
    }
    return find;
}

int main() {
    answer* ans;
    int a, b;
    cin >> a >> b;
    if (a == 1) {
        cout << a << "/" << b << " = " << a << "/" << b << endl;
        return 0;
    }
	int p_a = a / gcd(a, b);
	int p_b = b / gcd(a, b);
    // 迭代加深搜索
    for (int d = 1;; ++d)
        // 枚举搜索的深度 d
        if (!dfs(d, p_a, p_b, &ans)) {
            cout << a << "/" << b << " = ";
            ans->print();
            break;
        }

    return 0;
}
