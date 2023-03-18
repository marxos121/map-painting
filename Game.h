#pragma once

#include "Shared.h"

class Game
{
public:
	Game();
	~Game();

	void play();

	void handleInput();
	void update();
	void render();

private:
	sf::Sprite m_backgroundImage;
	Shared m_shared;

	void onResize();
};

