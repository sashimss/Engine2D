#pragma once

#include <list>
#include "PhysicsComponent.h" 
#include "Vector2.h"
#include "GameObject.h"

class Engine;
class Physics {
    public:
        Physics(Engine* engine) : engine(engine) {};
        void HandleCollision();
        void ApplyGravity();
        void AddRigidBody(GameObject* object) {m_rigidbodies.push_back(object);}
        void RemoveRigidBody(GameObject* object) {m_rigidbodies.remove(object);}
        void AddSolidBody(GameObject* object) {m_solidbodies.push_back(object);}
        void RemoveSolidBody(GameObject* object) {m_solidbodies.remove(object);}

    private:
        Engine* engine;
        float m_gravity = 9.8f;
        std::list<GameObject*> m_rigidbodies;
        std::list<GameObject*> m_solidbodies;
};