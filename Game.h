#pragma once

#include "Shared.h"

#include <SFML/Graphics/Sprite.hpp>

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

