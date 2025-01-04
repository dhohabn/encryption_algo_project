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

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("GM Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        printf("Renderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    srand((unsigned int)time(NULL));
    int n = 23;

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        int msg = rand() % 2;
        int c = (msg == 0) ? qres(n) : nqres(n);

        SDL_Color col = (msg == 0) ? (SDL_Color){0, 255, 0, 255} : (SDL_Color){255, 0, 0, 255};
        draw_circle(ren, W / 2, H / 2, 100, col);

        printf("Msg: %d, Cipher: %d\n", msg, c);

        SDL_RenderPresent(ren);

        SDL_Delay(2000);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
