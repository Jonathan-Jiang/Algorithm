#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using    namespace    std;

bool first_higher(char first, char second) {
    if (first == '+' && second == '+') return true;
    if (first == '+' && second == '-') return true;
    if (first == '-' && second == '+') return true;
    if (first == '-' && second == '-') return true;
    if (first == '*' && second == '+') return true;
    if (first == '*' && second == '-') return true;
    if (first == '*' && second == '*') return true;
    if (first == '*' && second == '/') return true;
    if (first == '/' && second == '+') return true;
    if (first == '/' && second == '-') return true;
    if (first == '/' && second == '*') return true;
    if (first == '/' && second == '/') return true;
	if (second == '(') return true;
    if (second == ')') return true;
    return false;
}

int get_num(int num, int new_num) {
    return 10 * num + new_num;
}

struct Node {
    Node(int p_data, bool p_is_op = false) : data(p_data), is_op(p_is_op), lchild(NULL), rchild(NULL) {}
    bool is_op;
    int data;
    Node *lchild, *rchild;
};

// 逆波兰算法，得到后缀表达式
void func(char formula[], vector<Node*> &ve) {
    stack<char> op_st;
	for (int i = 0; i < strlen(formula); ++i) {
        if (isdigit(formula[i])) {
            int num = 0;
            while (isdigit(formula[i])) {
                num = get_num(num, formula[i] - '0');
                ++i;
            }
            ve.push_back(new Node(num));
        }

		if (i == strlen(formula)) {
			while (!op_st.empty()) {
				ve.push_back(new Node(op_st.top(), true));
				op_st.pop();
			}
		}

        if (formula[i] == ')') {
            while (op_st.top() != '(') {
                ve.push_back(new Node(op_st.top(), true));
                op_st.pop();
            }
            op_st.pop();
        } else if (op_st.empty() || formula[i] == '(') {
			op_st.push(formula[i]);
		} else if (first_higher(formula[i], op_st.top())) {
            op_st.push(formula[i]);
        } else {
            while (!first_higher(formula[i], op_st.top())) {
                ve.push_back(new Node(op_st.top(), true));
                op_st.pop();
            }
            op_st.push(formula[i]);
        }
    }
}

// 构建语法树
Node *build_tree(vector<Node*> &ve) {
    stack<Node*> st;
    for (vector<Node*>::iterator it = ve.begin(); it != ve.end(); ++it) {
        if ((*it)->is_op) {
            Node *node1 = st.top();
            st.pop();
            Node *node2 = st.top();
            st.pop();
            (*it)->lchild = node2;
            (*it)->rchild = node1;
            st.push(*it);
        } else st.push(*it);
    }
	return st.top();
}

void post_order(Node *root) {
    if (root->lchild) post_order(root->lchild);
    if (root->rchild) post_order(root->rchild);
    if (root->is_op) cout << (char)root->data << " ";
    else cout << root->data << " ";
}

void print(Node *ve) {
    if (ve->is_op) cout << (char)ve->data << " ";
    else cout << ve->data << " ";
}

int main(int argc, char* const argv[]) {
    char formula[] = "3+(2-5)*6/3";
    vector<Node*> ve;

    func(formula, ve);

    for_each(ve.begin(), ve.end(), print);
	cout << endl;

    post_order(build_tree(ve));
    cout << endl;

    return 0;
}
