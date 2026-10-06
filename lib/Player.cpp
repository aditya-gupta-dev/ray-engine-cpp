#include "../include/Player.hpp"
#include <raylib.h>

void Engine::Player::Update(float deltatime) {
    if (this->texture.has_value() && this->IsVisible()) {
        const float speed = this->speed;

        static float animTimer = 0.0f;
        static int currentFrame = 0;

        const int frameWidth = 128;
        const int frameHeight = 128;
        const int maxFrames = 4;
        const int cols = 2;

        static float widthScale = 1.0f;
        bool isMoving = false;

        if (IsKeyDown(KEY_W)) { this->position.Y -= speed * deltatime; isMoving = true; }
        if (IsKeyDown(KEY_S)) { this->position.Y += speed * deltatime; isMoving = true; }

        if (IsKeyDown(KEY_A)) {
            this->position.X -= speed * deltatime;
            isMoving = true;
            widthScale = 1.0f;
        }
        if (IsKeyDown(KEY_D)) {
            this->position.X += speed * deltatime;
            isMoving = true;
            widthScale = -1.0f;
        }

        if (isMoving) {
            animTimer += deltatime;
            if (animTimer >= 0.15f) {
                animTimer = 0.0f;
                currentFrame++;
                if (currentFrame >= maxFrames) {
                    currentFrame = 0;
                }
            }
        } else {
            currentFrame = 0;
        }

        if (this->texture.has_value() && this->IsVisible()) {
            int currentColumn = currentFrame % cols;
            int currentRow = currentFrame / cols;

            Rectangle sourceRect = {
                static_cast<float>(currentColumn * frameWidth),
                static_cast<float>(currentRow * frameHeight),
                static_cast<float>(frameWidth) * widthScale,
                static_cast<float>(frameHeight)
            };

            Vector2 drawPos = { this->position.X, this->position.Y };
            DrawTextureRec(this->texture.value(), sourceRect, drawPos, WHITE);
        }
    }
}
