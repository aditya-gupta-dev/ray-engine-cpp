#pragma once

#include "Math.hpp"
#include "Errors.hpp"
#include <expected>
#include <optional>
#include <raylib.h>
#include <string>
namespace Engine {

	class Entity {
	    protected:
			bool visible = true;
			Math::Vec2<float> position = Math::Vec2<float>{ 0.0f, 0.0f };
			std::optional<Texture> texture = std::nullopt;

		public:
		    Entity() = default;
            Entity(const float x, const float y) : position(x, y), texture(std::nullopt) {};
            Entity(const Math::Vec2<float>& pos) : position(pos.X, pos.Y), texture(std::nullopt) {};

            virtual ~Entity() = default;

            virtual void Update(float deltatime) {};

            bool IsVisible() const;

            void SetVisible(const bool visible);
            void SetPosition(const Engine::Math::Vec2<float> pos);
            std::expected<void, Engine::Errors::IoError> SetTexture(const std::string& file_path);
	};

};
