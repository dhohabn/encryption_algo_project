#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float linear_regression(float w, float b, int x) {
    return (w * x) + b;
}

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Horizontal offset
            int dy = radius - h; // Vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

int SDL_main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Linear Regression Visualization", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    float t1[5], t2[5];
    int y;
    printf("Enter the values for the first table:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &t1[i]);
    }

    printf("Enter the values for the second table:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &t2[i]);
    }

    printf("Enter the prediction value (y):\n");
    scanf("%d", &y);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Define colors
        SDL_Color white = {255, 255, 255, 255};
        SDL_Color red = {255, 0, 0, 255};

        // Draw axes
        draw_line(renderer, 50, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2, white); // X-axis
        draw_line(renderer, SCREEN_WIDTH / 2, 50, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, white); // Y-axis

        // Plot points and regression line
        for (int i = 0; i < 5; i++) {
            float fx = linear_regression(t1[i], t2[i], y);

            // Scale values to fit the screen
            int x = (int)(t1[i] * 10) + SCREEN_WIDTH / 2;
            int y_actual = SCREEN_HEIGHT / 2 - (int)(t2[i] * 10);
            int y_pred = SCREEN_HEIGHT / 2 - (int)(fx * 10);

            // Draw actual point
            draw_circle(renderer, x, y_actual, 5, red);

            // Draw prediction point
            draw_circle(renderer, x, y_pred, 5, white);

            // Draw line from actual to predicted
            draw_line(renderer, x, y_actual, x, y_pred, white);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}