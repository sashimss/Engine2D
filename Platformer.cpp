#include <iostream>
#include "Engine.h"

class CPlayer : public GameObject {
    public:
        using GameObject::GameObject;

        float yVel=0;
        float speed_multiplier=1;
        bool canJump;
        void OnCollision (CollisionData data) override {
            if (data.overlapY < data.overlapX ){
                // Player hit ground
                yVel = 0;
                canJump = true;
            }
        }
        void Controls(){
            if (engine.IsKeyPressed(SDL_SCANCODE_RSHIFT)){
                speed_multiplier = 2;
            } else {
                speed_multiplier = 1;
            }
            if (engine.IsKeyPressed(SDL_SCANCODE_RIGHT)){
                Move(100*speed_multiplier, 0, engine.GetDeltaTime());
            }
            if (engine.IsKeyPressed(SDL_SCANCODE_LEFT)){
                Move(-100*speed_multiplier, 0, engine.GetDeltaTime());
            }
            if (engine.IsKeyPressed(SDL_SCANCODE_UP) && canJump){
                yVel = -500;
                canJump = false;
            }
        }
        void Update(){
            yVel += 980.0f * engine.GetDeltaTime();
            Move(0, yVel, engine.GetDeltaTime());

            if (GetPosition().y > 900){
                SetPosition(100, 400);
                yVel=0;
            }   
        }
};

int main(){
    Engine engine;
    if (!engine.Init("Platformer", 800, 600)){
        return -1;
    }
    const SDL_Color RED = {255, 0, 0, 255};
    const SDL_Color BLUE = {0, 0, 255, 255};
    const SDL_Color GREEN = {0, 255, 0, 255};
    
    // <----Player---->
    CPlayer Player(engine, 100, 400, 10, 20, RED, true);

    // <----Level Statics---->
    GameObject level_statics[] = {
        GameObject(engine, 0, 500, 200, 100, GREEN, true),
        GameObject(engine, 300, 500, 300, 100, GREEN, true),
        GameObject(engine, 650, 400, 100, 20, GREEN, true),
        GameObject(engine, 500, 300, 100, 20, GREEN, true),
        GameObject(engine, 300, 350, 100, 20, GREEN, true),
        GameObject(engine, 150, 300, 60, 20, GREEN, true),
        GameObject(engine, 50, 200, 60, 20, GREEN, true),
        GameObject(engine, 190, 120, 200, 30, GREEN, true),
        GameObject(engine, 480, 120, 200, 30, GREEN, true),
    };
    for (GameObject& obstacle : level_statics) {
        obstacle.isStatic(true);
    }
    GameObject box = GameObject(engine, 400, 470, 30, 30, BLUE, true);

    while (engine.IsRunning()){
        engine.HandleEvents();
        engine.Update();
        
        Player.Controls();
        Player.Update();

        engine.HandleCollisions();
        
        engine.Render();
        engine.Present();
        engine.LimitFPS();
    }

    engine.Cleanup();

    return 0;
    
}