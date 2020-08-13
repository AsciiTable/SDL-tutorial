#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"

class AssetManager {
public:
	AssetManager(Manager* man);
	~AssetManager();

	//Game objects
	void CreateProjectile(Vector2D pos, int range, Vector2D vel, float speed, std::string id);

	//Texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	std::map<std::string, SDL_Texture*> textures;
	Manager* manager;
};