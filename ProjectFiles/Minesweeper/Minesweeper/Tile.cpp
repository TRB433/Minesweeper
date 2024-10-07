#include <assert.h>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Tile.h"


using namespace sf;
using namespace std;

void Tile::init() {
	if (!tileTexture.loadFromFile("data/tile2.png")) {
		assert(false);
	}

	tileSprite.setTexture(tileTexture);

	if (!font.loadFromFile("data/Roboto-BoldItalic.ttf")) {
		assert(false);
	}

	AdjacentBombText.setFont(font);
	AdjacentBombText.setCharacterSize(25);
	AdjacentBombText.setColor(Color::White);

	if (!flagTexture.loadFromFile("data/flag.png")) {
		assert(false);
	}

	flagSprite.setTexture(flagTexture);
	flagSprite.setScale(0.0f, 0.0f);
}

bool Tile::clickTile(vector<vector<Tile>> &tiles) {
	
	if (isBomb) {
		return true;
	}
	else {		
		for (int i = 0; i < tiles.size(); i++) {
			for (int j = 0; j < tiles[i].size(); j++) {
				if (tiles[i][j].tileNum == tileNum) {	

					clicked = true;

					for (int i = 0; i < tiles.size(); i++) {
						for (int j = 0; j < tiles[i].size(); j++) {
							if (tiles[i][j].tileNum == tileNum) {
								

								if (i < 9 && tiles[i + 1][j].closeBombs == 0 && tiles[i + 1][j].clicked == false && tiles[i + 1][j].isBomb == false) {
									tiles[i + 1][j].clickTile(tiles);
								}
								if (i > 0 && tiles[i - 1][j].closeBombs == 0 && tiles[i - 1][j].clicked == false && tiles[i - 1][j].isBomb == false) {
									tiles[i - 1][j].clickTile(tiles);
								}
								if (j < 9 && tiles[i][j + 1].closeBombs == 0 && tiles[i][j + 1].clicked == false && tiles[i][j + 1].isBomb == false) {
									tiles[i][j + 1].clickTile(tiles);
								}
								if (j > 0 && tiles[i][j - 1].closeBombs == 0 && tiles[i][j - 1].clicked == false && tiles[i][j - 1].isBomb == false) {
									tiles[i][j - 1].clickTile(tiles);
								}
								if (i < 9 && j < 9 && tiles[i + 1][j + 1].closeBombs == 0 && tiles[i + 1][j + 1].clicked == false && tiles[i + 1][j + 1].isBomb == false) {
									tiles[i + 1][j + 1].clickTile(tiles);
								}
								if (i < 9 && j > 0 && tiles[i + 1][j - 1].closeBombs == 0 && tiles[i + 1][j - 1].clicked == false && tiles[i + 1][j - 1].isBomb == false) {
									tiles[i + 1][j - 1].clickTile(tiles);
								}
								if (i > 0 && j > 0 && tiles[i - 1][j - 1].closeBombs == 0 && tiles[i - 1][j - 1].clicked == false && tiles[i - 1][j - 1].isBomb == false) {
									tiles[i - 1][j - 1].clickTile(tiles);
								}
								if (i > 0 && j < 9 && tiles[i - 1][j + 1].closeBombs == 0 && tiles[i - 1][j + 1].clicked == false && tiles[i - 1][j + 1].isBomb == false) {
									tiles[i - 1][j + 1].clickTile(tiles);
								}

								if (tiles[i][j].closeBombs == 0) {
									if (i < 9 && tiles[i + 1][j].clicked == false && tiles[i + 1][j].isBomb == false) {
										tiles[i + 1][j].clickTile(tiles);
									}
									if (i > 0 && tiles[i - 1][j].clicked == false && tiles[i - 1][j].isBomb == false) {
										tiles[i - 1][j].clickTile(tiles);
									}
									if (j < 9 && tiles[i][j + 1].clicked == false && tiles[i][j + 1].isBomb == false) {
										tiles[i][j + 1].clickTile(tiles);
									}
									if (j > 0 && tiles[i][j - 1].clicked == false && tiles[i][j - 1].isBomb == false) {
										tiles[i][j - 1].clickTile(tiles);
									}
									if (i < 9 && j < 9 && tiles[i + 1][j + 1].clicked == false && tiles[i + 1][j + 1].isBomb == false) {
										tiles[i + 1][j + 1].clickTile(tiles);
									}
									if (i < 9 && j > 0 && tiles[i + 1][j - 1].clicked == false && tiles[i + 1][j - 1].isBomb == false) {
										tiles[i + 1][j - 1].clickTile(tiles);
									}
									if (i > 0 && j > 0 && tiles[i - 1][j - 1].clicked == false && tiles[i - 1][j - 1].isBomb == false) {
										tiles[i - 1][j - 1].clickTile(tiles);
									}
									if (i > 0 && j < 9 && tiles[i - 1][j + 1].clicked == false && tiles[i - 1][j + 1].isBomb == false) {
										tiles[i - 1][j + 1].clickTile(tiles);
									}
								}
							}
						}
					}

					flagged = false;
					

					tiles[i][j].tileSprite.setScale(0.0f, 0.0f);

					if (closeBombs != 0) {
						AdjacentBombText.setString(to_string(closeBombs));
					}

					return false;
				}
			}
		}
	}
	
}

void Tile::setCloseBombs(vector<vector<Tile>> &tiles) {
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j].tileNum == tileNum) {
				int x = i;
				int y = j;
				if (x < 9 && tiles[x + 1][y].isBomb) {
					closeBombs++;
				}
				if (x > 0 && tiles[x - 1][y].isBomb) {
					closeBombs++;
				}
				if (y < 9 && tiles[x][y + 1].isBomb) {
					closeBombs++;
				}
				if (y > 0 && tiles[x][y - 1].isBomb) {
					closeBombs++;
				}
				if (x < 9 && y < 9 && tiles[x + 1][y + 1].isBomb) {
					closeBombs++;
				}
				if (x < 9 && y > 0 && tiles[x + 1][y - 1].isBomb) {
					closeBombs++;
				}
				if (x > 0 && y > 0 && tiles[x - 1][y - 1].isBomb) {
					closeBombs++;
				}
				if (x > 0 && y < 9 && tiles[x - 1][y + 1].isBomb) {
					closeBombs++;
				}
			}
		}
	}
}

void Tile::flagTile(vector<vector<Tile>> &tiles) {
	if (!flagged) {
		flagged = true;
		flagSprite.setScale(0.225f, 0.225f);
	}
	else {
		flagged = false;
		flagSprite.setScale(0.0f, 0.0f);
	}
}

