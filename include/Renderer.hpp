#pragma once

#include <iostream>
#include "Window.hpp"
#include <memory>

namespace Engine::Renderer {
	class Renderer {
	public:
		const WindowConfig win_config;

		explicit Renderer(const WindowConfig& config) : win_config(config) {};
		~Renderer();

		void Render();
	};

	std::unique_ptr<Renderer> Init(const WindowConfig& win_config);
}
