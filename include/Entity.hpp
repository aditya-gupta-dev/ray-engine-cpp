#pragma once

#include "Math.hpp"
namespace Engine {

	class Entity {
	    private:
			bool visible = true;
			Math::Vec2<float> position = Math::Vec2<float>{ 0.0f, 0.0f };

		public:
		    Entity() = default;
            Entity(const float x, const float y) : position(x, y) {};
            Entity(const Math::Vec2<float>& pos) : position(pos.X, pos.Y) {};

            virtual ~Entity() = default;

            virtual void Update(float deltatime) {};

            bool IsVisible() const;

            void SetVisible(const bool visible);
	};

};
