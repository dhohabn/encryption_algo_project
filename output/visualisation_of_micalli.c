#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 800
#define H 600

int qres(int n) {
    int x = rand() % n;
    return (x * x) % n;
}

int nqres(int n) {
    while (1) {
        int x = rand() % n;
        int r = (x * x) % n;
        if (r != 0 && r % n != qres(n)) {
            return r;
        }
    }
}