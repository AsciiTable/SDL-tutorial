#pragma once
#include "ECS.h"
//#include "TransformComponent.h"
#include "SDL.h"
//#include "SpriteComponent.h"
#include "AssetManager.h"

class TileComponent : public Component {
public:
	//TransformComponent* transform;
	//SpriteComponent* sprite;
	//SDL_Rect tileRect;
	//int tileID;
	//char* path;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, float tscale, std::string id) {
		//texture = TextureManager::LoadTexture(path);
		texture = Game::assets->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = tsize;
		srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = tsize * tscale;
		destRect.h = tsize * tscale;
	}

	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

	void Update() override {
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	//TileComponent(int x, int y, int w, int h, int id) {
	//	//tileRect.x = x;
	//	//tileRect.y = y;
	//	//tileRect.h = h;
	//	//tileRect.w = w;
	//	//tileID = id;

	//	//switch (tileID) {
	//	//case 0:
	//	//	path = const_cast<char*>("Assets/Art/water.png");
	//	//	break;
	//	//case 1:
	//	//	path = const_cast <char*>("Assets/Art/grass.png");
	//	//	break;
	//	//case 2:
	//	//	path = const_cast < char*>("Assets/Art/dirt.png");
	//	//	break;
	//	//default:
	//	//	break;
	//	//}
	//}

	//void Init() override {
	//	//entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
	//	//transform = &entity->GetComponent<TransformComponent>();

	//	//entity->AddComponent<SpriteComponent>(path);
	//	//sprite = &entity->GetComponent<SpriteComponent>();
	//}
};