#pragma once
#include "Components.h"
#include "Vector2D.h";

class TransformComponent : public Component { // can just be a struct bc everything by default is public 
public:
	Vector2D position;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(float x, int y) {
		position.x = x;
		position.y = y;
	}
	float GetXPos() { return position.x; }
	float GetYPos() { return position.y; }

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