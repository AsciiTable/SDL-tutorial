#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "Vector2D.h"
#include "AssetManager.h"

Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };
AssetManager* Game::assets = new AssetManager(&manager);

//std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& enemy(manager.AddEntity());
//auto& wall(manager.AddEntity());

//const char* mapfile = "Assets/Art/map-tiles.png";


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

	assets->AddTexture("terrain", "Assets/Art/map-tiles.png");
	assets->AddTexture("player", "Assets/Art/panpo_sheet.png");
	assets->AddTexture("projectile", "Assets/Art/bullet.png");
	map = new Map("terrain", 2, 32);

	//tile0.AddComponent<TileComponent>(200,200,32,32,0);
	//tile1.AddComponent<TileComponent>(250, 250, 32, 32, 1);
	//tile1.AddComponent<ColliderComponent>("dirt");
	//tile2.AddComponent<TileComponent>(150, 150, 32, 32, 2);
	//tile2.AddComponent<ColliderComponent>("grass");

	map->LoadMap("Assets/Art/Tilemaps/test-map-1.txt", 25, 20);

	player.AddComponent<TransformComponent>(1);
	player.AddComponent<SpriteComponent>("player", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	enemy.AddComponent<TransformComponent>(100,500);
	enemy.AddComponent<SpriteComponent>("Assets/Art/floppy_shadow.png");

	player.AddGroup(groupPlayers);
	enemy.AddGroup(groupEnemies);

	// note here: the "speed" variable doesn't do anything, and the range actually changes based on how fast it's travelling
	// the math needs to be redone.
	assets->CreateProjectile(Vector2D(100, 550),  200000, Vector2D(20, -1), 0.0f, "projectile"); 

	//wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	//wall.AddComponent<SpriteComponent>("Assets/Art/dirt.png");
	//wall.AddComponent<ColliderComponent>("wall");

	//wall.AddGroup(groupMap);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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

	SDL_Rect playerCol = player.GetComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.GetComponent<TransformComponent>().position;
	//player -> Update();
	//enemy->Update();
	manager.Refresh();
	manager.Update();
	//std::cout << newPlayer.GetComponent<PositionComponent>().GetXPos() << ", " << newPlayer.GetComponent<PositionComponent>().GetYPos() << std::endl;
	enemy.GetComponent<TransformComponent>().position + Vector2D(2, 2);

	/**Collision detection*/
	//for (auto cc : colliders) {
	//	Collision::AABB(player.GetComponent<ColliderComponent>(), *cc);
	//	//if ()) {
	//	//	player.GetComponent<TransformComponent>().velocity * -1;
	//	//	std::cout << "Wall Hit!" << std::endl;
	//	//}
	//}
	/** Scrolling map */
	//Vector2D pVel = player.GetComponent<TransformComponent>().velocity;
	//int pSpeed = player.GetComponent<TransformComponent>().speed;
	//for (auto t : tiles) {
	//	t->GetComponent<TileComponent>().destRect.x += (-1 * (pVel.x) * (pSpeed));
	//	t->GetComponent<TileComponent>().destRect.y += (-1 * (pVel.y) * (pSpeed));
	//}

	for (auto& c : colliders) {
		SDL_Rect cCol = c->GetComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.GetComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles) {
		if (Collision::AABB(player.GetComponent<ColliderComponent>().collider, p->GetComponent<ColliderComponent>().collider)) {
			std::cout << "Projectile hit player" << std::endl;
			p->Destroy();
		}
	}

	camera.x = player.GetComponent<TransformComponent>().position.x - 400;
	camera.y = player.GetComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;

}

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
	// UNCOMMENT THIS IF YOU DON'T WANT TO SEE COLLIDERS
	for (auto& c : colliders) {
		c->Draw();
	}
	for (auto& p : players) {
		p->Draw();
	}
	for (auto& e : enemies) {
		e->Draw();
	}
	for (auto& p : projectiles) {
		p->Draw();
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

