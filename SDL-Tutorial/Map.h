#pragma once
//#include "Game.h"
#include <string>
class Map
{
public:
	//Map(const char* mapFP, float mscale, int tsize);
	Map(std::string tID, float mscale, int tsize);
	~Map();
	
	void AddTile(int srcX, int srcY, int xpos, int ypos);
	void LoadMap(std::string path, int sizeX, int sizeY);
	//void LoadMap(int arr[20][25]);
	//void DrawMap();

private:
	//const char* mapFilePath;
	std::string texID;
	float mapScale;
	int tileSize;
	float scaledSize;
	//SDL_Rect src, dest;

	//SDL_Texture* dirt;
	//SDL_Texture* grass;
	//SDL_Texture* water;

	//int map[20][25];
};

