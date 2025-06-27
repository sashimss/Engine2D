#include "Engine.h"
#include <iostream>

Engine::Engine() : window(nullptr), renderer(nullptr), isRunning(false), FPS(60), lastFrameTime(0) {}

Engine::~Engine() {
    Cleanup();
}

bool Engine::Init(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed! SDL Error : " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed! SDL Error : " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    lastFrameTime = SDL_GetTicks();
    keyboardState = SDL_GetKeyboardState(nullptr);
    return true;
}

void Engine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

void Engine::Update () {
    frameStart = SDL_GetTicks();
    deltaTime = (frameStart - lastFrameTime) / 1000.0f;
    lastFrameTime = frameStart;
    // Game logic
}

void Engine::HandleCollisions() {
    Vector2 pos_a, pos_b, scale_a, scale_b;
    for (GameObject* a : m_solidObjects){
        if (a->isStatic()){ continue; }
        for (GameObject* b : m_solidObjects){
            if (a != b){
                pos_a = a->GetPosition(), pos_b = b->GetPosition();
                scale_a = a->GetScale(), scale_b = b->GetScale();
                int sign;
                
                float overlapX = pos_a.x < pos_b.x ? pos_a.x+scale_a.x-pos_b.x : pos_b.x+scale_b.x-pos_a.x;
                float overlapY = pos_a.y < pos_b.y ? pos_a.y+scale_a.y-pos_b.y : pos_b.y+scale_b.y-pos_a.y;
                // Check if collides
                if (overlapX > 0 && overlapY > 0){
                    if (overlapY > overlapX){
                        sign = pos_a.x < pos_b.x ? 1 : -1;
                        if (b->isStatic()){
                            a->SetPosition(pos_a - Vector2(overlapX*sign, 0));
                        } else {
                            a->SetPosition((pos_a - Vector2(overlapX*sign, 0)/2));
                            b->SetPosition((pos_b + Vector2(overlapX*sign, 0)/2));
                        }
                    } else {
                        sign = pos_a.y < pos_b.y ? 1 : -1;
                        if (b->isStatic()){
                            a->SetPosition(pos_a - Vector2(0, overlapY*sign));
                        } else {
                            a->SetPosition((pos_a - Vector2(0, overlapY*sign)/2));
                            b->SetPosition((pos_b + Vector2(0, overlapY*sign)/2));
                        }
                    }
                    a->OnCollision({b, overlapX, overlapY});
                    b->OnCollision({a, overlapX, overlapY});
                }
            }
        }
    }
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (GameObject* object : m_visibleObjects){
        DrawGameObject(*object, object->GetColor());
    }
}

void Engine::Present() {
    SDL_RenderPresent(renderer);
}

void Engine::LimitFPS() {
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < (1000/FPS)) {
        SDL_Delay((1000/FPS) - frameTime);
    }
}

void Engine::Cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

float Engine::GetDeltaTime(){
    return deltaTime;
}

void Engine::DrawRectangle(int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void Engine::DrawGameObject(GameObject& object, SDL_Color color){
    Vector2 pos = object.GetPosition();
    Vector2 scale = object.GetScale();
    DrawRectangle(pos.x, pos.y, scale.x, scale.y, color);
}

bool Engine::IsKeyPressed(int key) {
    return keyboardState[key];
}