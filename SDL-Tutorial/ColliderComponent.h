#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

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

	void Init() override {
		if (!entity->HasComponent<TransformComponent>()) {
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("Assets/Art/collision.png");

		Game::colliders.push_back(this);
	}

	void Update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width *  transform->scale;
		collider.h = transform->height * transform->scale;
	}

};