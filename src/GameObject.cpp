#include "GameObject.h"
#include "Engine.h"

GameObject::GameObject(Engine& eng, const Vector2& i_pos, const Vector2& i_scale, SDL_Color color, bool is_solid) : engine(eng), m_position(i_pos), m_scale(i_scale), m_color(color), m_isStatic(false) {
    eng.AddVisibleObject(this);
    eng.AddSolidBody(this);
}
GameObject::GameObject(Engine& eng, float x, float y, float w, float h, SDL_Color color, bool is_solid) : engine(eng), m_position(x, y), m_scale(w, h), m_color(color), m_isSolid(is_solid), m_isStatic(false) {
    eng.AddVisibleObject(this);
    eng.AddSolidBody(this);
}

void GameObject::SetPhysicsComponent(PhysicsComponent* com) {
    physicsComponent = com;
    engine.AddRigidBody(this);
}