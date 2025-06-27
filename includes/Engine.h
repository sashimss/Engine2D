#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Vector2.h"

class Engine {
    public :
        Engine();
        ~Engine();

        bool Init(const char* title, int width, int height);
        void Update();
        void HandleEvents();
        void HandleCollisions();
        void Cleanup();
        void Render();
        void Present();
        void LimitFPS();
        bool IsRunning() const { return isRunning ;}

        void DrawRectangle(int x, int y, int w, int h, SDL_Color color);
        void DrawGameObject(GameObject& object, SDL_Color);
        bool IsKeyPressed(int key);
        float GetDeltaTime();

        void AddVisibleObject(GameObject* object) {m_visibleObjects.push_back(object);}
        void RemoveVisibleObject(GameObject* object) {m_visibleObjects.remove(object);}

        void AddSolidObject(GameObject* object) {m_solidObjects.push_back(object);}
        void RemoveSolidObject(GameObject* object) {m_solidObjects.remove(object);}


    private :
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning;
        Uint8 FPS;
        float lastFrameTime;
        const Uint8* keyboardState;
        float deltaTime;
        Uint32 frameStart;

        std::list<GameObject*> m_visibleObjects;
        std::list<GameObject*> m_solidObjects;
};


#endif