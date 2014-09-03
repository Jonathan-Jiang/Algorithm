//
// STL 全排列
// 构造全排列:
// 1. 增量构造，构造前缀之后递归构造下一个
// 2. swap 构造法，如下所示
// 3. STL 下一个排列构造法，算法思想见 next_permutation
//
#include <iostream>
using	namespace	std;
bool ok(int array[], int cur, int end) {
    // 只选之前没有出现过的数进行替换
    for (int i = cur; i < end; ++i) if (array[i] == array[end])
        return false;
    return true;
}

// 由于全排列就是从第一个数字起每个数分别与它后面的数字交换。我们先尝试加个这样的判断——如果一个数与后面的数字相同那么这二个数就不交换了。如122，第一个数与后面交换得212、221。然后122中第二数就不用与第三个数交换了，但对212，它第二个数与第三个数是不相同的，交换之后得到221。与由122中第一个数与第三个数交换所得的221重复了。所以这个方法不行。
// 换种思维，对122，第一个数1与第二个数2交换得到212，然后考虑第一个数1与第三个数2交换，此时由于第三个数等于第二个数，所以第一个数不再与第三个数交换。再考虑212，它的第二个数与第三个数交换可以得到解决221。此时全排列生成完毕。
// 这样我们也得到了在全排列中去掉重复的规则——去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。
void func(int array[], int cur, int num) {
    // cur 表示当前选取到第几个数，num 表示一共有多少数
    if (cur == num) { for (int i = 0; i <= num; ++i)
        cout << array[i] << " ";
        cout << endl;
    }
    for (int i = cur; i <= num; ++i) {
        // 第 i 个数分别与它后面的数字交换就能得到新的排列
        if (ok(array, cur, i)) {
            swap(array[cur], array[i]);
            func(array, cur + 1, num);
            swap(array[cur], array[i]);
        }
    }
}
int main(int argc, const char* argv[]) {
    int data[3] = { 1, 2, 2 };
    func(data, 0, 2);
    cout << endl;
    return 0;
}
