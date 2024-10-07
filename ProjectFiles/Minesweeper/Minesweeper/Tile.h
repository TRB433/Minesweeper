#pragma once

#include <assert.h>
#include <iostream>
#include "SFML/Graphics.hpp"


using namespace sf;
using namespace std;

class Tile {
public:
	bool flagged = false;
	bool clicked = false;
	int tileNum;
	int closeBombs = 0;
	bool isBomb = false;
	Sprite tileSprite;
	Sprite flagSprite;
	Texture tileTexture;
	Texture flagTexture;
	void init();
	bool clickTile(vector<vector<Tile>> &tiles);
	void flagTile(vector<vector<Tile>> &tiles);
	void setCloseBombs(vector<vector<Tile>> &tiles);
	Text AdjacentBombText;
	Font font;
};
