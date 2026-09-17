#include "../include/Errors.hpp"
#include "../include/Entity.hpp"
#include <expected>
#include <raylib.h>
#include <string>

bool Engine::Entity::IsVisible() const {
    return this->visible;
}

void Engine::Entity::SetVisible(const bool visible) {
    this->visible = visible;
}

void Engine::Entity::SetPosition(const Engine::Math::Vec2<float> pos) {
    this->position.X = pos.X;
    this->position.Y = pos.Y;
}

std::expected<void, Engine::Errors::IoError> Engine::Entity::SetTexture(const std::string& file_path) {
    if (!FileExists(file_path.c_str())) {
        return std::unexpected(Engine::Errors::IoError::FileNotFound);
    }

    this->texture = LoadTexture(file_path.c_str());
    if ((*this->texture).id == 0) {
        return std::unexpected(Engine::Errors::IoError::FailedToLoad);
    }

    return {};
}
