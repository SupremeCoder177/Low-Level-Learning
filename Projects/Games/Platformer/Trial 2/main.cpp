#include <iostream>
#include <SDL3/SDL.h>

#define W_WIDTH 800
#define W_HEIGHT 600

#define TILE_SIZE 50

class Player{
    private:
        SDL_FRect player_rect;
        Uint8 color[4];
        int move_speed;
        
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
            move_speed = 4;
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
                this->player_rect.x += this->move_speed;
            }
            if(x < 0){
                this->player_rect.x -= this->move_speed;
            }
            if(y > 0){
                this->player_rect.y += this->move_speed;
            }
            if(y < 0){
                this->player_rect.y -= this->move_speed;
            }
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

    while(running){


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

        SDL_RenderPresent(renderer);
    }

    return 0;
}