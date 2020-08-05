#pragma once
#include "Components.h"
#include "Vector2D.h";

class TransformComponent : public Component { // can just be a struct bc everything by default is public 
public:
	Vector2D position;
	Vector2D velocity;
	float speed = 3.0f;

	int height = 70;
	int width = 100;
	int scale = 1;


	TransformComponent() {
		position.Zero();
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(int sc) {
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	float GetXPos() { return position.x; }
	float GetYPos() { return position.y; }

	void Init() override {
		velocity.Zero();
	}

	//void Update() override {
	//	position.x += velocity.x * speed;
	//	position.y += velocity.y * speed;
	//}

	//void Init() override {
	//	xpos = 0;
	//	ypos = 0;
	//}

	//void Update() override {
	//	xpos++;
	//	ypos++;
	//}

	//void SetPos(int x, int y) {
	//	xpos = x;
	//	ypos = y;
	//}

};