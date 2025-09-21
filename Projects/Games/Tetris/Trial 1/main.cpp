#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <random>


#define W_WIDTH 700
#define W_HEIGHT 800
#define FPS 30
#define DELAY 1000 / FPS
#define BRICK_FALL_SPEED 1
#define TILE_SIZE 50


using namespace std;

class BrickFactory{

    private:

    vector<int> brick1(int x, int y, int orient){
        vector<int> output;
        output.push_back(int x);
        output.push_back(int y);
        switch(orient){
            case 0:
                break;
        }
    }

    vector<int> brick2(int x, int y, int orient){
        
    }

    vector<int> brick3(int x, int y, int orient){
        
    }

    vector<int> brick4(int x, int y, int orient){
        
    }

    vector<int> brick5(int x, int y, int orient){
        
    }

    public:
    BrickFactory();

    vector<int>(*)(int, int, int) get_brick(){

    }


};



class Brick{

    private:
    int fall_speed = TILE_SIZE * BRICK_FALL_SPEED;

    public:
    Brick(int x, int y){

    }

};


int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 1){
        cout << "Failed to initialize SDL" << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tetris Trial 1", W_WIDTH, W_HEIGHT, SDL_EVENT_WINDOW_SHOWN);
    if(!window){
        cout << "Failed to create window" << endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer){
        cout << "Failed to create renderer" << endl;
        return 1;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool running = true;

    cout << "running" << endl;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE) running = false;
        }

        Uint64 start_time = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);



        SDL_RenderPresent(renderer);

        Uint64 end_time = SDL_GetTicks();
        if((end_time - start_time) < DELAY){
            SDL_Delay(DELAY - (end_time - start_time));
        }
    }
    cout << "Ending..." << endl;

    return 0;
}