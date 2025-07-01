#include "Physics.h"
#include "Engine.h"
void Physics::HandleCollision(){
    Vector2 pos_a, pos_b, scale_a, scale_b;
    for (GameObject* a : m_solidbodies){
        if (a->isStatic()){ continue; }
        for (GameObject* b : m_solidbodies){
            if (a != b){
                pos_a = a->GetPosition(), pos_b = b->GetPosition();
                scale_a = a->GetScale(), scale_b = b->GetScale();
                int sign;
                
                float overlapX = pos_a.x < pos_b.x ? pos_a.x+scale_a.x-pos_b.x : pos_b.x+scale_b.x-pos_a.x;
                float overlapY = pos_a.y < pos_b.y ? pos_a.y+scale_a.y-pos_b.y : pos_b.y+scale_b.y-pos_a.y;
                // Check if collides
                if (overlapX > 0 && overlapY > 0){
                    if (overlapY > overlapX){       // Collision along x axis
                        sign = pos_a.x < pos_b.x ? 1 : -1;
                        
                        if (b->isStatic()){
                            a->SetPosition(pos_a - Vector2(overlapX*sign, 0));
                        } else {
                            a->SetPosition((pos_a - Vector2(overlapX*sign, 0)/2));
                            b->SetPosition((pos_b + Vector2(overlapX*sign, 0)/2));
                        }
                    } else {
                        sign = pos_a.y < pos_b.y ? 1 : -1;

                        // Check if a is moving downwards
                        if (a->GetPhysicsComponent()->velocity.y > 0){
                            a->GetPhysicsComponent()->velocity.y = 0;
                        }

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

void Physics::ApplyGravity(){
    for (auto obj : m_rigidbodies){
        obj->GetPhysicsComponent()->velocity.y += m_gravity;
    }
}