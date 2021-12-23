#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"

Tile::Tile()
{
	tileTex = new sf::Texture;
	flagTex = new sf::Texture;
	tileTex->loadFromFile("images/tile_hidden.png");
	flagTex->loadFromFile("images/flag.png");
	tileSprite = new sf::Sprite;
	flagSprite = new sf::Sprite;
	tileSprite->setTexture(*tileTex);
	flagSprite->setTexture(*flagTex);
}

void Tile::draw(RenderWindow* window, bool debuggingOn)
{
	tileSprite->setTexture(*tileTex);
	tileSprite->setPosition(sizeX, sizeY);
	window->draw(*tileSprite);

	if (isFlagged)
	{
		flagSprite->setPosition(sizeX, sizeY);
		window->draw(*flagSprite);
	}

	if ((isClicked && isMine) || (debuggingOn && isMine))
	{
		mineSprite->setTexture(*mineTex);
		mineSprite->setPosition(sizeX, sizeY);
		window->draw(*mineSprite);
	}

	else if (mineTex && isClicked && adjMines > 0)
	{
		mineSprite->setTexture(*mineTex);
		mineSprite->setPosition(sizeX, sizeY);
		window->draw(*mineSprite);
	}
}

void Tile::setX(int x)
{
	sizeX = 32 * x;
	locX = x;
}

void Tile::setY(int y)
{
	sizeY = 32 * y;
	locY = y;
}

void Tile::click()
{
	if (isClicked || isFlagged)
	{
		return;
	}

	isClicked = true;

	if (isMine)
	{
		return;
	}
	tileTex->loadFromFile("images\\tile_revealed.png");
}

void Tile::setAdjMines(int num)
{
	adjMines = num;
	if (isMine) 
	{
		mineTex = new Texture;
		mineTex->loadFromFile("images\\mine.png");
		mineSprite = new Sprite;
	}
	else if (adjMines > 0)
	{
		mineTex = new Texture;
		mineTex->loadFromFile(std::string("images\\number_") + std::to_string(num) + ".png");
		mineSprite = new Sprite;
	}
}

void Tile::flag()
{
	if (isClicked)
	{
		return;
	}
	isFlagged = !isFlagged;
}

bool Tile::getClicked() 
{
	return isClicked; 
}

bool Tile::getFlagged()
{
	return isFlagged; 
}

bool Tile::getMine() 
{ 
	return isMine;
}

int Tile::getX() 
{ 
	return locX;
}

int Tile::gety() 
{ 
	return locY; 
}

int Tile::getAdjMines()
{
	return adjMines; 
}

float Tile::getXPixel() 
{
	return sizeX; 
}

float Tile::getYPixel()
{
	return sizeY; 
}