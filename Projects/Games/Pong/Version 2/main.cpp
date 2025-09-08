#include <iostream>
#include <SDL3/SDL.h>
#include <math.h>

#define W_WIDTH 800
#define W_HEIGHT 500
#define FPS 60
#define FRAME_DELAY 1000 / 60
#define PI 3.14159265359

void draw_circle(SDL_Renderer* renderer, int x, int y, int radius){
    float curr_x = x + radius;
    float curr_y = y;
    float step = 0.01f; 
    for(float angle = 0; angle <= 2 * PI; angle += step){
        float dx = cos(angle) * radius;
        float dy = sin(angle) * radius;
        SDL_RenderLine(renderer, 
                   x + dx, 
                   y + dy, 
                   x + cos(angle + step) * radius, 
                   y + sin(angle + step) * radius);
    }
}

bool check_hit_player(int x, int y, int radius, SDL_FRect* rect){
    int points[][2] = {{x - radius, y - radius}, 
                    {x + radius, y - radius},
                    {x + radius, y + radius},
                    {x - radius, y + radius}
                    };
    
    for(int i = 0; i < 4; i++){
        if(rect->x <= points[i][0] && points[i][0] <= rect->x + rect->w){
            if(rect->y <= points[i][1] && points[i][1] <= rect->y + rect->h){
                return true;
            }
        }
    }
    return false;
}

class Player{
    private:
    SDL_FRect player_rect;
    float move_speed;
    SDL_Renderer* renderer;
    int color[4];

    void take_input(){
        const bool* key_states = SDL_GetKeyboardState(NULL);
        if((key_states[SDL_SCANCODE_UP] || key_states[SDL_SCANCODE_W]) && this->player_rect.y - this->move_speed >= 0){
            this->player_rect.y -= this->move_speed;
        }

        if((key_states[SDL_SCANCODE_DOWN] || key_states[SDL_SCANCODE_S]) && this->player_rect.y + this->player_rect.h + this->move_speed <= W_HEIGHT){
            this->player_rect.y += this->move_speed;
        }
    }

    public:
    Player(SDL_Renderer* renderer, int x, int y, int w, int h){
        this->color[0] = 200;
        this->color[1] = 0;
        this->color[2] = 0;
        this->color[3] = 255;
        this->renderer = renderer;
        this->move_speed = 3;
        this->player_rect.x = x;
        this->player_rect.y = y;
        this->player_rect.w = w;
        this->player_rect.h = h;
    }

    void draw(bool outline){
        SDL_SetRenderDrawColor(this->renderer, this->color[0], this->color[1], this->color[2], this->color[3]);
        SDL_RenderFillRect(this->renderer, &this->player_rect);

        if(outline){
            SDL_SetRenderDrawColor(this->renderer, 200, 200, 200, 255);
            SDL_RenderLine(this->renderer, this->player_rect.x, this->player_rect.y, this->player_rect.x + this->player_rect.w, this->player_rect.y);
            SDL_RenderLine(this->renderer, this->player_rect.x, this->player_rect.y + this->player_rect.h, this->player_rect.x + this->player_rect.w, this->player_rect.y + this->player_rect.h);
            SDL_RenderLine(this->renderer, this->player_rect.x, this->player_rect.y, this->player_rect.x, this->player_rect.y + this->player_rect.h);
            SDL_RenderLine(this->renderer, this->player_rect.x + this->player_rect.w, this->player_rect.y, this->player_rect.x + this->player_rect.w, this->player_rect.y + this->player_rect.h);
        }
    }

    void update(){        
        this->take_input();
    }

    SDL_FRect* get_rect(){
        return &this->player_rect;
    }

};


int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 1){
        std::cout << "Failed to initialize SDL" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pong Version 2", W_WIDTH, W_HEIGHT, SDL_EVENT_WINDOW_SHOWN);

    if(!window){
        std::cout << "Failed to create window " << std::endl;
        return 1;
    }

    SDL_Renderer* renderer  = SDL_CreateRenderer(window, NULL);

    if(!renderer){
        std::cout << "Failed to create renderer" << std::endl;
        return 1;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool running = true;
    SDL_Event event;

    int actual_w, actual_h;
    actual_w = W_WIDTH - 7;
    actual_h = W_HEIGHT - 7;
    SDL_FRect center_rect;
    center_rect.h = 100;
    center_rect.w = 50;
    center_rect.x = (actual_w - center_rect.w) / 2;
    center_rect.y = (actual_h - center_rect.h) / 2;

    Player player = Player(renderer, 0, 0, 30, 70);

    int ball_x, ball_y, radius, thickness, ball_move_speed;
    ball_x = actual_w / 2;
    ball_y = actual_h / 2;
    radius = 25;
    thickness = 5;
    ball_move_speed = 4;

    bool moving_down, moving_up, moving_right, moving_left;
    moving_right = false;
    moving_up = false;
    moving_down = true;
    moving_left = true;

    while(running){

        Uint32 start_time = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE) running = false;
        }

        // clearing the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(renderer);

        //updating
        
        // taking player input and moving playes
        player.update();

        // moving the ball based on current movement direction
        if(moving_up){
            ball_y -= ball_move_speed;
        }
        else if(moving_down){
            ball_y += ball_move_speed;
        }
        if(moving_left){
            ball_x -= ball_move_speed;
        }
        else if(moving_right){
            ball_x += ball_move_speed;
        }


        //checking ball collision with walls
        if(moving_right && ball_x + radius + ball_move_speed >= actual_w){
            moving_right = false;
            moving_left = true;
        }
        if(moving_down && ball_y + radius + ball_move_speed >= actual_h){
            moving_down = false;
            moving_up = true;
        }
        if(moving_up && ball_y - radius - ball_move_speed <= 0){
            moving_up = false;
            moving_down = true;
        }

        // checking ball collision with player
        if(check_hit_player(ball_x, ball_y, radius, player.get_rect())){
            moving_left = false;
            moving_right = true;
        }

        // checking if ball is out of screen
        if(ball_x + radius <= -radius){
            ball_x = actual_w / 2;
        }

        //drawing
        SDL_SetRenderDrawColor(renderer, 66, 245, 233, 255);

        SDL_RenderLine(renderer, 0, 0, actual_w, 0);
        SDL_RenderLine(renderer, 0, 0, 0, actual_h);
        SDL_RenderLine(renderer, actual_w, 0, actual_w, actual_h);
        SDL_RenderLine(renderer, 0, actual_h, actual_w, actual_h);
        SDL_RenderLine(renderer, actual_w / 2, 0, actual_w / 2, center_rect.y);
        SDL_RenderLine(renderer, actual_w / 2, center_rect.y + center_rect.h, actual_w / 2, actual_h);
        SDL_RenderRect(renderer, &center_rect);

        player.draw(true);
        int temp = radius;
        while(temp >= radius - thickness){
            draw_circle(renderer, ball_x, ball_y, temp);
            temp--;
        }
        
        SDL_RenderPresent(renderer);

        Uint32 end_time = SDL_GetTicks();

        if(FRAME_DELAY > (end_time - start_time)){
            SDL_Delay(FRAME_DELAY - (end_time - start_time));
        }
    }

    return 0;
}