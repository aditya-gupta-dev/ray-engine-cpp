#pragma once

#include <string>

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

namespace Engine {
	struct WindowConfig {
		int Width = kWindowWidth;
		int Height = kWindowHeight;
		bool Vsync = false;
		bool Debug = true;

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
