#pragma once

#include <Vector2.h>
class GameObject;
class PhysicsComponent{
    public:
        float mass;
        Vector2 velocity;
        PhysicsComponent(GameObject& obj, float mass) : m_gameObject(obj), mass(mass) {};

    private:
        GameObject& m_gameObject;
};