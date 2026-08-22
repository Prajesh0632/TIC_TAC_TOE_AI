#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include "../../include/ui/menu.hpp"
#include "../../include/Play/play.hpp"


int main(int argc, char *argv[])
{

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "SDL Initialization Failed.";
        return 1;
    }

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        std::cout << "Images Initialization Failed.";
        return 1;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "TTF Initialization Failed: " << TTF_GetError() << std::endl;
        return 1;
    }

    int Width = 1000;
    int Height = 800;

    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "SDL Window Creation Failed.";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cout << "SDL Renderer Creation Failed.";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool exit = false;

    SDL_Event event;

    std::map<std::string, int> screenStates = {

        {"Main_Menu", 0},
        {"Play", 1},
        {"Play AI", 2},
        {"Settings", 3},
        {"Quit", 4}};

    Menu menu(renderer);
   
    Play play(renderer, 0);      // Type 0 for human vs human
    Play playAi(renderer, 1);    // Type 1 for human vs AI

    Uint32 start;
    Uint32 end;

    int currentState = 0;
    while (!exit)
    {

        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT)
            {
                exit = true;
                break; 
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && currentState == 0)
            {


               

                

                currentState = menu.checkStateChange();
                if (currentState == 1 || currentState == 2)
                {
                    start = SDL_GetTicks();
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && currentState == 1 && SDL_GetTicks() - start > 500)
            {

               
               

                  
                currentState = play.checkClick(event.button.x, event.button.y);

                
             
            }

            if(event.type == SDL_MOUSEBUTTONDOWN && currentState == 2 && SDL_GetTicks() - start > 500) {

                
                 
                    currentState = playAi.checkClick(event.button.x, event.button.y);

                
            }
        }

        
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 159, 255);
        SDL_RenderClear(renderer);

        

        switch (currentState)
        {

            // For Main Menu

            

        case 0:
        {

            menu.display();
            break;
        }

        case 1:
        {

           
            play.display();

            break;
        }

        case 2:
        {

          

            playAi.display();            

            break;

        }

        case 4:
        {
            exit = true;
        }

        default:
            break;
        }

     SDL_RenderPresent(renderer);
    }

    return 0;
}

