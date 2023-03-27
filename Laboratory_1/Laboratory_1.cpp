//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include <math.h>

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* windowSurface = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = { 100, 100, 200, 200 };
SDL_Rect Dreptunghi;
Uint32 rectagleColor;
Uint32 drepColor;

bool quit = false;
int nr = 0;
int r = 0;
int g = 0;
int b = 0;
int mouseX, mouseY;
int dInitx, dInity;
int finX, finY;

bool initWindow()
{
    bool success = true;

    //Try to initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    }
    else {
        //Try to create the window
        window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

        if (window == NULL)
        {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Try to get the window surface
            windowSurface = SDL_GetWindowSurface(window);

            if (windowSurface == NULL)
            {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initialize surface color
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));

                //Update the surface
                SDL_UpdateWindowSurface(window);
            }

        }
    }
    return success;
}

void destroyWindow()
{
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initWindow())
    {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }

    rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);


    while (!quit) {
        //Handle events on queue
        if (SDL_WaitEvent(&currentEvent) != 0)
        {
            //User requests quit
            if (currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
            //Mouse event -> pressed button
            if (currentEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if (currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                    dInitx = mouseX;
                    dInity = mouseY;

                }
            }

            //Mouse event -> mouse movement
            if (currentEvent.type == SDL_MOUSEMOTION)
            {
                if (currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                    finX = mouseX;
                    finY = mouseY;
                }
                Dreptunghi = { dInitx,dInity,abs(dInitx - finX),abs(dInity - finY) };
                drepColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);
                SDL_FillRect(windowSurface, &Dreptunghi, drepColor);
                if (currentEvent.type != SDL_MOUSEMOTION)
                    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));

            }

            //Keyboard event
            if (currentEvent.type == SDL_KEYDOWN)
            {
                switch (currentEvent.key.keysym.sym)
                {
                case SDLK_g:
                    nr = 2;
                    break;
                case SDLK_r:
                    nr = 1;
                    break;
                case SDLK_b:
                    nr = 3;
                    break;
                case SDLK_x:
                    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
                    break;

                default:

                    break;
                }
            }
            switch (nr)
            {
            case 1:
                if (currentEvent.key.keysym.sym == SDLK_UP)
                {
                    if (r >= 255)
                        r = 0;
                    r += 10;
                }
                if (currentEvent.key.keysym.sym == SDLK_DOWN)
                {
                    if (r <= 0)
                        r = 255;
                    r -= 10;
                }
                break;
            case 2:
                if (currentEvent.key.keysym.sym == SDLK_UP)
                {
                    if (g >= 255)
                        g = 0;
                    g += 10;
                }
                if (currentEvent.key.keysym.sym == SDLK_DOWN)
                {
                    if (g <= 0)
                        g = 255;
                    g -= 10;
                }
                break;
            case 3:
                if (currentEvent.key.keysym.sym == SDLK_UP)
                {
                    if (b >= 255)
                        b = 0;
                    b += 10;
                }
                if (currentEvent.key.keysym.sym == SDLK_DOWN)
                {
                    if (b <= 0)
                        b = 255;
                    b -= 10;
                }
                break;
            default:
                break;
            }
            rectagleColor = SDL_MapRGB(windowSurface->format, r, g, b);
            SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
            SDL_UpdateWindowSurface(window);
        }
    }
    destroyWindow();
    return 0;
}
