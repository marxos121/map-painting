#pragma once

#include "Shared.h"
#include "StateManager.h"

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
};

