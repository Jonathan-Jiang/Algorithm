#include <iostream>
using    namespace    std;

struct node {
   node *next;
   int data;

   node() {}

   node(int p_data) {
       data = p_data;
       next = NULL;
   }

   ~node() {
       cout << data << "\t deleted" << endl;
   }
};

node *head = new node(11);

void build_link() {
    node *cur = head;
    for (int i = 0; i < 6; ++i) {
        node *x = new node(i);
        cur->next = x;
        cur = x;
    }
}

typedef bool (*remove_fn)(node* v);

bool func(node* v) {
	return v->data & 1;
}

node *remove_if(node **head, remove_fn rm) {
	for (node **cur = head; *cur;) {
        node *entry = *cur;
        if (rm(entry)) {
            *cur = entry->next;
            return entry;
        } else cur = &entry->next;
    }
	return NULL;
}


int main(int argc, char* const argv[]) {
	build_link();

    node *tmp;
    while (tmp = remove_if(&head, func)) {
        cout << tmp->data << endl;
		delete tmp;
    }

    return 0;
}
