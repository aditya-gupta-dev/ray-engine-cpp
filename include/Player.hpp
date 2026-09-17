#pragma once
#include "Entity.hpp"
#include <raylib.h>
namespace Engine {
    class Player : public Engine::Entity {
    public:
        float speed = 900.0f;
        void Update(float deltatime) override;
    };
}
