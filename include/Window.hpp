#pragma once

#include <string>

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

namespace Engine {
	struct WindowConfig {
		const int Width = kWindowWidth;
		const int Height = kWindowHeight;
		const bool Vsync = false;
		const bool Debug = true;
		const int FPS = 60;

		const std::string Title = "Game";

		WindowConfig() = default;
	};
	class Window {
	public:
		const WindowConfig config;
		Window() = default;

		void Init();
		void Run();
	};
}
