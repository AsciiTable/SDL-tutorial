#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.AddEntity());
auto& enemy(manager.AddEntity());

Game::Game() {

}

Game::~Game() {

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { // if successfully initialized everything
		std::cout << "Subsystems Initialized!..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) { // if window is created
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) { // if renderer is created
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	map = new Map();

	player.AddComponent<TransformComponent>();
	player.AddComponent<SpriteComponent>("Assets/Art/panpo_shadow.png");
	enemy.AddComponent<TransformComponent>(100,500);
	enemy.AddComponent<SpriteComponent>("Assets/Art/floppy_shadow.png");
}

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update() {
	//player -> Update();
	//enemy->Update();
	manager.Refresh();
	manager.Update();
	//std::cout << newPlayer.GetComponent<PositionComponent>().GetXPos() << ", " << newPlayer.GetComponent<PositionComponent>().GetYPos() << std::endl;
	if (player.GetComponent<PositionComponent>().GetXPos() > 100) {
		player.GetComponent<SpriteComponent>().SetTexture("Assets/Art/floppy_shadow.png");
	}
}

void Game::Render() {
	SDL_RenderClear(renderer); // clears the buffer
	// Add things to render
	map->DrawMap();
	manager.Draw();
	//player->Render();
	//enemy->Render();
	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned." << std::endl;
}

bool Game::Running() {
	return isRunning;
}

