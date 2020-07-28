#pragma once
#include "ECS.h"

class PositionComponent : public Component {
public:
	int GetXPos() { return xpos; }
	int GetYPos() { return ypos; }

	void Init() override {
		xpos = 0;
		ypos = 0;
	}

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
