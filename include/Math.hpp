#pragma once

namespace Engine::Math {
	template <typename T>
	class Vec2 {
	public:
		T X;
		T Y;

		constexpr Vec2() : X(0), Y(0) {};
		constexpr Vec2(T x, T y) : X(x), Y(y) {};

		void Add(Vec2<T>& rhs);

		Vec2<T>& operator+=(const Vec2<T>& rhs);
		Vec2<T>& operator-=(const Vec2<T>& rhs);
		bool operator==(const Vec2<T>& rhs);
	};
}
