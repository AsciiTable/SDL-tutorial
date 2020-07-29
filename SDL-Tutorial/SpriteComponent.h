#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		SetTexture(path);
	}

	void Init() override {
		position = &entity->GetComponent<PositionComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = 100;
		srcRect.h = 70;
		destRect.w = 100;
		destRect.h = 70;
	}
	void Update() override {
		destRect.x = position->GetXPos();
		destRect.y = position->GetYPos();
	}
	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void SetTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

};