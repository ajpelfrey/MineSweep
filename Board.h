#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "Tile.h"
#include <map>
using namespace std;
using namespace sf;
using std::map;

class Board
{
private:
	Tile* tiles[25][16];
	int totalMines = 0;
	int totalRevealed = 0;
	int totalFlagged = 0;
	bool failed = false;
	bool easyDub = false;
	bool debuggingOn = false;

	std::vector<Texture*> textures;

	Texture* smile;
	Texture* frown;
	Texture* sunglasses;
	Texture* debugTexture;
	Texture* test1Texture;
	Texture* test2Texture;
	Texture* test3Texture;
	Texture* tex0;
	Texture* tex1;
	Texture* tex2;
	Texture* tex3;
	Texture* tex4;
	Texture* tex5;
	Texture* tex6;
	Texture* tex7;
	Texture* tex8;
	Texture* tex9;
	Texture* negativeTexture;

	Sprite* resetButton;
	Sprite* debugSprite;
	Sprite* test1Sprite;
	Sprite* test2Sprite;
	Sprite* test3Sprite;
	Sprite* digit1;
	Sprite* digit2;
	Sprite* digit3;

	void checkDub();
	void finish();
	void restart();
	void makeMines(std::map<int, int> mineLayout);
	std::map<int, int> makeRandVec();
	std::map<int, int> makeFileMines(std::string file_);
	void findAdj();
	
public:
	Board();
	void click(int x, int y, bool leftClicked);
	void clickTile(int x, int y);
	Tile* getTile(int x, int y);
	void draw(RenderWindow* window);
};