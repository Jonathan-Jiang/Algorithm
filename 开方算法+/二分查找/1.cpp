#include <iostream>
#include <math.h>
using    namespace    std;

double _sqrt(double n) {
    double low = 0;
    double high = n;
    do {
        double mid = low + (high - low) / 2;
        if (fabs(mid * mid - n) < 0.0000001) {
            return mid;
        } else if (mid * mid > n) {
            high = mid;
			// high = mid + 1
			// not valid
        } else {
            low = mid;
			// low = mid - 1
			// not valid
        }
    } while (low <= high);
}

int main(int argc, char* const argv[]) {
    for (int i = 0; i < 10; ++i) {
        cout << _sqrt(i) << endl;
    }

    return 0;
}
