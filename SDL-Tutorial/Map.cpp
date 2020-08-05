#include "Map.h"
#include "Game.h"
#include <fstream> // file reading

//#include "TextureManager.h"

//int lvl1[20][25] = { {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

Map::Map() {
	//dirt = TextureManager::LoadTexture("Assets/Art/dirt.png");
	//grass = TextureManager::LoadTexture("Assets/Art/grass.png");
	//water = TextureManager::LoadTexture("Assets/Art/water.png");
	//LoadMap(lvl1);
	//src.x = 0;
	//src.y = 0;
	//src.w = 32;
	//src.h = 32;
	//dest.w = src.w;
	//dest.h = src.h;
	//dest.x = 0;
	//dest.y = 0;
}

Map::~Map() {
	//SDL_DestroyTexture(grass);
	//SDL_DestroyTexture(water);
	//SDL_DestroyTexture(dirt);
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	//for (int row = 0; row < 20; row++) {
	//	for (int column = 0; column < 25; column++) {
	//		map[row][column] = arr[row][column];
	//	}
	//}
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			srcY = atoi(&tile);//atoi converts char to int
			std::cout << srcY << ", ";
			srcY *= 32;
			//mapFile.get(tile);
			//srcX = atoi(&tile);//atoi converts char to int
			//srcX *= 32;
			//std::cout << srcX << std::endl;
			Game::AddTile(srcY, 0, x * 64, y * 64); 
			mapFile.ignore();
		}
	}

	mapFile.close();
}

//void Map::DrawMap() {
//	int type = 0;
//
//	for (int row = 0; row < 20; row++) {
//		for (int column = 0; column < 25; column++) {
//			type = map[row][column];
//
//			dest.x = column * 32;
//			dest.y = row * 32;
//
//			switch (type) {
//			case 0:
//				TextureManager::Draw(water, src, dest);
//				break;
//			case 1:
//				TextureManager::Draw(grass, src, dest);
//				break;
//			case 2:
//				TextureManager::Draw(dirt, src, dest);
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}