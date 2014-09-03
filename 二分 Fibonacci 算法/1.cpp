/*
F(n+2)=F(n)+F(n-1)＝2*F(n-1)+F(n-2)=3*F(n-2)+2*F(n-4)
用归纳法很容易证明 F(n) = F(k)*F(n+1-k) + F(k-1)*F(n-k)，利用该递推公式和原递推公式，要计算F(n)，只要计算F([n/2])和F([n/2]+1)，时间复杂度为 O(lg n)。如：要计算F(58)，由 58 -> 29,30 -> 14,15 -> 7,8 -> 3,4 -> 1,2 可知只要算5次。可以用一个栈保存要计算的数，实际上，将n的最高位1（假设在第k位）左边的0去除掉后，第m次要计算的数是第k位到第k-m+1位这m个位组成的值t(m)，则第m-1次要计算的数为t(m-1)，且
t(m)=2*t(m-1)+(第k-m+1位是否为1)。
若第m-1次计算得到了f(k)和f(k+1)，则第m次计算：
 
第k-m+1位	已计算	待计算
1			f(k)	f(2*k+1),f(2*k+2)
0			f(k+1)	f(2*k),f(2*k+1)
*/


/*   Fibonacci数列第N个数的最后4位数
    注意，当 N>93 时 第N个数的值超过64位无符号整数可表示的范围。
F(n+2)=F(n)+F(n-1) F(0)=0 F(1)=1  F(2)=1        ==>
F(n)=F(k)*F(n+1-k) + F(k-1)*F(n-k)              ==>
F(2*n)=F(n+1)*F(n)+F(n)*F(n-1)=(F(n+1)+F(n-1))*F(n)=(F(n+1)*2-F(n))*F(n)
F(2*n+1)=F(n+1)*F(n+1)+F(n)*F(n)
F(2*n+2)=F(n+2)*F(n+1)+F(n+1)*F(n)=(F(n+2)+F(n))*F(n+1)=(F(n+1)+F(n)*2)*F(n+1)
*/

unsigned fib_last4(unsigned num)
{
  if (num == 0) return 0;
  const unsigned M=10000;
  unsigned ret=1,next=1,ret_=ret;
  unsigned flag=1, tt=num;
  while (tt >>= 1) flag <<= 1;
  while (flag >>= 1){
    if (num & flag){
      ret_ = ret * ret + next * next;
      next = (ret + ret + next) * next;
    } else {
      //多加一个M，避免 2*next-ret是负数，造成结果不对
      ret_ = (next + next + M - ret) * ret;
      next = ret * ret + next * next;
    }
    ret = ret_ % M;
    next = next % M;
  }
  return ret;
}

#include <iostream>
using	namespace	std;

int func(int num) {
    if (0 == num) return 1;

    int k = 0;
    int tmp = num;
    while (tmp >>= 1) k += 1;

    int n = 1;
	int last_fn = 1;
	int last_fn1 = 1;
	int fn;
	int fn1;

    while (n != num) {
		n = num >> k;
		--k;
		if (n == 1) {
			fn = last_fn;
			fn1 = last_fn1;
			goto final;
		}

		if (n & 1) {
			// is odd
			fn = last_fn1 * last_fn1 + last_fn * last_fn;
			fn1 = (last_fn1 + 2 * last_fn) * last_fn1;
		} else {
			// is even
			fn = (2 * last_fn1 - last_fn) * last_fn;
			fn1 = last_fn1 * last_fn1 + last_fn * last_fn;
		}

final:
		last_fn = fn;
		last_fn1 = fn1;
    }

	return fn;
}

int main(int argc, const char* argv[]) {
	// for (int i = 0; i < 10; ++i)
		// cout << i << " : " << func(i) << endl;

	cout << func(8) << endl;

	return 0;
}
