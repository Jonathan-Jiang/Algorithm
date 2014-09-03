/*
F(n+2)=F(n)+F(n-1)��2*F(n-1)+F(n-2)=3*F(n-2)+2*F(n-4)
�ù��ɷ�������֤�� F(n) = F(k)*F(n+1-k) + F(k-1)*F(n-k)�����øõ��ƹ�ʽ��ԭ���ƹ�ʽ��Ҫ����F(n)��ֻҪ����F([n/2])��F([n/2]+1)��ʱ�临�Ӷ�Ϊ O(lg n)���磺Ҫ����F(58)���� 58 -> 29,30 -> 14,15 -> 7,8 -> 3,4 -> 1,2 ��ֻ֪Ҫ��5�Ρ�������һ��ջ����Ҫ���������ʵ���ϣ���n�����λ1�������ڵ�kλ����ߵ�0ȥ�����󣬵�m��Ҫ��������ǵ�kλ����k-m+1λ��m��λ��ɵ�ֵt(m)�����m-1��Ҫ�������Ϊt(m-1)����
t(m)=2*t(m-1)+(��k-m+1λ�Ƿ�Ϊ1)��
����m-1�μ���õ���f(k)��f(k+1)�����m�μ��㣺
 
��k-m+1λ	�Ѽ���	������
1			f(k)	f(2*k+1),f(2*k+2)
0			f(k+1)	f(2*k),f(2*k+1)
*/


/*   Fibonacci���е�N���������4λ��
    ע�⣬�� N>93 ʱ ��N������ֵ����64λ�޷��������ɱ�ʾ�ķ�Χ��
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
      //���һ��M������ 2*next-ret�Ǹ�������ɽ������
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
