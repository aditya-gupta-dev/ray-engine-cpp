#pragma once

#include <iostream>
#include "Player.hpp"
#include "Window.hpp"
#include <memory>
#include <vector>

namespace Engine::Renderer {
	class Renderer {
	public:
		const WindowConfig win_config;
		std::vector<Player> players;

		explicit Renderer(const WindowConfig& config) : win_config(config) {};
		~Renderer();

		void LoadAssets();
		void Render();
	};

	std::unique_ptr<Renderer> Init(const WindowConfig& win_config);
}
