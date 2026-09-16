#include "../include/Entity.hpp"

bool Engine::Entity::IsVisible() const {
    return this->visible;
}

void Engine::Entity::SetVisible(const bool visible) {
    this->visible = visible;
}
