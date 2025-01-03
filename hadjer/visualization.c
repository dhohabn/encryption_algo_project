#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#define max_s 50
int main(int argc, char* argv[]) {
    int E,D;
    char text[max_s]="This is the text i want to encrypt";
    printf("enter public key");
    scanf("%d",&E);
    printf("enter private key");
    scanf("%d",&D);

    char numberTextE[50];
    char numberTextD[50];
    sprintf(numberTextE, "E: %d", E);
    sprintf(numberTextD, "D: %d", D);

    /*initializing SDL*/
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }
    /*initializing ttf*/
     if (TTF_Init() < 0) {
        printf("TTF initialization failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    // Create a window
    SDL_Window* window = SDL_CreateWindow("RAS visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window); 
        SDL_Quit();
        return 1;
    }
SDL_Color white = {255, 255, 255, 255};  // White color
SDL_Color black = {0, 0, 0, 255};        // Black color
SDL_Color red = {255, 0, 0, 255};        // Red color
SDL_Color green = {0, 255, 0, 255};      // Green color
SDL_Color blue = {0, 0, 255, 255};       // Blue color
SDL_Color yellow = {255, 255, 0, 255};   // Yellow color
SDL_Color cyan = {0, 255, 255, 255};     // Cyan color
SDL_Color magenta = {255, 0, 255, 255};  // Magenta color 
SDL_Color gray = {128, 128, 128, 255};   // Gray color
SDL_Color lightGray = {211, 211, 211, 255}; // Light gray color
SDL_Color darkGray = {169, 169, 169, 255}; // Dark gray color
SDL_Color orange = {255, 165, 0, 255};    // Orange color
SDL_Color purple = {128, 0, 128, 255};    // Purple color
SDL_Color brown = {139, 69, 19, 255};     // Brown color
SDL_Color pink = {255, 192, 203, 255};    // Pink color
SDL_Color lightBlue = {173, 216, 230, 255}; // Light blue color
SDL_Color lightGreen = {144, 238, 144, 255}; // Light green color

    TTF_Font* font = TTF_OpenFont("C:\\Users\\mchel\\OneDrive\\Desktop\\encryption_algo_project-main\\hadjer\\font\\consolab.ttf", 24);
    if (!font) {
        SDL_Log("Font loading failed: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
        }
    
    SDL_Color textColorE = {255, 255, 255, 255}; // White color
    SDL_Color textColorD = {255,255,255, 255};
    SDL_Surface* textSurfaceE = TTF_RenderText_Solid(font, numberTextE, textColorE);
    if (!textSurfaceE) {
        printf("Failed to create text surface E: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Surface* textSurfaceD = TTF_RenderText_Solid(font, numberTextD, textColorD);
    if (!textSurfaceD) {
        printf("Failed to create text surface D: %s\n", TTF_GetError());
        SDL_FreeSurface(textSurfaceE);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Color textColortext = {128, 0, 128, 255}; // idk what they call this color but i's beautiful
    SDL_Surface* textSurfacetext = TTF_RenderText_Solid(font, text, textColortext);
    if (!textSurfacetext) {
        printf("Failed to create text surface E: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


   
    SDL_Texture* textTextureE = SDL_CreateTextureFromSurface(renderer, textSurfaceE);
    SDL_FreeSurface(textSurfaceE); // Free the surface after creating the texture
    if (!textTextureE) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }
     SDL_Texture* textTextureD = SDL_CreateTextureFromSurface(renderer, textSurfaceD);
    SDL_FreeSurface(textSurfaceD); // Free the surface after creating the texture
    if (!textTextureD) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }
    SDL_Texture* textTexturetext = SDL_CreateTextureFromSurface(renderer, textSurfacetext);
    SDL_FreeSurface(textSurfacetext); // Free the surface after creating the texture
    if (!textTexturetext) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit(); 
        TTF_Quit();
        return 1;
    }

    int speed = 1;
    /*defining the rects*/
    SDL_Rect rectE = {100, 100, 200, 100};
    SDL_Rect rectD = {680, 100, 200, 100};
    SDL_Rect recttext = {300,250,380,100};
    /*defining rects text*/
    SDL_Rect textRectE = {120, 110, 160, 80};
    SDL_Rect textRectD = {700, 110, 160, 80};
    SDL_Rect textRecttext={325,260,330,80}; 


    // Main loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                default: 
                    break;
            }
        }
       


        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);/*background cleared with white color */
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer,90, 34, 139, 40);
        SDL_RenderFillRect(renderer, &rectE);


        SDL_SetRenderDrawColor(renderer,90, 34, 139, 40);
        SDL_RenderFillRect(renderer, &rectD);

 
        SDL_SetRenderDrawColor(renderer,0, 255, 0, 255); 
        SDL_RenderFillRect(renderer, &recttext);




        SDL_RenderCopy(renderer, textTextureE, NULL, &textRectE);
        SDL_RenderCopy(renderer, textTextureD, NULL, &textRectD);
        SDL_RenderCopy(renderer, textTexturetext, NULL, &textRecttext);

        /*i want to move the rectengle text horizontally*/
        recttext.x -= speed;
        textRecttext.x -= speed;
        if (recttext.x<=100){
            speed=0;
        }



        



 
 




        // Present the renderer
        SDL_RenderPresent(renderer);
       


        // Delay to control frame rate
        SDL_Delay(16); // Approximately 60 frames per second
       
    }


    // Cleanup and exit
    SDL_DestroyTexture(textTexturetext);
    SDL_DestroyTexture(textTextureE);
    SDL_DestroyTexture(textTextureD);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();


    return 0;
}


 