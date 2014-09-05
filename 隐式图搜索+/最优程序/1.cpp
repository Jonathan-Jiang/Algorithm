#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using	namespace	std;

enum ops {ADD, SUB, MUL, DIV, DUP};

struct program {
    int n;
    ops code[100];

    program(const program& p_p) {
        this->n = p_p.n;
        for (int i = 0; i < n; ++i)
            this->code[i] = p_p.code[i];
    }

    program(ops p_c) {
        code[0] = p_c;
        this->n = 1;
    }

    program operator+(ops p_c) {
        program p(*this);
        p.code[p.n++] = p_c;
        return p;
    }

    void print() {
        for (int i = 0; i < n; ++i)
            if (code[i] == ADD)
                cout << "ADD" << " ";
            else if (code[i] == SUB)
                cout << "SUB" << " ";
            else if (code[i] == MUL)
                cout << "MUL" << " ";
            else if (code[i] == DIV)
                cout << "DIV" << " ";
            else
                cout << "DUP" << " ";
        cout << endl;
    }
};

int run(stack<int>& s, ops n) {
    int a = s.top(), b;
    s.pop();
    switch (n) {
        case ADD:
            if (s.empty()) return -1;
            b = s.top();
            s.pop();
            s.push(a + b);
            break;
        case SUB:
            if (s.empty()) return -1;
            b = s.top();
            s.pop();
            s.push(b - a);
            break;
        case MUL:
            if (s.empty()) return -1;
            b = s.top();
            s.pop();
            s.push(a * b);
            break;
        case DIV:
            if (a == 0 || s.empty()) return -1;
            b = s.top();
            s.pop();
            s.push(b / a);
            break;
        case DUP:
            s.push(a);
            s.push(a);
            break;
    }
    return 0;
}

int test(program p, int a, int b) {
    stack<int> s;
    s.push(a);
    for (int i = 0; i < p.n; ++i)
        if (run(s, p.code[i]) == -1)
            // error
            return -1;
    // find a program
    if (s.top() == b) return 0;
    // can run properly
    else return 1;
}

void bfs(pair<int, int> p[], int n) {
    queue<program> q;
    program root(DUP);
    q.push(root);
    while (!q.empty()) {
        program cur_node = q.front();
        q.pop();
        for (int i = 0; i < 5; ++i) {
            ops op = static_cast<ops>(i);
            program next_node = cur_node + op;
            bool all_ok = true;
            for (int i = 0; i < n; ++i) {
                int a = p[i].first;
                int b = p[i].second;
                int test_result = test(next_node, a, b);
                if (test_result == -1)
                    all_ok = false;
                else if (test_result == 1) {
                    q.push(next_node);
                    all_ok = false;
                }
            }
            if (all_ok) {
                next_node.print();
                return;
            }
        }
    }
}

int main() {
    int a, b, n = 0;
    pair<int, int> p[100];

    while (cin >> a >> b)
        p[n++] = pair<int, int>(a, b);
    bfs(p, n);

    return 0;
}
