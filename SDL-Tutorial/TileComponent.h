#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
#include "SpriteComponent.h"

class TileComponent : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Rect tileRect;
	int tileID;
	char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.h = h;
		tileRect.w = w;
		tileID = id;

		switch (tileID) {
		case 0:
			path = const_cast<char*>("Assets/Art/water.png");
			break;
		case 1:
			path = const_cast <char*>("Assets/Art/dirt.png");
			break;
		case 2:
			path = const_cast < char*>("Assets/Art/grass.png");
			break;
		default:
			break;
		}
	}

	void Init() override {
		entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
		transform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(path);
		sprite = &entity->GetComponent<SpriteComponent>();
	}
};