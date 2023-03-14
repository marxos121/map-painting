#pragma once
#include "BaseState.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <unordered_set>
#include <unordered_map>
#include <string>

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
	void save();
	void clear();

	sf::Vector2i m_playerStart;
	//std::unordered_set<std::pair<int, int>> m_playerBlocks;
	sf::Vector2i m_mapSize;

	sf::Sprite m_playerSprite;
	sf::Sprite m_unpaintedSprite;
	sf::Sprite m_wallSprite;

	sf::Font m_font;
	std::unordered_map<std::string, sf::Text> m_texts;
	std::unordered_map<std::string, sf::RectangleShape> m_fills;

	//sf::RectangleShape m_saveBackground;
	//sf::RectangleShape m_clearBackground;
};

