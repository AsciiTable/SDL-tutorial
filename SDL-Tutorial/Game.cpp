#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "Vector2D.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.AddEntity());
auto& enemy(manager.AddEntity());
auto& wall(manager.AddEntity());

const char* mapfile = "Assets/Art/map-tiles.png";

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

//auto& tile0(manager.AddEntity());
//auto& tile1(manager.AddEntity());
//auto& tile2(manager.AddEntity());

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

	//tile0.AddComponent<TileComponent>(200,200,32,32,0);
	//tile1.AddComponent<TileComponent>(250, 250, 32, 32, 1);
	//tile1.AddComponent<ColliderComponent>("dirt");
	//tile2.AddComponent<TileComponent>(150, 150, 32, 32, 2);
	//tile2.AddComponent<ColliderComponent>("grass");

	Map::LoadMap("Assets/Art/Tilemaps/test-map-1.txt", 25, 20);

	player.AddComponent<TransformComponent>();
	player.AddComponent<SpriteComponent>("Assets/Art/panpo_sheet.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	enemy.AddComponent<TransformComponent>(100,500);
	enemy.AddComponent<SpriteComponent>("Assets/Art/floppy_shadow.png");

	player.AddGroup(groupPlayers);
	enemy.AddGroup(groupEnemies);

	//wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	//wall.AddComponent<SpriteComponent>("Assets/Art/dirt.png");
	//wall.AddComponent<ColliderComponent>("wall");

	wall.AddGroup(groupMap);
}

void Game::HandleEvents() {
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
	enemy.GetComponent<TransformComponent>().position + Vector2D(2, 2);

	for (auto cc : colliders) {
		Collision::AABB(player.GetComponent<ColliderComponent>(), *cc);
		//if ()) {
		//	player.GetComponent<TransformComponent>().velocity * -1;
		//	std::cout << "Wall Hit!" << std::endl;
		//}
	}


}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::Render() {
	SDL_RenderClear(renderer); // clears the buffer
	// Add things to render
	//map->DrawMap();
	//manager.Draw(); // draws in order of creation
	//player->Render();
	//enemy->Render();
	for (auto& t : tiles) {
		t->Draw();
	}
	for (auto& p : players) {
		p->Draw();
	}
	for (auto& e : enemies) {
		e->Draw();
	}
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

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.AddGroup(groupMap);
}

