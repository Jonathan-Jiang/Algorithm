#include <iostream>
#include <stack>
using   namespace   std;

struct Node {
    int data;
    Node *left, *right;

    Node(int p_data, Node *p_left = NULL, Node *p_right = NULL) : data(p_data), left(p_left), right(p_right) {}
};

class Iterator {
public:
	virtual Node *next() = 0;
};

class InorderIterator : public Iterator {
public:
	InorderIterator(Node *node) {
		current = node;
		mStack.push(current);
		while (current->left) {
			mStack.push(current->left);
			current = current->left;
		}
	}

	virtual Node *next() {
		if (mStack.empty()) return NULL;

		Node *top = mStack.top();
		mStack.pop();
		if (top->right) {
			mStack.push(top->right);
			current = top->right;
			while (current->left) {
				mStack.push(current->left);
				current = current->left;
			}
		}
		return top;
	}

	Node *operator*() {
		return current;
	}
private:
	Node *current;
	stack<Node*> mStack;
};

void
func(Node *node) {
	stack<Node*> stack;
	stack.push(node);
	do {
		while (node->left) {
			stack.push(node->left);
			node = node->left;
		}
		Node *top = stack.top();
		stack.pop();
		cout << top->data << " ";
		if (NULL != top->right) {
			stack.push(top->right);
			node = top->right;
		}
	}
	while (!stack.empty());
}

int
main(int argc, char *const argv[]) {
    Node *root = new Node(1);
    Node *node2 = new Node(2);
    Node *node3 = new Node(3);
    Node *node4 = new Node(4);
    Node *node5 = new Node(5);
    Node *node6 = new Node(6);
    Node *node7 = new Node(7);
    Node *node8 = new Node(8);
    Node *node9 = new Node(9);

    root->left = node2;
    root->right = node3;

    node2->left = node4;
    node2->right = node5;

    node4->left = node6;
    node4->right = node7;

    node7->left = node8;
    node7->right = node9;

	func(root);
	cout << endl;

	InorderIterator i(root);
	while (Node *t = i.next()) {
		cout << t->data << " ";
	}

    return 0;
}
