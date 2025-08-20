#include <iostream>
#include <SDL3/SDL.h>
#include <math.h>
#include <vector>

#define FPS 100
#define FRAME_DELAY 1000 / 60
#define FLOOR 500
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define DEGREE 0.0174533
#define PI 3.14159265359
#define GRAV 2
#define ACC 0.75

//SDL3 has no implmentation for drawing circles, hence this function
void DrawCircle(SDL_Renderer* renderer, Uint32 center_x, Uint32 center_y, Uint32 radius, float start_angle, float stop_angle, bool fill){
    float x =  cos(start_angle) * radius + center_x;
    float y =  sin(start_angle) * radius + center_y;
    float end_angle;
    if(stop_angle > 2 * PI){
        end_angle = fmod(fabs(stop_angle), 2 * PI);
    }else{
        end_angle = stop_angle;
    }
    if(start_angle > end_angle){return;}

    const float theta = DEGREE / 100;
    for(float i = start_angle; i < end_angle; i += theta){
        if(fill){
            SDL_RenderLine(renderer, center_x, center_y, x, y);
        }else{
            SDL_RenderPoint(renderer, x, y);
        }
        x = cos(i) * radius + center_x;
        y = sin(i) * radius + center_y;
    }
}

void apply_gravity(Uint32* y, size_t* count){
    *y += GRAV + ((*(count) % FPS) * ACC);
}


int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "Couldn't initialize SDL, exiting !" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Platformer Trial 1",
                        WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if(!window){
        std::cerr << "Couldn't make window, exiting." << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if(!renderer){
        std::cerr << "Couldn't make rendered, exiting." << std::endl;
        return 1;
    }

    std::vector<uint32_t> blocks;
    Uint32 player_x, player_y, count;
    player_x = 100;
    player_y = 0;
    count = 0;
    short player_height = 50;
    short player_width = 50;

    bool running = true;
    SDL_Event event;
    while(running){

        Uint32 start_time = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE){
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //drawing the floor
        size_t count = 0;
        for(size_t i = FLOOR; i < WINDOW_HEIGHT; ++i){
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 150 - count);
            SDL_RenderLine(renderer, 0, i, WINDOW_WIDTH, i);
            count ++;
        }

        //drawing the sky
        count = 0;
        for(size_t i = 0; i < FLOOR; ++i){
            SDL_SetRenderDrawColor(renderer, 19, 46, 64, 200 - count);
            SDL_RenderLine(renderer, 0, i, WINDOW_WIDTH, i);
            if(i % 3 == 0){
                count++;
            }
        }

        //drawing the moon
        SDL_SetRenderDrawColor(renderer, 122, 122, 122, 200);
        DrawCircle(renderer, WINDOW_WIDTH - 100, 100, 50, DEGREE * 30, DEGREE * 270, false);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
        DrawCircle(renderer, WINDOW_WIDTH - 100, 100, 49, DEGREE * 30, DEGREE * 270, true);

        //updating the player
        apply_gravity(&player_y, &count);

        if(player_y + player_height >= FLOOR){
            count = 0;
            player_y = FLOOR - player_height;
        }

        //drawing the player
        SDL_FRect player_rect;
        player_rect.h = player_height;
        player_rect.w = player_width;
        player_rect.x = player_x;
        player_rect.y = player_y;

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
        SDL_RenderRect(renderer, &player_rect);

        //updating the screen
        SDL_RenderPresent(renderer);

        // setting fps
        Uint32 end_time = SDL_GetTicks();
        if(FRAME_DELAY < (end_time - start_time)){
            SDL_Delay((end_time - start_time) - FRAME_DELAY);
        }
    }

    return 0;
}