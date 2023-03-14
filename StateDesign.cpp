#include "StateDesign.h"

#include "Shared.h"
#include "TextureManager.h"
#include "Window.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <fstream>
#include <iostream>

StateDesign::StateDesign(Shared* shared)
	: BaseState(StateType::Design, shared), m_mapSize({ 1, 1})
{
	//m_playerSprite.setTextureRect({0, 0,
		//(int)m_playerSprite.getTexture()->getSize().y,
		//(int)m_playerSprite.getTexture()->getSize().y});

	m_tiles.push_back(std::vector<sf::Sprite>(1, sf::Sprite(
		*m_shared->m_texMgr->getTexture("san70px"))));
	m_tiles[0][0].setPosition(m_shared->m_window->getRenderWindow()->getSize().x / 2
		- m_tiles[0][0].getGlobalBounds().width / 2,
		m_shared->m_window->getRenderWindow()->getSize().y / 2
		- m_tiles[0][0].getGlobalBounds().height / 2);

	m_font.loadFromFile("./Graphics/KOMIKAP.TTF");
	m_texts["clear"].setString("Clear");
	m_texts["save"].setString("Save");
	m_texts["width"].setString("Width:");
	m_texts["height"].setString("Height:");
	m_texts["width+"].setString("+");
	m_texts["width-"].setString("-");

	m_texts["height+"] = m_texts["width+"];
	m_texts["height-"] = m_texts["width-"];

	for (auto& text : m_texts) {
		text.second.setFont(m_font);
		text.second.setCharacterSize(32);
		text.second.setFillColor(sf::Color::White);
		auto rect = text.second.getLocalBounds();
		text.second.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	}

	m_texts["width"].setPosition(70.f, 40.f);
	m_texts["width-"].setPosition(50.f, 70.f);
	m_texts["width+"].setPosition(90.f, 70.f);

	m_texts["height"].setPosition(70.f, 120.f);
	m_texts["height-"].setPosition(50.f, 150.f);
	m_texts["height+"].setPosition(90.f, 150.f);


	m_texts["save"].setPosition(70.f, 200.f);
	m_texts["clear"].setPosition(70.f, 250.f);

	


	m_fills["settings"].setPosition(m_texts["height"].getGlobalBounds().left - 5,
		m_texts["width"].getGlobalBounds().top - 10);
	m_fills["settings"].setSize(sf::Vector2f(m_texts["height"].getGlobalBounds().width + 10, 
		m_texts["height+"].getGlobalBounds().top + 2*m_texts["height+"].getGlobalBounds().height - m_texts["width"].getGlobalBounds().top));

	m_fills["save"].setPosition(m_texts["height"].getGlobalBounds().left - 5, m_texts["save"].getGlobalBounds().top - 5);
	m_fills["save"].setSize(sf::Vector2f(m_texts["height"].getGlobalBounds().width + 10, m_texts["save"].getGlobalBounds().height + 10));


	m_fills["clear"].setPosition(m_texts["height"].getGlobalBounds().left - 5, m_texts["clear"].getGlobalBounds().top - 5);
	m_fills["clear"].setSize(sf::Vector2f(m_texts["height"].getGlobalBounds().width + 10, m_texts["clear"].getGlobalBounds().height + 10));
	for (auto& fill : m_fills) {
		fill.second.setFillColor(sf::Color(0, 0, 0, 150));
	}

	m_isActive = true;
}

void StateDesign::handleInput()
{
	static bool released = true;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		released = true;
		return;
	}

	if (!released) {
		return;
	}

	released = false;

	auto pos = sf::Mouse::getPosition(*m_shared->m_window->getRenderWindow());
	pos = sf::Vector2i(m_shared->m_window->getRenderWindow()->mapPixelToCoords(pos));

	for (auto& text : m_texts) {
		if (!(pos.x > text.second.getGlobalBounds().left
			&& pos.x < text.second.getGlobalBounds().left + text.second.getGlobalBounds().width
			&& pos.y > text.second.getGlobalBounds().top
			&& pos.y < text.second.getGlobalBounds().top + text.second.getGlobalBounds().height))
		{
			continue;
		}

		if (text.first == "clear") {
			clear();
			return;
		}
	    if (text.first == "save") {
			save();
			return;
		}
		if (text.first == "width+") {
			m_mapSize.x++;
			if (m_mapSize.x > 10)
				m_mapSize.x = 10;
			m_updateTiles = true;
			return;
		}
		if (text.first == "width-") {
			m_mapSize.x--;
			if (m_mapSize.x < 1)
				m_mapSize.x = 1;
			m_updateTiles = true;
			return;
		}
		if (text.first == "height+") {
			m_mapSize.y++;
			if (m_mapSize.y > 10)
				m_mapSize.y = 10;
			m_updateTiles = true;
			return;
		}
		if (text.first == "height-") {
			m_mapSize.y--;
			if(m_mapSize.y < 1)
				m_mapSize.y = 1;
			m_updateTiles = true;
			return;
		}
	}

	for (int y = 0; y != m_tiles.size(); ++y) {
		for (int x = 0; x != m_tiles[y].size(); ++x) {
			auto bounds = m_tiles[y][x].getGlobalBounds();
			if (pos.x > bounds.left && pos.x < bounds.left + bounds.width
				&& pos.y > bounds.top && pos.y < bounds.top + bounds.height)
			{
				if (m_player.empty() || 
					(!m_player.empty() && (abs(x - m_player.back().x) + abs(y - m_player.back().y) == 1)
						&& std::find(m_player.cbegin(), m_player.cend(), sf::Vector2i({ x, y })) == m_player.cend()))
				{
					m_player.push_back(sf::Vector2i(x, y));
					m_tiles[y][x].setTexture(*m_shared->m_texMgr->getTexture("blocksheet"));
					m_tiles[y][x].setTextureRect({ 0, 0, 50, 50 });
					y = m_tiles.size() - 1;
					break;
				}
			}
		}
	}
}

void StateDesign::update()
{
	if (!m_updateTiles) {
		return;
	}

	if (m_mapSize.y > m_tiles.size()) {
		m_tiles.push_back(std::vector<sf::Sprite>
			(m_tiles.back().size(),
				sf::Sprite(*m_shared->m_texMgr->getTexture("san70px"))));
	}
	else if (m_mapSize.y < m_tiles.size()) {
		m_tiles.pop_back();
	}

	if(m_mapSize.x > m_tiles.back().size()) {
		for (auto& row : m_tiles) {
			row.push_back(sf::Sprite(*m_shared->m_texMgr->getTexture("san70px")));
		}
	}
	else if (m_mapSize.x < m_tiles.back().size()) {
		for (auto& row : m_tiles) {
			row.pop_back();
		}
	}

	//Set new positions
	static const float spriteSize = 50.f;
	static const float padding = 2.f;

	float startX = m_shared->m_window->getRenderWindow()->getDefaultView().getCenter().x -
		m_mapSize.x * (spriteSize + padding) / 2;
	float posY = m_shared->m_window->getRenderWindow()->getDefaultView().getCenter().y -
		m_mapSize.y * (spriteSize + padding) / 2;
	float posX = startX;

	for (int y = 0; y != m_tiles.size(); ++y) {
		for (int x = 0; x != m_tiles[y].size(); ++x) {
			m_tiles[y][x].setPosition(posX, posY);
			posX += spriteSize + padding;
		}
		posY += spriteSize + padding;
		posX = startX;
	}

	m_updateTiles = false;
}

void StateDesign::render()
{
	for (int y = 0; y != m_tiles.size(); ++y) {
		for (int x = 0; x != m_tiles[y].size(); ++x) {
			m_shared->m_window->getRenderWindow()->draw(m_tiles[y][x]);
		}
	}

	for (auto& fill : m_fills) {
		m_shared->m_window->getRenderWindow()->draw(fill.second);
	}

	for (auto& text : m_texts) {
		m_shared->m_window->getRenderWindow()->draw(text.second);
	}
}

void StateDesign::save()
{
	if (m_player.empty()) {
		return;
	}

	std::ofstream os("./Maps/newmap.txt");

	os << "--MAPFILE--\nNEXT: NULL\nSIZE: "
		<< m_mapSize.x << " " << m_mapSize.y
		<< "\nSTART: " << m_player.front().x << " " << m_player.front().y << std::endl;
	int added = 0;
	for (int x = 0; x != m_mapSize.x; ++x) 
	{
		for (int y = 0; y != m_mapSize.y; ++y)
		{
			bool isPath = std::find(m_player.cbegin(), m_player.cend(), sf::Vector2i(x, y)) != m_player.cend();

			if (isPath) {
				break;
			}
			os << "TILE: " << x << " " << y << std::endl;
		}
	}

	os.close();
}

void StateDesign::clear()
{
}
