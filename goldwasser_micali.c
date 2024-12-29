#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long mod_exp(long b, long e, long m) {
    long r = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            r = (r * b) % m;
        }
        b = (b * b) % m;
        e /= 2;
    }
    return r;
}

int is_qr(long num, long n) {
    return mod_exp(num, (n - 1) / 2, n) == 1;
}

long get_prime() {
    long p[] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149};
    return p[rand() % 10];
}

void gen_keys(long *n, long *p, long *q, long *y) {
    *p = get_prime();
    *q = get_prime();
    *n = (*p) * (*q);
    do {
        *y = rand() % (*n);
    } while (is_qr(*y, *n) == 1);
}

long encrypt(long bit, long n, long y) {
    long r = rand() % (n - 1);
    return (mod_exp(y, r, n) * bit) % n;
}

long decrypt(long c, long n, long p, long q) {
    long xp = mod_exp(c, (p + 1) / 4, p);
    long xq = mod_exp(c, (q + 1) / 4, q);
    long x = (xp * q * mod_exp(q, p - 2, p) + xq * p * mod_exp(p, q - 2, q)) % (p * q);
    return is_qr(x, n) ? 0 : 1;
}

int main() {
    srand(time(NULL));

    long n, p, q, y;
    gen_keys(&n, &p, &q, &y);

    printf("Public Key: (n = %ld, y = %ld)\n", n, y);
    printf("Private Key: (p = %ld, q = %ld)\n\n", p, q);

    long msg = 1;
    long c = encrypt(msg, n, y);

    printf("Encrypted message: %ld\n", c);

    long dec = decrypt(c, n, p, q);
    printf("Decrypted message: %ld\n", dec);

    return 0;
}
