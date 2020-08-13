#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component {
public:
	ProjectileComponent(int rng, float sp, Vector2D vel) {
		range = rng;
		speed = sp;
		velocity = vel;
	}
	~ProjectileComponent() {}

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		transform->velocity = velocity;
		std::cout << transform->position << std::endl;
	}
	void Update() override {
		distance += speed;
		if (distance > range) {
			std::cout << "Out of Range" << std::endl;
			entity->Destroy();
		}
		else if(transform->position.x > Game::camera.x + Game::camera.w|| transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h||transform->position.y < Game::camera.y){
			std::cout << "Out of Bounds" << std::endl;
			entity->Destroy();
		}
	}


private:
	TransformComponent* transform;

	int range = 0;
	float speed = 0;
	int distance = 0;
	Vector2D velocity;
};