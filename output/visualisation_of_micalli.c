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

void draw_circle(SDL_Renderer *r, int x, int y, int rad, SDL_Color c) {
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    for (int w = 0; w < rad * 2; w++) {
        for (int h = 0; h < rad * 2; h++) {
            int dx = rad - w;
            int dy = rad - h;
            if ((dx * dx + dy * dy) <= (rad * rad)) {
                SDL_RenderDrawPoint(r, x + dx, y + dy);
            }
        }
    }
}