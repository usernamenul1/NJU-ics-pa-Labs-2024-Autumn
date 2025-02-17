#include <stdint.h>

uint64_t ac[150], bc[150], mc[70], mt[150];
uint64_t al, bl, ml, cl;

void initab(uint64_t a, uint64_t b, uint64_t m) {
    for (int i = 0; i < 150; ++i){
        ac[i]=0;
    }
    for (int i = 0; i < 150; ++i){
        bc[i]=0;
    }for (int i = 0; i < 70; ++i){
        mc[i]=0;
    }for (int i = 0; i < 150; ++i){
        mt[i]=0;
    }
    al = 0, bl = 0, ml = 0, cl = 0;
    while (a) {
        ac[al] = a - ((a >> 1) << 1);
        a >>= 1;
        al++;
    }
    while (b) {
        bc[bl] = b - ((b >> 1) << 1);
        b >>= 1;
        bl++;
    }
    while (m) {
        mc[ml] = m - ((m >> 1) << 1);
        m >>= 1;
        ml++;
    }
}

void mut() {
    uint64_t dl = al + bl;
    for (uint64_t i = 0; i < dl; i++) {
        for (uint64_t j = 0; j <= i; j++) {
            mt[i] += ac[j] && bc[i - j];
        }
    }
}

void fmt() {
    for (uint64_t i = 0; i < 140; i++) {
        if (mt[i] >= 2) {
            mt[i + 1]++;
            mt[i] -= 2;
            i--;
        }
    }
    cl = 140;
    while (mt[cl] == 0)
        cl--;
    cl++;
}

_Bool mymin(uint64_t *strt, uint64_t *end) {
    if ((end - strt) < ml) return 0;
    for (uint64_t *i = end - 1; i >= strt; i--) {
        if ((*i) > mc[i - strt])
            break;
        if ((*i) < mc[i - strt])
            return 0;
    }
    for (uint64_t *i = strt; i < end; i++) {
        if (*i < mc[i - strt]) {
            {
                int temp = 1;
                while ((*(i + temp)) == 0) temp++;
                (*(i + temp))--;
                while (--temp)
                    (*(i + temp))++;
            }
            (*i) += 2;
        }
        (*i) -= (mc[i - strt]);
    }
    return 1;
}

void mydi() {
    uint64_t *right = mt + cl;
    uint64_t *left = right - 1;
    while (left + 1 != mt) {
        if (!mymin(left, right)) {
            left--;
        } else while ((*(right-1))==0 && right > left){right--;}
    }
}

uint64_t retv(const uint64_t *arr, uint64_t len) {
    uint64_t ret = 0;
    for (; len > 0; len--) {
        if (arr[len - 1] != 0) break;
    }
    for (; len > 0; len--) {
        ret <<= 1;
        ret += arr[len - 1];
    }
    return ret;
}


uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
    initab(a, b, m);
    mut();
    fmt();
    mydi();
    return retv(mt, 135);
}
