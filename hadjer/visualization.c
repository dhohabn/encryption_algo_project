
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  // Include time.h for srand() and time()
TTF_Font* font = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600



// Function to compute the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}


// Function to find modular inverse
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1) return d;
    }
    return -1;
}


// Function to compute power (m^e) % n
long long modExp(long long m, long long e, long long n) {
    long long result = 1;
    m = m % n;
    while (e > 0) {
        if (e % 2 == 1)
            result = (result * m) % n;
        e = e >> 1;
        m = (m * m) % n;
    }
    return result;
}


// Function to generate a random prime number
int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}


int generatePrime() {
    int num;
    do {
        num = rand() % 100 + 50; // Generate a random number between 50 and 150
    } while (!isPrime(num));
    return num;
}


// RSA key generation
void generateRSAKeys(int* e, int* d, int* n) {
    srand(time(NULL));  // Use time to seed the random number generator


    int p = generatePrime();
    int q = generatePrime();


    *n = p * q;
    int phi = (p - 1) * (q - 1);


    // Choose e such that 1 < e < phi(n) and gcd(e, phi) = 1
    *e = 2;
    while (gcd(*e, phi) != 1) (*e)++;


    // Compute d such that (d * e) % phi = 1
    *d = modInverse(*e, phi);
}


// Function to render text using simple SDL (rectangles, lines, etc.)
void renderText(SDL_Renderer* renderer, const char* text, int x, int y) {
    // Simple rendering: display text as small rectangles (basic for visualization)
    SDL_Rect rect = { x, y, 100, 30 };  // Just a placeholder for text
    SDL_SetRenderDrawColor(renderer, 128,0,128,255); // White color
    SDL_RenderFillRect(renderer, &rect);  // Draw rectangle to simulate text
}


// Function to render RSA visualization
void renderRSAVisualization(int e, int d, int n, int message, long long encrypted, long long decrypted) {
    SDL_Init(SDL_INIT_VIDEO);


    SDL_Window* window = SDL_CreateWindow("RSA Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Set background to yellow
    SDL_SetRenderDrawColor(renderer,255,255,0,255);
    SDL_RenderClear(renderer);


    // Display RSA key information and visualization (just as a basic example)
    char text[256];
    sprintf(text, "Public Key: e = %d, n = %d", e, n);
    renderText(renderer, text, 50, 50);


    sprintf(text, "Private Key: d = %d, n = %d", d, n);
    renderText(renderer, text, 50, 100);


    sprintf(text, "Message: %d", message);
    renderText(renderer, text, 50, 150);


    sprintf(text, "Encrypted: %lld", encrypted);
    renderText(renderer, text, 50, 200);


    sprintf(text, "Decrypted: %lld", decrypted);
    renderText(renderer, text, 50, 250);


    // Example of visualization: Draw a simple box for RSA steps
    SDL_SetRenderDrawColor(renderer, 128,0,128,255);  // purple color
    SDL_Rect rsaBox = { 200, 300, 400, 100 };  // Example box for encryption process
    SDL_RenderDrawRect(renderer, &rsaBox);


    SDL_RenderPresent(renderer);


    SDL_Delay(50000); // Wait for 5 seconds before closing


    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int SDL_main(int argc, char* argv[]){
    int e, d, n,q,p;
    q=61;
    p=53;
    e=17;
    d=2753;
    n=q*p;
    generateRSAKeys(&e, &d, &n);


    int message = 65; // Example message
    long long encrypted = modExp(message, e, n);
    long long decrypted = modExp(encrypted, d, n);


    renderRSAVisualization(e, d, n, message, encrypted, decrypted);


    return 0;
}


