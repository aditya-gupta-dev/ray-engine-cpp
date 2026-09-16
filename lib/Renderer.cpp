#include "../include/Renderer.hpp"
#include "../include/Window.hpp"
#include <raylib.h>
#include <memory>

std::unique_ptr<Engine::Renderer::Renderer> Engine::Renderer::Init(const WindowConfig& config) {
	InitWindow(config.Width, config.Height, config.Title.c_str());
	if (config.Vsync) {
		SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	} else {
	    if (config.FPS > 0) {
	        SetTargetFPS(config.FPS);
	    }
	}

	return std::make_unique<Renderer>(config);
}

void Engine::Renderer::Renderer::Render() {
	while (!WindowShouldClose()) {
		BeginDrawing();
		if (this->win_config.Debug) {
			DrawFPS(20, 20);
		}

		ClearBackground(SKYBLUE);
		EndDrawing();
	}
}

Engine::Renderer::Renderer::~Renderer() {
	CloseWindow();
}
