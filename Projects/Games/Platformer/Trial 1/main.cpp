#include <iostream>
#include <SDL3/SDL.h>

int main(){

    if(!SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "Couldn't initialize SDL, exiting !" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Platformer Trial 1",
                        600, 400, SDL_EVENT_WINDOW_SHOWN);

    if(!window){
        std::cerr << "Couldn't make window, exiting." << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, "myRenderer");

    if(!renderer){
        std::cerr << "Couldn't make rendered, exiting." << std::endl;
        return 1;
    }

    bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }
    }

    return 0;
}