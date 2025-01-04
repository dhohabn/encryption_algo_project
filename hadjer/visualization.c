#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <math.h>
#define max_s 50
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
//this is RAS algorithm:"R"avist-"S"hemir-"A"delman// 
void Ascii(char text[max_s],int ascii[max_s]){
    int i;
    for (i=0;i<max_s;i++){
        ascii[i]=(int)text[i];
       
    }


}
void Inv_Ascii(int ascii[max_s],char ciphertext[max_s]){
int i;
for (i=0;i<max_s;i++){
    ciphertext[i]=(char)ascii[i];
}
}
//verifies if the public key is prime //
int prime(int E){
    int i;
    if (E<=1){
        return 1;
    
    }
    for(i=2;i<=sqrt(E);i++){
        if (E%i==0){
            return 1;
        }
    }
    return 0;
}
//verifies if the public key is not a factor of the totient//
int fact_totient(int E, int T){
    if (T%E==0){
        return 0;
    }
    return 1;
}
/*function to check if the public key is valid
1* it has to be prime
2*it has to be less than the totient
3*it mustn't be a factor of the totient
*/
int public_key(int E,int T){
    if (prime(E)==0 && E<=T && fact_totient(E,T)==1){
        return 0;
    }
    return 1;

}
int Generating_keys(int q,int p,int*n,int*T){
    if(prime(p)==1 || prime(q)==1){
        printf("the number you just antered is not prime try another one ");
    }
    *n=q*p; //semi prime number//
    *T=(p-1)*(q-1);//this totient is especially for semi prime numbers such that n=p*q with q!=p and q&p are prime numbers //

}
/*I created this version of the algorithm to calculate the modular exponentiation function 
that already exists in the library math is not efficient when it comes to large numbers the algorithm that calculates it 
is called exponentiation by squaring and it reduces the number of number of multiplications needed and does it in an logarithmic time 
complexity*/
int modular_exponential_function (int Message_or_ciphertext, int K,int n){
    int mod=1;
    Message_or_ciphertext=Message_or_ciphertext%n;
    while (K>0){
        if (K%2==1){
            mod=(mod*Message_or_ciphertext)%n;
        }
        K=K/2;
        Message_or_ciphertext=(Message_or_ciphertext*Message_or_ciphertext)%n;

    }
    return mod;
}

void Encrypt(int ascii[max_s],int ciphertext[max_s],int E,int T,int n){
    int i;
    if (public_key(E,T)==0){

    for(i=0;i<max_s;i++){
        ciphertext[i]= modular_exponential_function(ascii[i],E,n);
    }
    }

}
int private_key(int E, int T,int D){
    if ((D*E)%T==1){
        return 0;
    }
    return 1;
}
void decrypt(int ciphertext[max_s],int ascii_decrypted_text[max_s],int D,int n,int T,int E){
    int i;
    if( private_key(E,T,D)==0){
        for(i=0;i<max_s;i++){
            ascii_decrypted_text[i]=modular_exponential_function(ciphertext[i],D,n);
        }
    }
}

int main(int argc, char* argv[]) {
    char text[max_s]="Hello world,";
    int i,n,T,q,p,E,D;
    q=61;
    p=53;
    E=17;
    D=2753;
    int ascii_of_text[max_s];
    int ciphertext[max_s];
    int ascii_decrypted_text[max_s];
    char decrypted_text[max_s];
    printf("the text i want to Encrypt");
    printf("\n");
     for(i=0;i<max_s;i++){
    printf("%c",text[i]);
     }
    printf("\n");
    
    Ascii(text,ascii_of_text);
    printf("\n");
    Generating_keys(61,53,&n,&T);
    Encrypt(ascii_of_text,ciphertext,E,T,n);
    
    printf("the ASCII of text to be Encrypted");
    printf("\n");
    for(i=0;i<max_s;i++){
    printf("%d",ascii_of_text[i]);
    }
    printf("\n");

    printf("Ciphertext:");
    printf("\n");
    for(i=0;i<max_s;i++){
        printf("%d",ciphertext[i]);
    }
    printf("\n");

    printf("ASCII of Dercypted text");
    printf("\n");
    decrypt(ciphertext,ascii_decrypted_text,D,n,T,E);
     for(i=0;i<max_s;i++){
        printf("%d",ascii_decrypted_text[i]);
    }
    printf("\n");

    printf("The Decrypted text:");
    printf("\n");
    Inv_Ascii(ascii_decrypted_text,decrypted_text);
     for(i=0;i<max_s;i++){
        printf("%c",decrypted_text[i]);
    }
    char textE[max_s]="PUBLIC KEY :";
    char textD[max_s]="PRIVATE KEY :";
    char numberTextE[max_s];
    char numberTextD[max_s];
    char numciphertext[max_s];/*This is to use sprintf with a table not just a one value*/
    char temp[max_s];
    for(i=0;i<max_s;i++){
        sprintf(temp,"%d ",ciphertext[i]);
        strcat(numciphertext,temp);
    }

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
    /*window creation*/
    SDL_Window* window = SDL_CreateWindow("RAS visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    /* Create a renderer*/
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

    TTF_Font* font = TTF_OpenFont("C:\\Users\\mchel\\OneDrive\\Desktop\\encryption_algo_project-main\\hadjer\\font\\consolab.ttf", 100);
    if (!font) {
        SDL_Log("Font loading failed: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
        }


    /*srfaces of E and D*/

    SDL_Color textColorE = {255, 255, 255, 255}; 
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


    /*surface for text*/

    SDL_Color textColortext = {255, 255, 255, 255}; 
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


    /*surface for cipher*/

    SDL_Color textColorCipher = {255, 255, 255, 255}; 
    SDL_Surface* textSurfaceCipher = TTF_RenderText_Solid(font, numciphertext, textColorCipher);
    if (!textSurfaceCipher) {
        printf("Failed to create text surface E: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    
  
    }



    /*surfaces of texts above E and D*/

    SDL_Color textColorEtext = {255, 255, 0, 255}; 
    SDL_Color textColorDtext = {255, 255, 0, 255};
    SDL_Surface* textSurfaceEtext = TTF_RenderText_Solid(font, textE, textColorEtext);
    if (!textSurfaceEtext) {
        printf("Failed to create text surface E: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Surface* textSurfaceDtext = TTF_RenderText_Solid(font, textD, textColorDtext);
    if (!textSurfaceDtext) {
        printf("Failed to create text surface D: %s\n", TTF_GetError());
        SDL_FreeSurface(textSurfaceEtext);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }



    SDL_Color textColordecripted = {0, 35, 102, 255};
    SDL_Surface* textSurfacedecrypted= TTF_RenderText_Solid(font, decrypted_text, textColordecripted);
    if (!textSurfacedecrypted) {
        printf("Failed to create text surface E: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    

    /*textures here*/



      /*texture for cipher*/
    SDL_Texture* cipherTexture = SDL_CreateTextureFromSurface(renderer, textSurfaceCipher);
    SDL_FreeSurface(textSurfaceCipher); // Free the surface after creating the texture
    if (!cipherTexture) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }
    

   /*texture for E & D*/

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


    /*texture for text*/

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




    /*texture for texts above  E & D*/

    SDL_Texture* textTextureEtext = SDL_CreateTextureFromSurface(renderer, textSurfaceEtext);
    SDL_FreeSurface(textSurfaceEtext); // Free the surface after creating the texture
    if (!textTextureEtext) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }

    SDL_Texture* textTextureDtext = SDL_CreateTextureFromSurface(renderer, textSurfaceDtext);
    SDL_FreeSurface(textSurfaceDtext); // Free the surface after creating the texture
    if (!textTextureDtext) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }








    /*texture for decrypted text*/

    SDL_Texture* textTexturedecrypted = SDL_CreateTextureFromSurface(renderer, textSurfacedecrypted);
    SDL_FreeSurface(textSurfacedecrypted); // Free the surface after creating the texture
    if (!textTexturedecrypted) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }





    int speed = 5;
    /*defining the rects*/
    SDL_Rect rectE = {100, 100, 200, 100};
    SDL_Rect rectD = {680, 100, 200, 100};
    SDL_Rect recttext = {300,210,380,60};
    SDL_Rect rectciphertext = {100,390,800,60};
    SDL_Rect rectdecryptedtext = {300,590,380,60};
    /*defining rects text*/
    SDL_Rect Etext = {100, 40, 200, 70};
    SDL_Rect Dtext = {680, 40, 200, 70};
    SDL_Rect textRectE = {120, 110, 160, 80};
    SDL_Rect textRectD = {700, 110, 160, 80};
    SDL_Rect textRecttext = {325,217,330,50}; 
    SDL_Rect textRectciphertext = {150,395,700,50};
    SDL_Rect textdecypted = {325,597,330,50}; 


 int key1X = 100;
 int key1Y = 330;


 int key2X = 100;
 int key2Y = 510;
    


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
    

       


        /*Clear the screen*/
        SDL_SetRenderDrawColor(renderer, 246, 36, 89,1);/*this is for background*/
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer,128, 0, 128, 255);/*this is for public key AKA E*/
        SDL_RenderFillRect(renderer, &rectE);


        SDL_SetRenderDrawColor(renderer,128, 0, 128, 255);/*this is for the private key AKA D*/
        SDL_RenderFillRect(renderer, &rectD);

 
        SDL_SetRenderDrawColor(renderer,128, 0, 128, 255);/*this for the Encrypted text*/
        SDL_RenderFillRect(renderer, &recttext);

        SDL_SetRenderDrawColor(renderer,128, 0, 128, 255);/*this is for the Encription of the text using the public key E*/
        SDL_RenderFillRect(renderer, &rectciphertext);

        SDL_SetRenderDrawColor(renderer,128, 0, 128, 255);/*this for the decrypted text*/
        SDL_RenderFillRect(renderer, &rectdecryptedtext );




        SDL_RenderCopy(renderer,textTextureEtext,NULL,&Etext);
        SDL_RenderCopy(renderer,textTextureDtext,NULL,&Dtext);
        SDL_RenderCopy(renderer, textTextureE, NULL, &textRectE);/*this is for public key AKA E*/
        SDL_RenderCopy(renderer, textTextureD, NULL, &textRectD);/*this is for the private key AKA D*/
        SDL_RenderCopy(renderer, textTexturetext, NULL, &textRecttext);/*this for the Encrypted text*/
        SDL_RenderCopy(renderer,cipherTexture,NULL,&textRectciphertext);/*this is for the Encription of the text using the public key E*/
        SDL_RenderCopy(renderer, textTexturetext, NULL, &textdecypted);/*this for the Encrypted text*/
       






        /*E key*/

        key1X += speed;
        if (key1X > 1000) {
            key1X = -100; // Reset to the left of the screen
        }


        int centerX = key1X, centerY = key1Y, radius = 50;
        for (int w = 0; w < radius * 2; w++) {
            for (int h = 0; h < radius * 2; h++) {
                int dx = radius - w; // Horizontal distance from center
                int dy = radius - h; // Vertical distance from center
                if ((dx * dx + dy * dy) <= (radius * radius)) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                    SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
                }
            }
        }


        SDL_Rect shaft = {centerX + radius, centerY - 10, 200, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
        SDL_RenderFillRect(renderer, &shaft);

        SDL_Rect tooth1 = {centerX + radius + 50, centerY + 10, 20, 20};
        SDL_Rect tooth2 = {centerX + radius + 100, centerY + 10, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
        SDL_RenderFillRect(renderer, &tooth1);
        SDL_RenderFillRect(renderer, &tooth2);


    
        




        SDL_Color textColorkeyhandle = {255, 255, 255, 255}; 
        SDL_Surface* textSurfacekh = TTF_RenderText_Solid(font, "E", textColorkeyhandle);
        if (textSurfacekh) {
            SDL_Texture* textTexturekh = SDL_CreateTextureFromSurface(renderer, textSurfacekh);
            SDL_FreeSurface(textSurfacekh);

            SDL_Rect textRect;
            textRect.x = centerX - radius / 2; 
            textRect.y = centerY - radius / 2; 
            textRect.w = radius;             
            textRect.h = radius;       

            SDL_RenderCopy(renderer, textTexturekh, NULL, &textRect);
            SDL_DestroyTexture(textTexturekh);
        }





        /*D key*/
        key2X += speed;
        if (key2X > 1000) {
            key2X = -100; }


        int center2Y = key2Y;
        centerX = key2X, 
        radius = 50;
        for (int w = 0; w < radius * 2; w++) {
            for (int h = 0; h < radius * 2; h++) {
                int dx = radius - w; // Horizontal distance from center
                int dy = radius - h; // Vertical distance from center
                if ((dx * dx + dy * dy) <= (radius * radius)) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                    SDL_RenderDrawPoint(renderer, centerX + dx, center2Y + dy);
                }
            }
        }


        SDL_Rect shaft2 = {centerX + radius, center2Y - 10, 200, 20};
        SDL_SetRenderDrawColor(renderer,255, 255, 0, 255); 
        SDL_RenderFillRect(renderer, &shaft2);

        SDL_Rect tooth12 = {centerX + radius + 50, center2Y + 10, 20, 20};
        SDL_Rect tooth22 = {centerX + radius + 100, center2Y + 10, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
        SDL_RenderFillRect(renderer, &tooth12);
        SDL_RenderFillRect(renderer, &tooth22);


    
        




        SDL_Color textColorkeyhandle2 = {255, 255, 255, 255}; 
        SDL_Surface* textSurfacekh2 = TTF_RenderText_Solid(font, "D", textColorkeyhandle2);
        if (textSurfacekh2) {
            SDL_Texture* textTexturekh2 = SDL_CreateTextureFromSurface(renderer, textSurfacekh2);
            SDL_FreeSurface(textSurfacekh2);

            SDL_Rect textRect2;
            textRect2.x = centerX - radius / 2; 
            textRect2.y = center2Y - radius / 2; 
            textRect2.w = radius;             
            textRect2.h = radius;       

            SDL_RenderCopy(renderer, textTexturekh2, NULL, &textRect2);
            SDL_DestroyTexture(textTexturekh2);
        }














        /*Present the renderer*/
        SDL_RenderPresent(renderer);
       


        // Delay to control 
        SDL_Delay(50); 
    }


    /*Cleanup and clear*/
    SDL_DestroyTexture(textTexturedecrypted);
    SDL_DestroyTexture(textTextureEtext);
    SDL_DestroyTexture(textTextureDtext);
    SDL_DestroyTexture(cipherTexture);
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


 