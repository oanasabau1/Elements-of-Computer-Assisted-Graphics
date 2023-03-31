//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include "transform.h"

using namespace egc;

SDL_Renderer* windowRenderer;
// define rectangle vertices
vec3 A(100, 100, 1), B(400, 100, 1), C(400, 200, 1), D(100, 200, 1);
vec3 A1(100, 100, 1), B1(400, 100, 1), C1(400, 200, 1), D1(100, 200, 1);
vec3 O;

mat3 T1, R, S, T2;
mat3 F;

float angle;
float scaleIndex = 1.0f;

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = { 100, 100, 200, 200 };

bool quit = false;

int mouseX, mouseY;

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
            // Create a renderer for the current window
            windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (windowRenderer == NULL)
            {
                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Set background color
                SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);

                //Apply background color
                SDL_RenderClear(windowRenderer);
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
                }
            }

            //Mouse event -> mouse movement
            if (currentEvent.type == SDL_MOUSEMOTION)
            {
                if (currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }

            //Keyboard event
            if (currentEvent.type == SDL_KEYDOWN)
            {
                switch (currentEvent.key.keysym.sym)
                {
                case SDLK_UP:
                    scaleIndex += 0.1;
                    break;

                case SDLK_DOWN:
                    scaleIndex -= 0.1;
                    if (scaleIndex < 0.1) {
                        scaleIndex = 0.1;
                    }
                    break;

                case SDLK_LEFT:
                    angle -= 10;
                    break;

                case SDLK_RIGHT:
                    angle += 10;
                    break;

                default:
                    angle = 0;
                    scaleIndex = 1.0f;
                    break;
                }
            }

            O = (A1 + C1) * (1.0f / 2.0f);

            T1 = translate(O.x, O.y);
            R = rotate(angle);
            S = scale(scaleIndex, scaleIndex);
            T2 = translate(-O.x, -O.y);

            F = T1 * R * S * T2;

            A = F * A1;
            B = F * B1;
            C = F * C1;
            D = F * D1;

            SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
            SDL_RenderClear(windowRenderer);

            SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);
            SDL_RenderDrawLine(windowRenderer, A.x, A.y, B.x, B.y);
            SDL_RenderDrawLine(windowRenderer, B.x, B.y, C.x, C.y);
            SDL_RenderDrawLine(windowRenderer, C.x, C.y, D.x, D.y);
            SDL_RenderDrawLine(windowRenderer, D.x, D.y, A.x, A.y);

            SDL_RenderPresent(windowRenderer);
        }
    }

    destroyWindow();
    return 0;
}
