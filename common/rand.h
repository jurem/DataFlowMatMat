#ifndef RAND_H
#define RAND_H


void rand_init(const int seed) {
    srand(seed >= 0 ? (unsigned int) seed : (unsigned int) time(NULL));
}


short rand_sign() {
    return rand() < (RAND_MAX >> 1) ? 1 : -1;
}


int rand_int(const int range) {
    return rand() % range;
}


double rand_double(const int range) {
    double r = range * (double)rand() / (double)RAND_MAX;
    if (r == 0) return rand_double(range);
    return r;
}


double rand_signdouble(const int range) {
    return rand_double(range) * rand_sign();
}


#endif
