#include "../include/Window.hpp"
#include "../include/Renderer.hpp"
#include <raylib.h>

void Engine::Window::Init() {
	auto renderer = Engine::Renderer::Init(this->config);
	renderer->Render();
}
