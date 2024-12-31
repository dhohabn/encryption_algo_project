#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function to draw a filled rectangle
void draw_rectangle(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

// Function to render text
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Diffie-Hellman Visualization",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load font
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 16);
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Colors
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color orange = {255, 165, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color brown = {139, 69, 19, 255};
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};

    // Rectangle positions
    int alice_x = 100;  // Alice's rectangle starting position
    int bob_x = 600;    // Bob's rectangle starting position
    int shared_secret_x = 350; // Shared secret rectangle

    // Animation speed
    int speed = 2;

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Update rectangle positions (move Alice and Bob closer to the center)
        if (alice_x < shared_secret_x - 50) alice_x += speed;
        if (bob_x > shared_secret_x + 50) bob_x -= speed;

        // Draw Alice's rectangles and labels
        draw_rectangle(renderer, alice_x, 50, 100, 50, yellow); // Common paint
        render_text(renderer, font, "Common", alice_x, 110, white);
        draw_rectangle(renderer, alice_x, 150, 100, 50, orange); // Secret paint
        render_text(renderer, font, "Secret", alice_x, 210, white);

        // Draw Bob's rectangles and labels
        draw_rectangle(renderer, bob_x, 50, 100, 50, yellow); // Common paint
        render_text(renderer, font, "Common", bob_x, 110, white);
        draw_rectangle(renderer, bob_x, 150, 100, 50, blue);  // Secret paint
        render_text(renderer, font, "Secret", bob_x, 210, white);

        // Draw shared secret rectangle and label
        draw_rectangle(renderer, shared_secret_x, 250, 100, 50, brown); // Shared secret
        render_text(renderer, font, "Shared Secret", shared_secret_x - 10, 310, white);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(16); // ~60 frames per second
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
