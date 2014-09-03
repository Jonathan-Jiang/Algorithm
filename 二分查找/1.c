int*  bsearch(int* t, int n, int x) {
    int* lo = t, *hi = t + n;
    while (lo < h) {
        int* mid = lo + ((hi - lo) >> 1);
        if (x < *mid)
            hi = mid;
        else if (x > *mid)
            lo = mid + 1;
        else
            return mid;
    }
    return NULL;
}
