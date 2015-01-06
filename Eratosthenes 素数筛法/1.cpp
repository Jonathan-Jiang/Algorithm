#include <iostream>
#include <math.h>
using    namespace    std;

void Eratosthenes(bool prime_table[], int n) {
    prime_table[2] = true;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (prime_table[i]) {
            for (int j = 2; j <= n / i; ++j) {
                prime_table[i * j] = false;
            }
        }
    }
}

void print(bool prime_table[], int n) {
    for (int i = 2; i < n; ++i)
        if (prime_table[i]) cout << i << endl;
}

int main(int argc, char* const argv[]) {
    bool prime_table[25];
    Eratosthenes(prime_table, 25);
    print(prime_table, 25);

    return 0;
}
