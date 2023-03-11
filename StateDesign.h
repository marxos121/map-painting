#pragma once
#include "BaseState.h"
#include <SFML/System/Vector2.hpp>
#include <unordered_set>

class StateDesign :
    public BaseState
{
public:
	StateDesign();
	~StateDesign() = default;

	void handleInput();
	void update();
	void render();

private:
	void initialise();
	void save();
	void clear();

	sf::Vector2i m_playerStart;
	std::unordered_set<int> m_playerBlocks;
	sf::Vector2i m_mapSize;

	Shared* m_shared;
};

