#pragma once
#include "Components.h"

class TransformComponent : public Component {
public:
	TransformComponent() {
		xpos = 0;
		ypos = 0;
	}
	TransformComponent(int x, int y) {
		xpos = x;
		ypos = y;
	}
	int GetXPos() { return xpos; }
	int GetYPos() { return ypos; }

	//void Init() override {
	//	xpos = 0;
	//	ypos = 0;
	//}

	void Update() override {
		xpos++;
		ypos++;
	}

	void SetPos(int x, int y) {
		xpos = x;
		ypos = y;
	}


private:
	int xpos;
	int ypos;

};