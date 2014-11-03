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

union Data {
    int num;
    char op;
};

struct Node {
    Node(char p_op) : is_op(true), lchild(NULL), rchild(NULL) {
		data.op = p_op;
	}
    Node(int p_num) : is_op(false), lchild(NULL), rchild(NULL) {
		data.num = p_num;
	}
    bool is_op;
	Data data;
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
				ve.push_back(new Node(op_st.top()));
				op_st.pop();
			}
		}

        if (formula[i] == ')') {
            while (op_st.top() != '(') {
                ve.push_back(new Node(op_st.top()));
                op_st.pop();
            }
            op_st.pop();
        } else if (op_st.empty() || formula[i] == '(') {
			op_st.push(formula[i]);
		} else if (first_higher(formula[i], op_st.top())) {
            op_st.push(formula[i]);
        } else {
            while (!first_higher(formula[i], op_st.top())) {
                ve.push_back(new Node(op_st.top()));
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
    if (root->is_op) cout << root->data.op << " ";
    else cout << root->data.num << " ";
}

void print(Node *ve) {
    if (ve->is_op) cout << ve->data.op << " ";
    else cout << ve->data.num << " ";
}

int calculate(vector<Node*> &ve) {
    stack<int> st;
    for (vector<Node*>::iterator it = ve.begin(); it != ve.end(); ++it) {
        if ((*it)->is_op) {
            int num1 = st.top();
            st.pop();
            int num2 = st.top();
            st.pop();
            if ((*it)->data.op == '+') {
                st.push(num2 + num1);
            } else if ((*it)->data.op == '-') {
                st.push(num2 - num1);
            } else if ((*it)->data.op == '*') {
                st.push(num2 * num1);
            } else if ((*it)->data.op == '/') {
                st.push(num2 / num1);
            }
        } else st.push((*it)->data.num);
    }
	return st.top();
}

int main(int argc, char* const argv[]) {
    char formula[] = "3+(2-5)*6/3";
    vector<Node*> ve;

    func(formula, ve);

    for_each(ve.begin(), ve.end(), print);
	cout << endl;

    post_order(build_tree(ve));
    cout << endl;

	cout << calculate(ve) << endl;

    return 0;
}
