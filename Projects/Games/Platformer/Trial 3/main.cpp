#include <iostream>
#include <SDL3/SDL.h>
#include <vector>
#include <array>

#define TILE_SIZE 50
#define FPS 60
#define FRAME_DELAY 1000 / FPS

class Player{
    private:
    SDL_FRect player_rect;
    float move_speed;
    float fall_speed;
    float fall_acc;
    int row_size, num_rows;
    int* map;
    std::vector<std::array<int, 2>> tiles;
    Uint32 count;
    SDL_Renderer* renderer;

    void apply_gravity(){
        if(!this->check_vertical_collision(this->fall_speed + (this->fall_acc * this->count) * TILE_SIZE)){
            this->player_rect.y += (this->fall_speed + (this->fall_acc * this->count)) * TILE_SIZE;
            this->count++;
            return;
        }
        else{
            while(this->check_vertical_collision(0)){
                this->player_rect.y -= this->fall_speed;
            }
        }
        this->count = 0;
    }

    void calc_tiles(){
        for(int i = 0; i < this->row_size * this->num_rows; ++i){
            if(this->map[i]){
                this->tiles.push_back({i % this->row_size,(int) i / this->row_size});
            }
        }
    }

    bool check_vertical_collision(int dy){
        for(size_t i = 0; i < this->tiles.size(); i++){
            SDL_Rect temp{this->tiles.at(i)[0] * TILE_SIZE, this->tiles.at(i)[1] * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_Rect temp2{(int)this->player_rect.x, (int)this->player_rect.y + dy, (int)this->player_rect.w, (int)this->player_rect.h};
            if(SDL_HasRectIntersection(&temp2, &temp)) return true;
        }
        return false;
    }

    bool check_horizontal_collision(int dx){
        for(size_t i = 0; i < this->tiles.size(); i++){
            SDL_Rect temp{this->tiles.at(i)[0] * TILE_SIZE, this->tiles.at(i)[1] * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_Rect temp2{(int)this->player_rect.x + dx, (int)this->player_rect.y, (int)this->player_rect.w, (int)this->player_rect.h};
            if(SDL_HasRectIntersection(&temp2, &temp)) return true;
        }
        return false;
    }

    public:
    Player(SDL_Renderer* renderer, int x, int y, int h, int w, int* MAP, int row_size, int num_rows){
        this->player_rect.x = x;
        this->player_rect.y = y;
        this->player_rect.w = w;
        this->player_rect.h = h;
        this->move_speed = 0.1;
        this->fall_speed = 0.1;
        this->fall_acc = 0.02;
        this->count = 0;
        this->row_size = row_size;
        this->num_rows = num_rows;
        this->renderer = renderer;
        this->map = MAP;
        this->calc_tiles();
    }

    void update(){
        this->apply_gravity();
        this->take_input();
    }

    void draw(){
        SDL_SetRenderDrawColor(this->renderer, 200, 0, 0, 255);
        SDL_RenderFillRect(this->renderer, &this->player_rect);
    }

    void take_input(){
        const bool* keystates = SDL_GetKeyboardState(NULL);

        if(keystates[SDL_SCANCODE_RIGHT]){
            if(!this->check_horizontal_collision(this->move_speed * TILE_SIZE)){
                this->player_rect.x += this->move_speed * TILE_SIZE;
            }
        }
        if(keystates[SDL_SCANCODE_LEFT]){
            if(!this->check_horizontal_collision(-this->move_speed * TILE_SIZE)){
                this->player_rect.x -= this->move_speed * TILE_SIZE;
            }
        }
    }
};

int main(){

    int MAP[][15] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    const int W_WIDTH = (int)(sizeof(MAP[0]) / sizeof(int)) * TILE_SIZE;
    const int W_HEIGHT = (int)(sizeof(MAP) / sizeof(int[sizeof(MAP[0]) / sizeof(int)])) * TILE_SIZE;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Failed to initialize SDL" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Platformer Trial 3", W_WIDTH, W_HEIGHT, SDL_EVENT_WINDOW_SHOWN);

    if(!window){
        std::cout << "Failed to create window" << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if(!renderer){
        std::cout << "Failed to create renderer" << std::endl;
        return 1;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool running = true;
    SDL_Event event;

    Player player = Player(renderer, 100, 40, 40, 20, &MAP[0][0], 15,(int) (sizeof(MAP) / sizeof(MAP[0])));

    while(running){

        Uint32 start_time = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //drawing

        //map
        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);

        for(int i = 0; i < sizeof(MAP) / sizeof(int[sizeof(MAP[0]) / sizeof(int)]); ++i){
            for(int j = 0; j < sizeof(MAP[0]) / sizeof(int); j++){
                if(MAP[i][j]){
                    SDL_FRect temp{(float) j *TILE_SIZE, (float) i *TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    SDL_RenderFillRect(renderer, &temp);
                }
            }
        }

        //player
        player.draw();

        //updating

        //player
        player.update();

        SDL_RenderPresent(renderer);

        Uint32 end_time = SDL_GetTicks();

        if(FRAME_DELAY > (end_time - start_time)){
            SDL_Delay(FRAME_DELAY - (end_time - start_time));
        }
    }

    return 0;
}