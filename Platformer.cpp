#include <iostream>
#include "Engine.h"


int main(){
    Engine engine;
    if (!engine.Init("Platformer", 800, 600)){
        return -1;
    }
    
    // <----Player---->
    GameObject Player = GameObject(engine, 100, 100, 10, 20, true);
    float yVel = 0, speed_multiplier = 1;
    bool canJump;
    Player.SetOnCollisionCallback([&yVel, &canJump](CollisionData data) {
        if (data.overlapY < data.overlapX ){
            // Player hit groun
            yVel = 0;
            canJump = true;
        }
    });

    // <----Ground---->
    GameObject Ground = GameObject(engine, 0, 500, 800, 100, true);
    Ground.isStatic(true);
    Ground.SetTag("Ground");

    // <----Obstacle---->
    GameObject obstacle = GameObject(engine, 300, 450, 20, 50, true);
    obstacle.isStatic(true);
    
    const SDL_Color RED = {255, 0, 0, 255};
    // const int GROUNDLEVEL = 500-Player.GetScale().y;

    auto PlayerControls = [&]() {
        if (engine.IsKeyPressed(SDL_SCANCODE_RSHIFT)){
            speed_multiplier = 2;
        } else {
            speed_multiplier = 1;
        }
        if (engine.IsKeyPressed(SDL_SCANCODE_RIGHT)){
            Player.Move(100*speed_multiplier, 0, engine.GetDeltaTime());
        }
        if (engine.IsKeyPressed(SDL_SCANCODE_LEFT)){
            Player.Move(-100*speed_multiplier, 0, engine.GetDeltaTime());
        }
        if (engine.IsKeyPressed(SDL_SCANCODE_UP) && canJump){
            yVel = -500;
            canJump = false;
        }
    };

    auto ApplyGravity = [&]() {
        yVel += 980.0f * engine.GetDeltaTime();
        Player.Move(0, yVel, engine.GetDeltaTime());
    };

    while (engine.IsRunning()){
        engine.HandleEvents();
        engine.Update();
        engine.Render();

        PlayerControls();
        ApplyGravity();        

        engine.HandleCollisions();

        // Draw Ground
        engine.DrawGameObject(Ground, {0, 255, 0, 255});
        // Draw Player
        engine.DrawGameObject(Player, RED);
        //DrawObstacle
        engine.DrawGameObject(obstacle, {0, 0, 255, 255});

        engine.Present();
        engine.LimitFPS();
    }

    engine.Cleanup();

    return 0;
    
}