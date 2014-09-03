#include <vector>
#include <iostream>
#include <assert.h>
#include <stack>
using	namespace	std;

const int len = 8;
int n[len] = {
	49, 38, 65, 97,
	76, 13, 27, 49
};

int partion(int n[], int low, int high) {
	int cursor = n[low];

	while (low < high) {
		while (n[high] >= cursor && low < high) --high;
		n[low] = n[high];
		while (n[low] <= cursor && low < high) ++low;
		n[high] = n[low];
	}

	n[low] = cursor;
	return low;
}

void quick_sort(int n[],int low,int high){
    stack< int > st;
    if(low < high) {
        int mid = partion(n, low, high);
        if (low < mid - 1) {
            st.push(low);
            st.push(mid - 1);
        }
        if (mid + 1 < high) {
            st.push(mid + 1);
            st.push(high);
        }
        //��ʵ������ջ����ÿһ���������Ӵ�����βԪ���±꣬��һ��whileѭ��ʱȡ�������Χ������������н���partition����
        while (!st.empty()) {
            int q = st.top();
            st.pop();
            int p = st.top();
            st.pop();
            mid = partion(n, p, q);
            if (p < mid - 1){
                st.push(p);
                st.push(mid - 1);
            }
            if (mid + 1 < q) {
                st.push(mid + 1);
                st.push(q);
            }      
        }
    }
}

int main() {
	quick_sort(n, 0, len - 1);

	for (int i = 0; i < len; ++i) cout << n[i] << " ";
	cout << endl;

	return 0;
}
