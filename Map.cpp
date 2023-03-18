#include "Map.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map(const std::string& nextMap)
	: m_nextMap(nextMap), m_currentMap(nextMap)
{
	loadMap();
}

void Map::loadMap()
{
	std::ifstream mapfile("./Maps/" + m_nextMap);

	if (!mapfile.is_open())
	{
		std::cerr << "! Failed loading map: " + m_nextMap << std::endl;
		return;
	}

	bool bValid = false;

	std::string line;
	while (std::getline(mapfile, line))
	{
		if (!bValid)
		{
			if (line == "--MAPFILE--")
			{
				bValid = true;
				m_currentMap = m_nextMap;
				continue;
			}
			else
			{
				std::cerr << "! Invalid file: " + m_nextMap << std::endl;
				return;
			}
		}

		std::stringstream ss(line);
		std::string tag;
		ss >> tag;
		
		if (tag == "NEXT:")
		{
			ss >> m_nextMap;
		}
		else if (tag == "SIZE:")
		{
			ss >> m_mapSize.x >> m_mapSize.y;
		}
		else if (tag == "START:")
		{
			ss >> m_playerStartingPosition.x >> m_playerStartingPosition.y;
		}
		else if (tag == "TILE:")
		{
			int x, y;
			ss >> x >> y;
			m_tiles.insert(y * m_mapSize.x + x);
		}
	}

	m_tilesToPaint = m_mapSize.x * m_mapSize.y - m_tiles.size();
}

void Map::purgeMap()
{
	if (!m_tiles.empty())
	{
		m_tiles.clear();
	}
	m_playerStartingPosition = { -1, -1 };
}

bool Map::loadNext()
{
	purgeMap();
	if (m_nextMap != "NULL")
	{
		loadMap();
		return true;
	}

	return false;
}

std::string Map::getCurrentMap() const
{
	return m_currentMap;
}

sf::Vector2i Map::getMapSize() const
{
	return m_mapSize;
}

const std::unordered_set<int>& Map::getTiles() const
{
	return m_tiles;
}

sf::Vector2i Map::getPlayerStartingPosition() const
{
	return m_playerStartingPosition;
}

int Map::getTilesToPaint() const
{
	return m_tilesToPaint;
}