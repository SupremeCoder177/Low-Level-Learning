#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <math.h>

#define W_WIDTH 800
#define W_HEIGHT 600
#define FPS 60
#define FRAME_TIME 1 / FPS
#define PI 3.14159265359

class Player{
    private:
    SDL_FRect rect;
    float move_speed;
    int border_width;
    bool move_down, move_up;

    void move(float dx, float dy){
        this->rect.x += dx;
        this->rect.y += dy;
    }

    bool checkValidMovementVertical(float dy, int direction){
        if(direction < 0) return this->rect.y - dy > 0;
        else return this->rect.y + dy + this->rect.h < W_HEIGHT;
    }

    public:
    Player(int width, int height, int x, int y, int border){
        this->rect.h = height;
        this->rect.w = width;
        this->rect.x = x;
        this->rect.y = y;
        this->move_speed = 0.5;
        this->border_width = border;
        this->move_down = false;
        this->move_up = false;
    }

    void draw(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderRect(renderer, &this->rect);

        SDL_FRect temp;
        temp.x = this->rect.x + this->border_width;
        temp.y = this->rect.y + this->border_width;
        temp.w = this->rect.w - (2 * this->border_width);
        temp.h = this->rect.h - (2 * this->border_width);

        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        SDL_RenderFillRect(renderer, &temp);
    }

    void takeInput(SDL_Event* event){
        if(event->type == SDL_EVENT_KEY_DOWN){
            if(event->key.key == SDLK_DOWN){
                if(this->checkValidMovementVertical(this->move_speed, 1)) this->move_down = true;
            }
            if(event->key.key == SDLK_UP){
                if(this->checkValidMovementVertical(this->move_speed, -1)) this->move_up = true;
            }
        }
        if(event->type == SDL_EVENT_KEY_UP){
            if(event->key.key == SDLK_UP) this->move_up = false;
            if(event->key.key == SDLK_DOWN) this->move_down = false;
        }
    }

    void implementInput(){
        if(this->move_down && this->checkValidMovementVertical(this->move_speed, 1)) this->move(0, this->move_speed);
        if(this->move_up && this->checkValidMovementVertical(this->move_speed, -1)) this->move(0, -this->move_speed);
    }

    SDL_FRect* getRect(){
        return &this->rect;
    }

};

class Ball{
    private:
    SDL_Renderer* renderer;
    float center_x, center_y, move_speed, radius;
    bool moving_up, moving_down, moving_left, moving_right, collided;
    Uint8 color[4];

    void move(float dx, float dy){
        this->center_x += dx;
        this->center_y += dy;
    }

    void implementMove(){
        if(this->moving_down) this->move(0, this->move_speed);
        if(this->moving_up) this->move(0, -this->move_speed);
        if(this->moving_left) this->move(-this->move_speed, 0);
        if(this->moving_right) this->move(this->move_speed, 0);
    }

    bool checkVerticalMovement(float dy, int direction){
        if(direction < 0) return this->center_y - this->radius - dy > 0;
        else return this->center_y + this->radius + dy < W_HEIGHT;
    }

    bool checkHorizontalMovement(float dx, int direction){
        if(direction < 0) return this->center_x - this->radius - dx > 0;
        else return this->center_x + this->radius + dx < W_WIDTH;
    }

    void changeDirection(){
        if(collided){
            this->moving_left = !this->moving_left;
            this->moving_right = !this->moving_right;
            this->collided = false;
            return;
        }

        bool vert_temp = this->checkVerticalMovement(this->move_speed, (this->moving_down) ? 1 : -1);
        bool hor_temp = this->checkHorizontalMovement(this->move_speed, (this->moving_right) ? 1 : -1);
        if(this->moving_down){
            this->moving_down = vert_temp;
            this->moving_up = !vert_temp;
        }
        else if(this->moving_up){
            this->moving_down = !vert_temp;
            this->moving_up = vert_temp;
        }
        if(this->moving_left){
            this->moving_left = hor_temp;
            this->moving_right = !hor_temp;
        }
        else if(this->moving_right){
            this->moving_right = hor_temp;
            this->moving_left = !hor_temp;
        }
    }

    public:
    Ball(SDL_Renderer* renderer, float radius, int red, int green, int blue, int alpha){
        this->renderer = renderer;
        this->color[0] = red;
        this->color[1] = green;
        this->color[2] = blue;
        this->color[3] = alpha;
        this->radius = radius;
        this->moving_left = true;
        this->moving_down = true;
        this->moving_right = false;
        this->moving_up = false;
        this->center_x = W_WIDTH / 2;
        this->center_y = W_HEIGHT / 2;
        this->move_speed = 0.2;
        this->collided = false;
    }

    void draw(){
        SDL_SetRenderDrawColor(this->renderer, this->color[0], this->color[1], this->color[2], this->color[3]);
        float angle = 0.0f;
        float delta = 0.01;
      
        while(angle < PI * 2){
            float temp_x, temp_y;
            temp_x = cos(angle) * this->radius;
            temp_y = sin(angle) * this->radius;

            SDL_RenderLine(this->renderer, this->center_x, this->center_y, temp_x + this->center_x, temp_y + this->center_y);
            
            angle += delta;
        }
    }

    void update(){
        this->changeDirection();
        this->implementMove();
    }

    void check_collisison(SDL_FRect* rect){
        float points[4][2] = {{this->center_x - this->radius, this->center_y}, {this->center_x + this->radius, this->center_y}, {this->center_x, this->center_y - this->radius}, {this->center_x, this->center_y + this->radius}};
        for(size_t i = 0; i < sizeof(points) / sizeof(points[0]); ++i){
            SDL_FPoint temp;
            temp.x = points[i][0];
            temp.y = points[i][1];
            if(SDL_PointInRectFloat(&temp, rect)){
                this->collided = true;
                break;
            }
        }
    }

};


int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Failed to initialize SDL" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pong", W_WIDTH, W_HEIGHT, SDL_EVENT_WINDOW_SHOWN);

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

    Player player = Player(50, 100, 0, 0, 5);
    Ball ball = Ball(renderer, 20, 50, 130, 100, 255);

    while(running){

        Uint32 start_time = SDL_GetTicks();

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) running = false;
            if(event.type == SDL_EVENT_KEY_DOWN){
                if(event.key.key == SDLK_ESCAPE) running = false;
            }
            player.takeInput(&event);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        player.implementInput();
        player.draw(renderer);

        ball.update();
        ball.check_collisison(player.getRect());
        ball.draw();

        SDL_RenderPresent(renderer);

        Uint32 end_time = SDL_GetTicks();
        if((end_time - start_time) > FRAME_TIME){
            SDL_Delay((end_time - start_time) - FRAME_TIME);
        }
    }

    return 0;
}