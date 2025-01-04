#include <SDL.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Function to draw a flower shape
void draw_flower(SDL_Renderer *renderer, int x, int y, int radius, int petal_count) {
    double angle_step = 2 * M_PI / petal_count;
    for (int i = 0; i < petal_count; ++i) {
        double angle = i * angle_step;
        int petal_x = x + (int)(cos(angle) * radius);
        int petal_y = y + (int)(sin(angle) * radius);
        SDL_RenderDrawLine(renderer, x, y, petal_x, petal_y);
    }
}

int SDL_main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Moving Flower",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int flower_x = WINDOW_WIDTH / 2;
    int flower_y = WINDOW_HEIGHT / 2;
    int radius = 100;
    int petal_count = 8;
    int dx = 2, dy = 2;

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Update flower position
        flower_x += dx;
        flower_y += dy;

        // Check for boundary collisions and reverse direction if needed
        if (flower_x + radius >= WINDOW_WIDTH || flower_x - radius <= 0) {
            dx = -dx;
        }
        if (flower_y + radius >= WINDOW_HEIGHT || flower_y - radius <= 0) {
            dy = -dy;
        }

        // Clear the screen with black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set color for flower (Yellow)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        // Draw flower
        draw_flower(renderer, flower_x, flower_y, radius, petal_count);

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
