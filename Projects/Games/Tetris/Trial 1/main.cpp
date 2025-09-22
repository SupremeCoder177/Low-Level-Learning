#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <ctime>


#define W_WIDTH 900
#define W_HEIGHT 800
#define GRID_WIDTH W_WIDTH * 0.7
#define GRID_HEIGHT W_HEIGHT
#define FPS 3
#define DELAY 1000 / FPS
#define BRICK_FALL_SPEED 1
#define TILE_SIZE 50


using namespace std;


//drawing a single brick cell in the grid
void draw_square(SDL_Renderer* renderer, int r, int g, int b, int a, int x, int y, bool fill){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_FRect temp;
    temp.h = TILE_SIZE;
    temp.w = TILE_SIZE;
    temp.x = x;
    temp.y = y;

    // the actual drawing of the squares
    if(!fill) SDL_RenderRect(renderer, &temp);

    // if not fill then adding a simple black border to add a little contrast
    // change the border color if you like :)
    else {
        SDL_RenderFillRect(renderer, &temp);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderRect(renderer, &temp);
    }
}

// simple function to draw a grid
void draw_grid(SDL_Renderer* renderer, int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for(int i = 0; i < GRID_WIDTH; i += TILE_SIZE){
        for(int j = 0; j < GRID_HEIGHT; j += TILE_SIZE){
            SDL_FRect temp;
            temp.h = TILE_SIZE;
            temp.w = TILE_SIZE;
            temp.x = i;
            temp.y = j;
            SDL_RenderRect(renderer, &temp);
        }
    }
}


// this function changes the grid color
Uint64 change_grid_color(vector<int>& color, bool randomize, int min){
    for(int i = 0; i < color.size() - 1; i++){
        if(!randomize){
            color[i]++;
            if(color[i] > 255) color[i] = min;
        }else{
            color[i] = rand() % min;
        }
    }
    return SDL_GetTicks();
}


class BrickFactory{

    private:
    vector<int> get_tile(int x, int y, int dx, int dy){
        vector<int> temp = {x + dx, y + dy};
        return temp;
    }

    public:

    vector<int> get_color(){
        int temp = rand() % 1;
        vector<int> color;
        switch (temp){
        case 0:
            color = {200, 0, 0, 255};
            break;
        
        default:
            break;
        }
        return color;
    }

    vector<vector<int>> brick1(int x, int y, int orient){
        vector<vector<int>> output;
        output.push_back(get_tile(x, y, 0, 0));
        switch(orient){
            case 0:
                output.push_back(get_tile(x, y, TILE_SIZE, 0));
                output.push_back(get_tile(x, y, TILE_SIZE, TILE_SIZE));
                output.push_back(get_tile(x, y, 0, TILE_SIZE));
                break;
        }
        return output;
    }


};



class Brick{

    private:
    int fall_speed = TILE_SIZE * BRICK_FALL_SPEED;
    int x, y, brick, orient;
    int upper_limit;
    bool fill;
    SDL_Renderer* renderer;
    vector<int> color;

    public:
    Brick(SDL_Renderer* renderer, int x, int y){
        this->x = x;
        this->y = y;
        this->brick = 1;
        this->orient = 0;
        this->renderer = renderer;
        this->color = BrickFactory().get_color();
        this->fill = rand() % 2;

        switch(this->brick){
            case 1:
                upper_limit = 1;
                break;
        }
    }

    void apply_gravity(){
        this->y += TILE_SIZE;
    }

    void check_floor_contact(){

    }

    void draw(){
        vector<vector<int>> temp;
        switch (this->brick){
        case 1:
            temp = BrickFactory().brick1(this->x, this->y, this->orient);
            break;
        }
        for(auto v : temp){
            draw_square(this->renderer, this->color[0], this->color[1], this->color[2], this->color[3], v[0], v[1], this->fill);
        }
    }

    void take_input(){

    }

    void check_valid_tiles(){

    }

    void update(){
        this->apply_gravity();
        this->take_input();
        this->check_valid_tiles();
        this->check_floor_contact();
        this->draw();
    }

    void inc_orient(){
        this->orient++;
        if(this->orient >= this->upper_limit) this->orient = 0;
    }

    void dec_orient(){
        this->orient--;
        if(this->orient < 0) this->orient = this->upper_limit - 1;
    }

};


int main(){

    // intializing stuff
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

    // setting a seed for the rand function
    srand(time(0));

    // variables
    vector<int> grid_color = {100, 100, 100, 200};
    Uint64 last_change_time;

    
    //const variable
    const Uint64 color_change_delay = 1000;
    bool running = true;
    Brick brick(renderer, 0, 0);

    cout << "running" << endl;
    SDL_Event event;
    while(running){

        // don't change this, important for closing the window (I know this but you might not, so I thought to tell ya)
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE) running = false;
        }

        Uint64 start_time = SDL_GetTicks();

        //clearing the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //drawing the grid
        draw_grid(renderer, grid_color[0], grid_color[1], grid_color[2], grid_color[3]);
        if(SDL_GetTicks() - last_change_time >= color_change_delay){
            last_change_time = change_grid_color(grid_color, true, 100);
        }

        //updating and drawing the brick
        brick.update();

        //rendering the presnt frame
        SDL_RenderPresent(renderer);

        //adding a frame cap
        Uint64 end_time = SDL_GetTicks();
        if((end_time - start_time) < DELAY){
            SDL_Delay(DELAY - (end_time - start_time));
        }
    }
    cout << "Ending..." << endl;

    return 0;
}