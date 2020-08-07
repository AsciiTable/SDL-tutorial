#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"


class ColliderComponent :public Component {
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}
	ColliderComponent(std::string t, int xpos, int ypos, int size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void Init() override {
		if (!entity->HasComponent<TransformComponent>()) {
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("Assets/Art/collision.png");
		srcRect = { 0,0,32,32 };
		destRect = { collider.x, collider.y, collider.w, collider.h };

		//Game::colliders.push_back(this);
	}

	void Update() override {
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y - Game::camera.y;
	}

	void Draw() override {
		TextureManager::Draw(tex, srcRect, destRect, SDL_FLIP_NONE);
	}
};