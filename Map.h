#pragma once
#include "GameFinished.h"

#include <string>
#include <unordered_set>

#include <SFML/System/Vector2.hpp>


class Map
{
	friend void GameFinished::update();
public:
	void loadMap();
	void purgeMap();
	bool loadNext();

	sf::Vector2i getMapSize() const;
	const std::unordered_set<int>& getTiles() const;
	sf::Vector2i getPlayerStartingPosition() const;
	int getTilesToPaint() const;

private:
	sf::Vector2i m_mapSize;
	std::unordered_set<int> m_tiles;	//positions of solid tiles
	int m_tilesToPaint = 0;

	sf::Vector2i m_playerStartingPosition;


	std::string m_nextMap = "map1.txt";
};

