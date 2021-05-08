// HelloSFML.cpp : This file contains the 'main' function. 
//

#include "HelloSDL.h"
#include "App.h"
#include "Lesson02.h"
#include "Lesson03.h"
#include "Lesson04.h"
#include "Lesson05.h"
#include "Lesson06.h"
#include "Lesson07.h"
#include "Lesson08.h"
#include "Lesson09.h"
#include "Lesson10.h"

#include "Lesson11.h"
#include "Lesson12.h"
#include "Lesson13.h"
#include "Lesson14.h"
#include "Lesson15.h"
#include "Lesson16.h"
#include "Lesson17.h"
#include "Lesson18.h"
#include "Lesson22.h"
#include "Lesson23.h"
#include "Lesson24.h"
#include "Lesson26.h"
#include "Lesson27.h"
#include "Lesson28.h"
#include "Lesson29.h"
#include "Lesson30.h"
#include "Lesson33.h"
#include "Lesson35.h"


// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int hello_sdl(int argc, char* argv[]) {
    // The window we will be rendering to
    SDL_Window* window = NULL;

    // The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        // Create window
        window = SDL_CreateWindow(
            "SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Wait two seconds
            SDL_Delay(2000);
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}


// This will render a image on the window that can be controlled using keyboard: up, down, left, right. 
int geeks_main(int argc, char* argv[]) {
    // returns zero on success, otherwise non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000, 1000, 0);

    // triggers the program that controls graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // create a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    // create a surface to load an image into main memory
    SDL_Surface* surface;

    surface = IMG_Load("C:\\Users\\jholmes\\OneDrive\\Pictures\\penny-and-me-key-largo.jpeg");

    // load image to graphics hardware memory
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

    // clear main memory
    SDL_FreeSurface(surface);

    // we can control the image position so that we can move it with our keyboard.
    SDL_Rect dest;

    // connect our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 6;
    dest.h /= 6;

    // set initial x-position of object
    dest.x = (1000 - dest.w) / 2;

    // set initial y-position of object
    dest.y = (1000 - dest.h) / 2;

    // control annimation loop
    int close = 0;

    // speed of box
    int speed = 300;

    // animation loop
    while (!close) {
        SDL_Event event;

        // Event mangement
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handle close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    dest.y -= speed / 30;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    dest.x -= speed / 30;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    dest.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    dest.x += speed / 30;
                    break;
                default:
                    break;
                }
            }
        }

        // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        // clear the screen
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, NULL, &dest);

        // trigger the double buffers for multiple rendering
        SDL_RenderPresent(rend);

        // calculate to 60 fps
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyTexture(tex);    // destroy texture
    SDL_DestroyRenderer(rend);  // destroy renderer
    SDL_DestroyWindow(win);     // destroy window

    SDL_Quit(); // close SDL

    return 0;
}



int main(int argc, char* argv[]) {
    ios::sync_with_stdio();  // notify compiler that both types of I/O will be used
    
    //cout << "Hello, Jeff!" << endl;
    //printf("Hello again!\n");

    //return App::GetInstance()->Execute(argc, argv);

    Lesson* ptr = NULL;

    // Lesson 2-9
    //return Lesson2::GetInstance()->main(argc, argv);
    //return Lesson9::GetInstance()->main(argc, argv);

    // Lesson 10-18, 22-24, 26
    //ptr = new Lesson10();
    //ptr = new Lesson29();
    ptr = new Lesson35();

    return ptr->main(argc, argv);
}

