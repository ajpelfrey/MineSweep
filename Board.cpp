#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <fstream>
#include <stdio.h>
#include "Board.h"

Board::Board()
{
	srand(time(NULL));

	smile = new Texture;
	smile->loadFromFile("images\\face_happy.png");

	frown = new Texture;
	frown->loadFromFile("images\\face_lose.png");

	sunglasses = new Texture;
	sunglasses->loadFromFile("images\\face_win.png");

	resetButton = new Sprite;

	debugTexture = new Texture;
	debugSprite = new Sprite;
	debugTexture->loadFromFile("images\\debug.png");

	test1Texture = new Texture;
	test1Sprite = new Sprite;
	test1Texture->loadFromFile("images\\test_1.png");

	test2Texture = new Texture;
	test2Sprite = new Sprite;
	test2Texture->loadFromFile("images\\test_2.png");

	test3Texture = new Texture;
	test3Sprite = new Sprite;
	test3Texture->loadFromFile("images\\test_3.png");

	digit1 = new Sprite;
	digit2 = new Sprite;
	digit3 = new Sprite;

	tex0 = new Texture;
	tex0->loadFromFile("images\\digits.png", Rect<int>(0, 0, 21, 32));
	tex1 = new Texture;
	tex1->loadFromFile("images\\digits.png", Rect<int>(21, 0, 21, 32));
	tex2 = new Texture;
	tex2->loadFromFile("images\\digits.png", Rect<int>(42, 0, 21, 32));
	tex3 = new Texture;
	tex3->loadFromFile("images\\digits.png", Rect<int>(63, 0, 21, 32));
	tex4 = new Texture;
	tex4->loadFromFile("images\\digits.png", Rect<int>(84, 0, 21, 32));
	tex5 = new Texture;
	tex5->loadFromFile("images\\digits.png", Rect<int>(105, 0, 21, 32));
	tex6 = new Texture;
	tex6->loadFromFile("images\\digits.png", Rect<int>(126, 0, 21, 32));
	tex7 = new Texture;
	tex7->loadFromFile("images\\digits.png", Rect<int>(147, 0, 21, 32));
	tex8 = new Texture;
	tex8->loadFromFile("images\\digits.png", Rect<int>(168, 0, 21, 32));
	tex9 = new Texture;
	tex9->loadFromFile("images\\digits.png", Rect<int>(189, 0, 21, 32));
	negativeTexture = new Texture;
	negativeTexture->loadFromFile("images\\digits.png", Rect<int>(210, 0, 21, 32));

	textures.push_back(tex0);
	textures.push_back(tex1);
	textures.push_back(tex2);
	textures.push_back(tex3);
	textures.push_back(tex4);
	textures.push_back(tex5);
	textures.push_back(tex6);
	textures.push_back(tex7);
	textures.push_back(tex8);
	textures.push_back(tex9);
	textures.push_back(negativeTexture);

	for (unsigned int x = 0; x < 25; x++)
	{
		for (unsigned int y = 0; y < 16; y++)
		{
			tiles[x][y] = new Tile;
			tiles[x][y]->setX(x);
			tiles[x][y]->setY(y);
		}
	}

	std::map<int, int> mineLayout = makeRandVec();
	makeMines(mineLayout);
	findAdj();
}

void Board::click(int x, int y, bool leftClicked)
{
	if (leftClicked && y < 512) 
	{
		int xPos = x / 32;
		int yPos = y / 32;
		clickTile(xPos, yPos);
		checkDub();
	}
	else if (!leftClicked && y < 512)
	{
		int xPos = x / 32;
		int yPos = y / 32;
		Tile* tile = tiles[xPos][yPos];
		if (easyDub || tile->getClicked() || failed) 
		{
			return;
		}
		tile->flag();
		if (tile->getFlagged())
		{
			totalFlagged++; 
		}
		else totalFlagged--;
		checkDub();
	}
	else if (x >= 368 && x <= 432 && y >= 512 && y <= 576 && leftClicked) 
	{
		restart();
		std::map<int, int> mineLayout = makeRandVec();
		makeMines(mineLayout);
		findAdj();
	}
	else if (x >= 496 && x <= 560 && y >= 512 && y <= 576 && leftClicked)
	{
		debuggingOn = !debuggingOn;
	}
	else if (x >= 560 && x <= 624 && y >= 512 & y < 576 && leftClicked) 
	{
		restart();
		std::map<int, int> mineLayout = makeFileMines("boards\\testboard1.brd");
		makeMines(mineLayout);
		findAdj();
	}
	else if (x >= 624 && x <= 688 && y >= 512 && y < 576 && leftClicked)
	{
		restart();
		std::map<int, int> mineLayout = makeFileMines("boards\\testboard2.brd");
		makeMines(mineLayout);
		findAdj();
	}
	else if (x >= 688 && x <= 752 && y >= 512 && y < 576 && leftClicked)
	{
		restart();
		std::map<int, int> mineLayout = makeFileMines("boards\\testboard3.brd");
		makeMines(mineLayout);
		findAdj();
	}
}

void Board::clickTile(int xPos, int yPos)
{
	Tile* tile = tiles[xPos][yPos];

	if (tile->getClicked() || easyDub || failed || tile->getFlagged())
	{
		return;
	}

	tile->click();
	totalRevealed++;
	if (tile->getMine())
	{
		finish();
	}

	int adjacentMines = tiles[xPos][yPos]->getAdjMines();
	if (adjacentMines == 0)
	{
		if (xPos > 0)
		{
			clickTile(xPos - 1, yPos);
		}
		if (xPos < 24)
		{
			clickTile(xPos + 1, yPos);
		}
		if (yPos > 0)
		{
			clickTile(xPos, yPos - 1);
		}
		if (yPos < 15)
		{
			clickTile(xPos, yPos + 1);
		}
		if (xPos > 0 && yPos > 0)
		{
			clickTile(xPos - 1, yPos - 1);
		}
		if (xPos > 0 && yPos < 15)
		{
			clickTile(xPos - 1, yPos + 1);
		}
		if (xPos < 24 && yPos > 0)
		{
			clickTile(xPos + 1, yPos - 1);
		}
		if (xPos < 24 && yPos < 15)
		{
			clickTile(xPos + 1, yPos + 1);
		}
	}
}

Tile* Board::getTile(int x, int y)
{
	return tiles[x][y];
}

void Board::draw(RenderWindow* window)
{
	for (auto& tile : tiles) {
		for (unsigned int j = 0; j < 16; j++)
		{
			tile[j]->draw(window, debuggingOn);
		}
	}

	resetButton->setPosition(368, 512);
	if (failed)
	{
		resetButton->setTexture(*frown);
	}
	else if (easyDub)
	{
		resetButton->setTexture(*sunglasses);
	}
	else {
		resetButton->setTexture(*smile);
	}
	window->draw(*resetButton);

	debugSprite->setTexture(*debugTexture);
	debugSprite->setPosition(496, 512);
	window->draw(*debugSprite);

	test1Sprite->setTexture(*test1Texture);
	test1Sprite->setPosition(560, 512);
	window->draw(*test1Sprite);

	test2Sprite->setTexture(*test2Texture);
	test2Sprite->setPosition(624, 512);
	window->draw(*test2Sprite);

	test3Sprite->setTexture(*test3Texture);
	test3Sprite->setPosition(688, 512);
	window->draw(*test3Sprite);

	int score = totalMines - totalFlagged;
	int dig1 = 0;
	int dig2 = 0;
	int dig3 = 0;
	if (score < 0) {
		dig1 = 10;
		dig2 = (score / 10) * -1;
		dig3 = (score % 10) * -1;
	}
	else {
		dig1 = score / 100;
		dig2 = score / 10;
		dig3 = score % 10;
	}

	digit1->setTexture(*textures[dig1]);
	digit1->setPosition(0, 512);
	window->draw(*digit1);
	digit2->setTexture(*textures[dig2]);
	digit2->setPosition(22, 512);
	window->draw(*digit2);
	digit3->setTexture(*textures[dig3]);
	digit3->setPosition(44, 512);
	window->draw(*digit3);
}

void Board::checkDub()
{
	if (totalFlagged == totalMines && totalRevealed + totalFlagged == 400)
	{
		easyDub = true;
	}
}

void Board::finish()
{
	failed = true;
}

void Board::restart()
{
	totalMines = 0;
	totalRevealed = 0;
	totalFlagged = 0;
	failed = false;
	easyDub = false;

	for (auto& tile : tiles) {
		for (auto& j : tile) {
			delete j;
		}
	}

	for (unsigned int x = 0; x < 25; x++)
	{
		for (unsigned int y = 0; y < 16; y++)
		{
			tiles[x][y] = new Tile;
			tiles[x][y]->setX(x);
			tiles[x][y]->setY(y);
		}
	}
}

void Board::makeMines(std::map<int, int> mineLayout)
{
	for (unsigned int x = 0; x < 25; x++)
	{
		for (unsigned int y = 0; y < 16; y++)
		{
			Tile* tile = tiles[x][y];
			int mine = y * 25 + x;
			tile->setMine(mineLayout[mine] != 0);
			if (mineLayout[mine] == 1) totalMines++;
		}
	}
}

std::map<int, int> Board::makeRandVec()
{
	std::map<int, int> ret;

	for (unsigned int i = 0; i < 400; i++)
	{
		ret[i] = 0;
	}
	int numGenerated = 0;
	while (numGenerated < 50)
	{
		int gen = rand() % 400;
		if (ret[gen] == 0)
		{
			numGenerated++;
			ret[gen] = 1;
		}
	}

	return ret;
}

std::map<int, int> Board::makeFileMines(std::string file_)
{
	std::map<int, int> ret;
	std::ifstream file(file_);
	std::string line;

	int count = 0;
	for (unsigned int i = 0; i < 16; i++)
	{
		getline(file, line);
		for (unsigned int j = 0; j < 25; j++)
		{
			int mine = std::stoi(line.substr(j, 1));
			ret[count] = mine;
			count++;
		}
	}
	return ret;
}

void Board::findAdj()
{
	for (unsigned int x = 0; x < 25; x++)
	{
		for (unsigned int y = 0; y < 16; y++)
		{
			int numAdjacent = 0;
			if (x > 0)
			{
				if (tiles[x - 1][y]->getMine()) numAdjacent++;
			}
			if (x < 24)
			{
				if (tiles[x + 1][y]->getMine()) numAdjacent++;
			}
			if (y > 0)
			{
				if (tiles[x][y - 1]->getMine()) numAdjacent++;
			}
			if (y < 15)
			{
				if (tiles[x][y + 1]->getMine()) numAdjacent++;
			}
			if (x > 0 && y > 0)
			{
				if (tiles[x - 1][y - 1]->getMine()) numAdjacent++;
			}
			if (x > 0 && y < 15)
			{
				if (tiles[x - 1][y + 1]->getMine()) numAdjacent++;
			}
			if (x < 24 && y > 0)
			{
				if (tiles[x + 1][y - 1]->getMine()) numAdjacent++;
			}
			if (x < 24 && y < 15)
			{
				if (tiles[x + 1][y + 1]->getMine()) numAdjacent++;
			}
			tiles[x][y]->setAdjMines(numAdjacent);
		}
	}
}