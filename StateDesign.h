#pragma once
#include "BaseState.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_set>

class StateDesign :
    public BaseState
{
public:
	StateDesign(Shared* shared);
	~StateDesign() = default;

	void handleInput();
	void update();
	void render();

private:
	void initialise();
	void save();
	void clear();

	sf::Vector2i m_playerStart;
	std::unordered_set<sf::Vector2i> m_playerBlocks;
	sf::Vector2i m_mapSize;

	sf::Sprite m_playerSprite;
	sf::Sprite m_unpaintedSprite;
	sf::Sprite m_wallSprite;

	sf::Sprite m_arrows[4];

	Shared* m_shared;
};

