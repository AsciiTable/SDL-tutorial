#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"

class SpriteComponent : public Component {
public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id) {
		SetTexture(id);
	}
	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;
		//SetTexture(path);

		Animation idle = Animation(0, 9, 300);
		Animation walk = Animation(1, 12, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
		SetTexture(id);
	}

	~SpriteComponent() {
		//SDL_DestroyTexture(texture);
	}

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}
	void Update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames); // this is what iterates through frames
		}

		srcRect.y = animIndex * transform->height; // gets the index of the animation

		destRect.x = static_cast<int>(transform->GetXPos()) - Game::camera.x;
		destRect.y = static_cast<int>(transform->GetYPos()) - Game::camera.y;
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height*transform->scale;
	}
	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void SetTexture(std::string id) {
		//texture = TextureManager::LoadTexture(path);
		texture = Game::assets->GetTexture(id);
	}


	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;  // delay in frames by milliseconds
};