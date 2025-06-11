#include "GameObject.h"
#include "Engine.h"


void GameObject::isSolid(bool val) {
    m_isSolid = val;
    if (val){
        engine.AddSolidObject(this);
    } else {
        engine.RemoveSolidObject(this);
    }
}