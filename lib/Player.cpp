
#include "../include/Player.hpp"
#include <raylib.h>

void Engine::Player::Update(float deltatime) {
    if (IsKeyDown(KEY_W)) this->position.Y -= this->speed * deltatime;
    if (IsKeyDown(KEY_S)) this->position.Y += this->speed * deltatime;
    if (IsKeyDown(KEY_A)) this->position.X -= this->speed * deltatime;
    if (IsKeyDown(KEY_D)) this->position.X += this->speed * deltatime;

    if (this->texture.has_value() && this->IsVisible()) {
        DrawTexture(this->texture.value(), static_cast<int>(this->position.X), static_cast<int>(this->position.Y), WHITE);
    }
}
