#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

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
	Shared shared;
	StateManager m_stateMgr;
};

