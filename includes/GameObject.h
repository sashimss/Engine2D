#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2.h"
#include "PhysicsComponent.h"
#include <iostream>
#include <functional>
#include <SDL2/SDL.h>

class Engine;
class GameObject;

struct CollisionData {
    GameObject* target;
    float overlapX;
    float overlapY;
};

class GameObject{
    public:
        GameObject(Engine& eng) : engine(eng), m_position(), m_scale(), m_isSolid(false) {};
        GameObject(Engine& eng, const Vector2& i_pos, const Vector2& i_scale, SDL_Color color, bool is_solid);
        GameObject(Engine& eng, float x, float y, float w, float h, SDL_Color color, bool is_solid);
        // ~GameObject();
        
        void Move(float x, float y, float deltaTime = 1.0f){
            m_position.x += x * deltaTime;
            m_position.y += y * deltaTime;
        }
        
        void Move(const Vector2& disp, float deltaTime = 1.0f){
            m_position += disp * deltaTime;
        }
        
        Vector2 GetPosition() const {return m_position;}
        void SetPosition(float x, float y) {m_position.x=x; m_position.y=y;}
        void SetPosition(const Vector2& pos) {m_position.x=pos.x; m_position.y=pos.y;}
        
        Vector2 GetScale() const {return m_scale;}
        void SetScale(float x, float y) {m_scale.x=x; m_scale.y=y;}
        void SetScale(const Vector2& scale) {m_scale.x=scale.x; m_scale.y=scale.y;}

        SDL_Color GetColor() const {return m_color;}
        void SetColor(SDL_Color color) {m_color = color;}

        std::string GetTag() const {return m_tag;}
        void SetTag(std::string newtag) {m_tag = newtag;}

        bool isSolid() const {return m_isSolid;}
        void isSolid(bool val);

        bool isStatic() const {return m_isStatic;}
        void isStatic(bool val) {m_isStatic = val;}

        void SetPhysicsComponent(PhysicsComponent* com);
        PhysicsComponent* GetPhysicsComponent() const { return physicsComponent;}

        void SetOnCollisionCallback(std::function<void(CollisionData data)> callback) {
            m_onCollisionCallback = callback;
        }
        virtual void OnCollision(CollisionData data){
            if (m_onCollisionCallback){
                m_onCollisionCallback(data);
            }
        }

    protected:
        Engine& engine;
        PhysicsComponent* physicsComponent;
        
    private:
        std::string m_tag;
        Vector2 m_position;
        Vector2 m_scale;
        SDL_Color m_color;
        bool m_isSolid;
        bool m_isStatic = false;

        std::function<void(CollisionData data)> m_onCollisionCallback;
    };
    
#endif