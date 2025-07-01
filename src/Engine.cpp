#include "Engine.h"
#include "Physics.h"
#include <iostream>

Engine::Engine() : window(nullptr), renderer(nullptr), isRunning(false), FPS(60), lastFrameTime(0), PhysicsEngine(this) {}

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

    PhysicsEngine.ApplyGravity();
    // Game logic
}

void Engine::Render() {
    PhysicsEngine.HandleCollision();

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