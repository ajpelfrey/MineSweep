#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

class Tile
{
private:
	float sizeX = 0.0;
	float sizeY = 0.0;
	int locX = 0;
	int locY = 0;
	bool isMine = false;
	bool isFlagged = false;
	bool isClicked = false;
	int adjMines = 0;

	Texture* tileTex;
	Texture* mineTex;
	Texture* flagTex;

	Sprite* tileSprite;
	Sprite* mineSprite;
	Sprite* flagSprite;

public:
	Tile();
	void draw(RenderWindow* window, bool debuggingOn);
	void click();
	void flag();
	void setMine(bool val) { isMine = val; }
	void setX(int x); 
	void setY(int y); 
	void setAdjMines(int num);
	bool getClicked();
	bool getFlagged();
	bool getMine(); 
	int getX(); 
	int gety();
	int getAdjMines();
	float getXPixel(); 
	float getYPixel();
};
