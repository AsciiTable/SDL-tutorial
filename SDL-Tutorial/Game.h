#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean(); // memory management
	bool Running();
	static SDL_Renderer* renderer;
	static SDL_Event event;
	//static std::vector<ColliderComponent*> colliders;
	
	static SDL_Rect camera;
	static AssetManager* assets;


	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles
	};


private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;
};

