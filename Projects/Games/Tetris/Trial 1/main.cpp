#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <ctime>
#include <map>


#define W_WIDTH 900
#define W_HEIGHT 800
#define GRID_WIDTH W_WIDTH * 0.7
#define GRID_HEIGHT W_HEIGHT
#define FPS 3
#define INPUT_DELAY 1000 / FPS
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


// this function draws the occupied tiles on the screen
void draw_tiles(SDL_Renderer* renderer, map<vector<int>, map<vector<int>, bool>> tiles){
    for(auto [tile, color_style] : tiles){
        vector<int> color;
        bool fill_type;
        for(auto [c, f_type] : color_style){
            color = c;
            fill_type = f_type;
        }
        draw_square(renderer, color[0], color[1], color[2], color[3], tile[0], tile[1], fill_type);
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

    int get_number_of_brick(){
        return 2;
    }

    int get_orientations_limit(int brick){
        switch(brick){
            case 1:
                return 1;
                break;
            case 2:
                return 4;
                break;
            default:
                return 0;
                break;
        }
    }

    //returns a color from the options listed
    vector<int> get_color(){
        int temp = rand() % 5;
        vector<int> color;
        switch (temp){
        //red
        case 0:
            color = {200, 0, 0, 255};
            break;
        //green
        case 1:
            color = {0, 200, 0, 255};
            break;
        //blue
        case 2:
            color = {0, 0, 200, 255};
            break;
        //purple like
        case 3:
            color = {200, 0, 200, 255};
            break;
        //cyan like
        case 4:
            color = {0, 200, 200, 255};
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

    vector<vector<int>> brick2(int x, int y, int orient){
        vector<vector<int>> output;
        output.push_back(get_tile(x, y, 0, 0));
        switch(orient){
            case 0:
                output.push_back(get_tile(x, y, TILE_SIZE, 0));
                output.push_back(get_tile(x, y, -TILE_SIZE, 0));
                output.push_back(get_tile(x, y, 0, -TILE_SIZE));
                break;
            case 1:
                output.push_back(get_tile(x, y, TILE_SIZE, 0));
                output.push_back(get_tile(x, y, 0, TILE_SIZE));
                output.push_back(get_tile(x, y, 0, -TILE_SIZE));
                break;
            case 2:
                output.push_back(get_tile(x, y, 0, TILE_SIZE));
                output.push_back(get_tile(x, y, -TILE_SIZE, 0));
                output.push_back(get_tile(x, y, TILE_SIZE, 0));
                break;
            case 3:
                output.push_back(get_tile(x, y, -TILE_SIZE, 0));
                output.push_back(get_tile(x, y, 0, TILE_SIZE));
                output.push_back(get_tile(x, y, 0, -TILE_SIZE));
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
    Brick(SDL_Renderer* renderer){
        this->renderer = renderer;
        this->reset();
    }

    // returns the color of the current brick
    vector<int> get_color(){
        return this->color;
    }

    // returns the fill type for the current brick
    bool get_fill_type(){
        return this->fill;
    }
    
    // moves the brick downward
    void apply_gravity(){
        this->y += TILE_SIZE;
    }

    // checks if the brick has collided with the other occupied cells, or the floor
    bool check_brick_contact(vector<vector<int>> occupied){
        if(reached_floor()) return true;
        for(auto v : get_tiles()){
            for(auto tile : occupied){
                if(v[0] == tile[0] && v[1] == tile[1]) return true;
            }
        }
        return false;
    }

    // returns the tiles occupied by the brick
    vector<vector<int>> get_tiles(){
        vector<vector<int>> temp;
        switch (this->brick){
        case 1:
            temp = BrickFactory().brick1(this->x, this->y, this->orient);
            break;
        case 2:
            temp = BrickFactory().brick2(this->x, this->y, this->orient);
            break;
        }
        return temp;
    }

    // draws the brick
    void draw(){
        vector<vector<int>> temp = get_tiles();
        for(auto v : temp){
            draw_square(this->renderer, this->color[0], this->color[1], this->color[2], this->color[3], v[0], v[1], this->fill);
        }
    }

    // resets the brick
    void reset(){
        this->x = TILE_SIZE * (rand() % (int)(GRID_WIDTH / TILE_SIZE));
        this->y = -TILE_SIZE;
        this->brick = 1 + (rand() % BrickFactory().get_number_of_brick());
        this->orient = 0;
        this->color = BrickFactory().get_color();
        this->fill = rand() % 2;
        this->orient = 0;
        this->upper_limit = BrickFactory().get_orientations_limit(this->brick);
    }


    //takes in horizontal movement input
    void take_input(){
        const bool* keyboardState  = SDL_GetKeyboardState(NULL);

        //horizontal moevement input
        if(keyboardState[SDL_SCANCODE_LEFT]){
            check_valid_tiles(-TILE_SIZE);
        }
        if(keyboardState[SDL_SCANCODE_RIGHT]){
            check_valid_tiles(TILE_SIZE);
        }

        // orientation changing input
        if(keyboardState[SDL_SCANCODE_UP]){
            this->inc_orient();
        }
        if(keyboardState[SDL_SCANCODE_DOWN]){
            this->dec_orient();
        }
    }

    // checks if the passed tile if in the bounds of the grid
    bool check_out_of_bounds(vector<int> tile){
        if(tile[0] < 0 || tile[0] > GRID_WIDTH) return false;
        if(tile[1] + TILE_SIZE > GRID_HEIGHT) return false;
        return true;
    }

    // checks if the current occupied tiles + dx if in the bounds of the grid
    void check_valid_tiles(int dx){
        vector<vector<int>> temp = get_tiles();
        for(auto v : temp) {
            v[0] += dx;
            if(!check_out_of_bounds(v)) return;
        }
        this->x += dx;
    }

    // the main function to call in order to take input, move, and draw the current brick
    // returns the occupied tiles if collides with floor or other occupied tiles
    vector<vector<int>> update(vector<vector<int>> cells){
        vector<vector<int>> output;
        this->apply_gravity();
        this->take_input();
        bool temp = this->check_brick_contact(cells);
        if(temp) this->y -= TILE_SIZE;
        this->draw();
        if(temp) return get_tiles();
        else return output;
    }

    // checks if any tile in the current occupied tiles have reached the floor
    bool reached_floor(){
        vector<vector<int>> temp = get_tiles();
        for(auto v : temp){
            if(v[1] >= GRID_HEIGHT) return true;
        }
        return false;
    }

    // looping the orientation variable
    // increases the orientation if valid bounds
    void inc_orient(){
        int temp = this->orient;
        this->orient++;
        if(this->orient >= this->upper_limit) this->orient = 0;
        for(auto tile : get_tiles()){
            if(!check_out_of_bounds(tile)){
                this->orient = temp;
                break;
            }
        }
    }

    // decreases the orientation if valid bounds
    void dec_orient(){
        int temp = this->orient;
        this->orient--;
        if(this->orient < 0) this->orient = this->upper_limit - 1;
        for(auto tile : get_tiles()){
            if(!check_out_of_bounds(tile)){
                this->orient = temp;
                break;
            }
        }
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

    // grid color varaibles
    vector<int> grid_color = {100, 100, 100, 200};
    Uint64 last_change_time;

    // cells variable
    vector<vector<int>> occupied_cells;
    map<vector<int>, map<vector<int>, bool>> color_mapping; // holds the color and fill type for each occupied tile
    
    //const variable
    const Uint64 color_change_delay = 1000;
    bool running = true;
    Brick brick(renderer);

    //running the main game loop
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

        //un-comment this code block to get a random colored grid which changes color every second
        // if(SDL_GetTicks() - last_change_time >= color_change_delay){
        //     last_change_time = change_grid_color(grid_color, true, 100);
        // }

        vector<vector<int>> temp = brick.update(occupied_cells);
        if(temp.size() != 0){ 
            vector<int> color = brick.get_color();
            bool fill_type = brick.get_fill_type();
            brick.reset();
            for(auto v : temp) {
                occupied_cells.push_back(v);
                map<vector<int>, bool> color_style;
                color_style[color] = fill_type;
                color_mapping[v] = color_style;
            }
        }

        // drawing the occupied tiles on the screen
        draw_tiles(renderer, color_mapping);

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