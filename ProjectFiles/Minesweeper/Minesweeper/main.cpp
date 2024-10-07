#include <assert.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "Tile.h"


using namespace sf;
using namespace std;

//2d integer dimensions
struct Dim2Di
{
	int x, y;
};

//2d float dimensions
struct Dim2Df
{
	float x, y;
};


//constants
namespace GC
{	
	const Dim2Di SCREEN_RES{ 1000,1000 };

	const char ESCAPE_KEY{ 27 };
	const char ENTER_KEY{ 13 };

	const float TILE_WIDTH{ 60.0f };
}

enum class gameMode { INTRO, GAME, DEAD };



void gameOver(gameMode &gMode) {
	void drawGame(gameMode &gMode);
	Text goText;
	Font font;

	if (!font.loadFromFile("data/Roboto-BoldItalic.ttf")) {
		assert(false);
	}

	goText.setFont(font);
	goText.setString("You died! Press enter to restart!");
	goText.setCharacterSize(36);
	goText.setPosition(GC::SCREEN_RES.x / 2 - goText.getGlobalBounds().width / 2, GC::SCREEN_RES.y / 2 - goText.getGlobalBounds().height);
	goText.setColor(Color::White);
	

	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "Game Over!");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{			
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close();		
				if (event.text.unicode == GC::ENTER_KEY) {
					gMode = gameMode::GAME;
				}
			}

		}

		if (gMode == gameMode::GAME) {
			window.close();
			drawGame(gMode);
		}

		Sprite bg;
		Texture bgTexture;

		if (!bgTexture.loadFromFile("data/bg.jpg")) {
			assert(false);
		}

		bg.setTexture(bgTexture);
		bg.setPosition(GC::SCREEN_RES.x / 2 - bg.getGlobalBounds().width / 2, GC::SCREEN_RES.y / 2 - bg.getGlobalBounds().height / 2);

		window.draw(bg);

		window.draw(goText);
		window.display();
		window.clear();
	}
}

void gameWin(gameMode &gMode, int elapsed) {
	void drawGame(gameMode &gMode);
	Text goText;
	Font font;

	if (!font.loadFromFile("data/Roboto-BoldItalic.ttf")) {
		assert(false);
	}

	goText.setFont(font);
	string goString = "You won in " + to_string(elapsed) + " seconds!";
	goText.setString(goString);	
	goText.setCharacterSize(36);
	goText.setPosition(GC::SCREEN_RES.x / 2 - goText.getGlobalBounds().width / 2, GC::SCREEN_RES.y / 2 - goText.getGlobalBounds().height);
	goText.setColor(Color::White);


	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "You Win");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close();
				if (event.text.unicode == GC::ENTER_KEY) {
					gMode = gameMode::GAME;
				}
			}

		}

		if (gMode == gameMode::GAME) {
			window.close();
			drawGame(gMode);
		}

		Sprite bg;
		Texture bgTexture;

		if (!bgTexture.loadFromFile("data/bg.jpg")) {
			assert(false);
		}

		bg.setTexture(bgTexture);
		bg.setPosition(GC::SCREEN_RES.x / 2 - bg.getGlobalBounds().width / 2, GC::SCREEN_RES.y / 2 - bg.getGlobalBounds().height / 2);

		window.draw(bg);

		window.draw(goText);
		window.display();
		window.clear();
	}
}

void drawGame(gameMode &gMode) {	
	
	Clock clock;
	int elapsed = 0;
	Text timerText;
	Font font;

	if (!font.loadFromFile("data/Roboto-BoldItalic.ttf")) {
		assert(false);
	}

	timerText.setFont(font);
	timerText.setCharacterSize(36);
	timerText.setPosition(GC::SCREEN_RES.x / 2, GC::SCREEN_RES.y / 10);

	bool firstMove = true;

	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "Minesweeper");

	

	Tile tile;	

	vector<vector<Tile>> mapTiles{ 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile}, 
		{tile, tile, tile, tile, tile, tile, tile, tile, tile, tile} 
	};
	
	float offsetX = -270.0f;
	float offsetY = -300.0f;
	int num = 0;
	for (int i = 0; i < mapTiles.size(); i++) {		
		for (int j = 0; j < mapTiles[i].size(); j++) {						
			mapTiles[i][j].tileNum = num;
			mapTiles[i][j].init();
			mapTiles[i][j].tileSprite.setPosition(GC::SCREEN_RES.x / 2.0f + offsetX - mapTiles[i][j].tileSprite.getGlobalBounds().width / 2.0f, GC::SCREEN_RES.y / 2 + offsetY - mapTiles[i][j].tileSprite.getGlobalBounds().height / 2);
			mapTiles[i][j].flagSprite.setPosition(mapTiles[i][j].tileSprite.getPosition().x + 10.0f, mapTiles[i][j].tileSprite.getPosition().y + 3.0f);
			mapTiles[i][j].AdjacentBombText.setPosition((mapTiles[i][j].tileSprite.getPosition().x + 20.0f), mapTiles[i][j].tileSprite.getPosition().y + 12.5f);

			offsetX += GC::TILE_WIDTH;
			num++;
		}
		offsetY += GC::TILE_WIDTH;
		offsetX = -270.0f;
	}
	
	while (window.isOpen()) {
		
		elapsed = clock.getElapsedTime().asSeconds();
				
		timerText.setString(to_string(elapsed));		

		Event event;
		while (window.pollEvent(event))
		{			
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY) {
					window.close();					
				}				
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				for (int i = 0; i < mapTiles.size(); i++) {
					for (int j = 0; j < mapTiles[i].size(); j++) {
						if (Mouse::getPosition(window).x - mapTiles[i][j].tileSprite.getPosition().x < 60 && Mouse::getPosition(window).x - mapTiles[i][j].tileSprite.getPosition().x > 0 && Mouse::getPosition(window).y - mapTiles[i][j].tileSprite.getPosition().y > 0 && Mouse::getPosition(window).y - mapTiles[i][j].tileSprite.getPosition().y < 60 && mapTiles[i][j].clicked == false && mapTiles[i][j].flagged == false) {							
							if (firstMove) {
								for (int i = 0; i < mapTiles.size(); i++) {
									for (int j = 0; j < mapTiles[i].size(); j++) {										

										int random = rand() % 5;
										if (random == 1) {
											mapTiles[i][j].isBomb = true;
										}	

									}
								}

								for (int i = 0; i < mapTiles.size(); i++) {
									for (int j = 0; j < mapTiles[i].size(); j++) {
										mapTiles[i][j].setCloseBombs(mapTiles);
									}
								}	

								firstMove = false;
							}
							if (mapTiles[i][j].clickTile(mapTiles)) {									
								gMode = gameMode::DEAD;
							}							
						}
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
				for (int i = 0; i < mapTiles.size(); i++) {
					for (int j = 0; j < mapTiles[i].size(); j++) {
						if (Mouse::getPosition(window).x - mapTiles[i][j].tileSprite.getPosition().x < 60 && Mouse::getPosition(window).x - mapTiles[i][j].tileSprite.getPosition().x > 0 && Mouse::getPosition(window).y - mapTiles[i][j].tileSprite.getPosition().y > 0 && Mouse::getPosition(window).y - mapTiles[i][j].tileSprite.getPosition().y < 60 && mapTiles[i][j].clicked == false) {
							mapTiles[i][j].flagTile(mapTiles);
						}

					}
				}
			}
			
		}
		
		int bombCount = 0;
		int clickCount = 0;
		for (int i = 0; i < mapTiles.size(); i++) {
			for (int j = 0; j < mapTiles[i].size(); j++) {
				if (mapTiles[i][j].isBomb == true) {
					bombCount++;
				}

				if (mapTiles[i][j].clicked == true) {
					clickCount++;
				}
			}
		}

		if (100 - bombCount == clickCount) {
			window.close();			
			gMode = gameMode::DEAD;
			gameWin(gMode, elapsed);
		}
		
		if (gMode == gameMode::DEAD) {
			window.close();
			gameOver(gMode);
		}
		
		Sprite bg;
		Texture bgTexture;

		if (!bgTexture.loadFromFile("data/bg.jpg")) {
			assert(false);
		}

		bg.setTexture(bgTexture);
		bg.setPosition(GC::SCREEN_RES.x / 2 - bg.getGlobalBounds().width / 2, GC::SCREEN_RES.y / 2 - bg.getGlobalBounds().height / 2);

		window.draw(bg);

		for (int i = 0; i < mapTiles.size(); i++) {
			for (int j = 0; j < mapTiles.size(); j++) {
				window.draw(mapTiles[i][j].AdjacentBombText);
				window.draw(mapTiles[i][j].tileSprite);
				window.draw(timerText);
				if (mapTiles[i][j].flagged) {
					window.draw(mapTiles[i][j].flagSprite);
				}
			}
		}
		

		
		window.display();
		
		window.clear();
	}
}

void drawIntro(gameMode &gMode) {
	void drawGame(gameMode &gMode);
	Font font;
	Text introText;
	Sprite bg;
	Texture bgTexture;

	if (!font.loadFromFile("data/Roboto-BoldItalic.ttf")) {
		assert(false);
	}

	introText.setFont(font);
	introText.setString("Welcome to minesweeper! Press enter to play :]");
	introText.setCharacterSize(36);
	introText.setPosition((GC::SCREEN_RES.x / 2.0f) - introText.getGlobalBounds().width / 2.0f, (GC::SCREEN_RES.y / 2.0f) - introText.getGlobalBounds().height);

	if (!bgTexture.loadFromFile("data/bg.jpg")) {
		assert(false);
	}

	bg.setTexture(bgTexture);
	bg.setPosition(GC::SCREEN_RES.x / 2 - bg.getGlobalBounds().width / 2, GC::SCREEN_RES.y / 2 - bg.getGlobalBounds().height / 2);
		
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "Welcome to Minesweeper");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ENTER_KEY) {
					window.close();
					gMode = gameMode::GAME;
				}
			}

		}

		if (gMode == gameMode::GAME) {
			drawGame(gMode);
		}

		window.draw(bg);
		window.draw(introText);		
		window.display();
		window.clear();
	}
}





int main()
{	
	srand(time(NULL));
	
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "GAME");

	gameMode gMode = gameMode::INTRO;

	switch (gMode) {
	case gameMode::INTRO:
		window.close();
		drawIntro(gMode);
		break;
	case gameMode::GAME:
		window.close();
		drawGame(gMode);
		break;
	case gameMode::DEAD:
		window.close();
		gameOver(gMode);
		break;
	}
	
	
	while (window.isOpen())
	{								
		Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed) 
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close();			
			}
			
		} 
	}

	return EXIT_SUCCESS;
}
