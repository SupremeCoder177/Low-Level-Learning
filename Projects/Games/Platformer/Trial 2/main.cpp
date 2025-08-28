#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <random>

#define W_WIDTH 800
#define W_HEIGHT 600
#define FPS 60
#define FRAME_TIME 1 / FPS

#define TILE_SIZE 50

class Player{
    private:
        SDL_FRect player_rect;
        Uint8 color[4];
        float move_speed;
        
    public:
        Player(){
            player_rect.w = TILE_SIZE;
            player_rect.h = TILE_SIZE;
            player_rect.x = 0;
            player_rect.y = 0;
            color[0] = 100;
            color[1] = 100;
            color[2] = 100;
            color[3] = 255;
            move_speed = 0.3;
        }

        void draw(SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, this->color[0], this->color[1], this->color[2], this->color[3]);
            SDL_RenderFillRect(renderer, &this->player_rect);
        }

        void draw_outline(SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, this->color[0] + 100, this->color[1] + 100, this->color[2] + 100, this->color[3]);
            SDL_RenderRect(renderer, &this->player_rect);
        }

        void move(int x, int y){
            if(x > 0){
                this->player_rect.x += (this->player_rect.x + this->player_rect.w + this->move_speed > W_WIDTH) ? 0 : this->move_speed;
            }
            if(x < 0){
                this->player_rect.x -= (this->player_rect.x - this->move_speed < 0) ? 0 : this->move_speed;
            }
            if(y > 0){
                this->player_rect.y += (this->player_rect.y + this->player_rect.h + this->move_speed > W_HEIGHT) ? 0 : this->move_speed;
            }
            if(y < 0){
                this->player_rect.y -= this->move_speed;
            }
        }

        SDL_FRect* getRect(){
            return &this->player_rect;
        }
};


class FallingObject{
    private:
    float fall_speed;
    SDL_FRect rect;

    public:
    FallingObject(int x, int y, int w, int h){
        this->rect.x = x;
        this->rect.y = y;
        this->rect.w = w;
        this->rect.h = h;
        this->fall_speed = 0.1;
    }

    void draw(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 100, 122, 133, 255);
        SDL_RenderFillRect(renderer, &this->rect);
    }

    void move(){
        this->rect.y += this->fall_speed;
    }

    bool checkCollision(SDL_FRect* obj){
        float selfPoints[4][2] = {{this->rect.x, this->rect.y}, {this->rect.x + this->rect.w, this->rect.y}, {this->rect.x, this->rect.y + this->rect.h}, {this->rect.x + this->rect.w, this->rect.y + this->rect.h}};
        float obj_x, obj_y;
        obj_x = obj->x;
        obj_y = obj->y;
        int obj_w, obj_h;
        obj_w = obj->w;
        obj_h = obj->h;
        for(int i = 0; i < 4; ++i){
            float point[2] = {selfPoints[i][0], selfPoints[i][1]};
            if(obj_x <= point[0] && point[0] <= obj_x + obj_w){
                if(obj_y <= point[1] && point[1] <= obj_y + obj_h){
                    return true;
                }
            }
        }
        return false;    
    }

    bool checkOutOfScreen(){
        return this->rect.y + this->rect.h > W_HEIGHT;
    }

    void reset(){
        this->rect.y = -(rand() % 100) + 1;
        int temp = rand() % W_WIDTH;
        this->rect.x = (temp + this->rect.w < W_WIDTH) ? temp : temp - this->rect.w;
    }
};


int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "Failed to initialize SDL" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Platformer Trial 2", W_WIDTH, W_HEIGHT, SDL_EVENT_WINDOW_SHOWN);
    if(!window){
        std::cerr << "Failed to create window !" << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer){
        std::cerr << "Failed to initialize renderer !" << std::endl;
        return 1;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    Player player = Player();

    bool running = true;
    SDL_Event event;

    bool move_up, move_down, move_left, move_right;
    move_up = false;
    move_down = false;
    move_left = false;
    move_right = false;

    //an array of falling objects
    FallingObject objects[1] = {FallingObject(100, 0, 20, 20)};

    srand(time(NULL));

    while(running){

        Uint32 start_time = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) running = false;

            if(event.type == SDL_EVENT_KEY_DOWN){
                if(event.key.key == SDLK_ESCAPE) running = false;
                if(event.key.key == SDLK_D){
                    move_right = true;
                }
                if(event.key.key == SDLK_A){
                    move_left = true;
                }
                if(event.key.key == SDLK_W){
                    move_up = true;
                }
                if(event.key.key == SDLK_S){
                    move_down = true;
                }
            }
            if(event.type == SDL_EVENT_KEY_UP){
                if(event.key.key == SDLK_ESCAPE) running = false;
                if(event.key.key == SDLK_D){
                    move_right = false;
                }
                if(event.key.key == SDLK_A){
                    move_left = false;
                }
                if(event.key.key == SDLK_W){
                    move_up = false;
                }
                if(event.key.key == SDLK_S){
                    move_down = false;
                }
            }
        }

        if(move_down){
            player.move(0, 1);
        }
        if(move_up){
            player.move(0, -1);
        }
        if(move_left){
            player.move(-1, 0);
        }
        if(move_right){
            player.move(1, 0);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //drawing the player
        player.draw(renderer);
        player.draw_outline(renderer);

        //rendeting falling objects and moving them
        for(FallingObject &obj: objects){
            obj.move();
            obj.draw(renderer);
            if(obj.checkCollision(player.getRect()) || obj.checkOutOfScreen()){
                obj.reset();
            }
        }

        SDL_RenderPresent(renderer);

        Uint32 end_time = SDL_GetTicks();
        if((end_time - start_time) > FRAME_TIME){
            SDL_Delay((end_time - start_time) - FRAME_TIME);
        }
    }

    return 0;
}