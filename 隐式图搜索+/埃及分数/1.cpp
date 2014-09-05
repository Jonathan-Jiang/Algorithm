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

    bool test(int a, int b) {
        if (n == 1) return a == 1 && b == this->denominator[0];
        int c = gcd(this->denominator[0], this->denominator[1]);
        for (int i = 2; i < n; ++i)
            c = gcd(c, this->denominator[i]);

        // c 为所有分母的最大公约数
        int sum = 1, numerator = 0;
        for (i = 0; i < n; ++i)
            sum *= this->denominator[i] / c;
        // sum 为所有分母的最小公倍数
        sum *= c;
        for (i = 0; i < n; ++i)
            numerator += sum / this->denominator[i];

        c = gcd(numerator, sum);
        return a == numerator / c && b == sum / c;
    }

    void print() {
        for (int i = 0; i < n - 1; ++i)
            cout << 1 << "/" << this->denominator[i] << " + ";
        cout << 1 << "/" << this->denominator[n - 1] << endl;
    }
};

int dfs(int d, int a, int b) {
    for (int r = 2;; ++r) {
        int cur_depth = 1;
        stack<answer*> s;
        answer* root = new answer(r);

		int next_min_number = r + 1;
		double total_sum = static_cast<double>(a) / b;
		double cur_sum = 1.0 / r;
		bool negative = (total_sum - cur_sum < 0);
		int remain = ceil((total_sum - cur_sum) * next_min_number);

		if (negative) continue;
		else if (remain + cur_depth > d) return 1;

        s.push(root);
        while (!s.empty()) {
            answer* cur_node = s.top();
			answer* next_node = new answer();
			*next_node = cur_node->get_next();

            next_min_number = next_node->denominator[next_node->n - 1] + 1;
			total_sum = static_cast<double>(a) / b;
			cur_sum = next_node->get_sum();
			negative = (total_sum - cur_sum < 0);
            remain = ceil((total_sum - cur_sum) * next_min_number);

			if (negative) continue;
			else if (remain + cur_depth > d)
                // 剪枝
				if (cur_depth == 1) return 1;
				else break;
            else if (next_node->test(a, b)) {
                cout << a << "/" << b << " = ";
				next_node->print();
                return 0;
            } else s.push(next_node);
            ++cur_depth;
            if (cur_depth > d) {
                s.pop();
                --cur_depth;
            }
        }
    }
}

int main() {
    int a, b;
    cin >> a >> b;
    // 迭代加深搜索
    for (int d = 1;; ++d)
        // 枚举搜索的深度 d
        if (!dfs(d, a, b)) break;

    return 0;
}
