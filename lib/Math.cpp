#include "../include/Math.hpp"

template<typename T>
void Engine::Math::Vec2<T>::Add(Vec2<T>& rhs) {
	this->X = this->X + rhs.X;
	this->Y = this->Y + rhs.Y;
}

template<typename T>
Engine::Math::Vec2<T>& Engine::Math::Vec2<T>::operator+=(const Engine::Math::Vec2<T>& rhs) {
	this->X += rhs.X;
	this->Y += rhs.Y;

	return *this;
}

template<typename T>
Engine::Math::Vec2<T>& Engine::Math::Vec2<T>::operator-=(const Engine::Math::Vec2<T>& rhs) {
	this->X -= rhs.X;
	this->Y -= rhs.Y;

	return *this;
}
