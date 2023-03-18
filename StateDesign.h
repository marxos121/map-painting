#pragma once
#include "BaseState.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>
#include <string>

struct Button
{
	sf::RectangleShape background; 
	sf::Text text;
};

class StateDesign :
	public BaseState
{
public:
	StateDesign(Shared* shared);
	~StateDesign() = default;

	void handleInput();
	void update();
	void render();
	void onResize();

private:
	void save();
	void clear();

	sf::Vector2i m_mapSize;
	std::vector<std::vector<sf::Sprite>> m_tiles;	//all tiles
	std::vector<sf::Vector2i> m_player;

	sf::Font m_font;
	std::unordered_map<std::string,  Button> m_buttons;
	sf::RectangleShape m_sizingBackground;


	bool m_updateTiles = false;
};

