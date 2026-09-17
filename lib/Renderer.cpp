#include "../include/Player.hpp"
#include "../include/Assets.hpp"
#include "../include/Renderer.hpp"
#include "../include/Window.hpp"
#include <expected>
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

void Engine::Renderer::Renderer::LoadAssets() {

    auto player = Engine::Player();
    std::expected<void, Engine::Errors::IoError> result = player.SetTexture(Engine::Assets::player_texture_file_path);
    if (!result) {
        TraceLog(LOG_ERROR, "failed to load player texture: %s", result.error());
        return;
    }
    player.SetPosition(Engine::Math::Vec2<float>(300, 30));

    this->players.push_back(player);
}

void Engine::Renderer::Renderer::Render() {
    this->LoadAssets();
    while (!WindowShouldClose()) {
        float frame_time = GetFrameTime();
        BeginDrawing();
		if (this->win_config.Debug) {
			DrawFPS(20, 20);
		}

		for(auto& player: this->players) {
		    player.Update(frame_time);
		}

		ClearBackground(SKYBLUE);
		EndDrawing();
	}
}

Engine::Renderer::Renderer::~Renderer() {
	CloseWindow();
}
