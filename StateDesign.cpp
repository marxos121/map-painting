#include "StateDesign.h"

#include "Shared.h"
#include "TextureManager.h"
#include "Window.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <fstream>
#include <iostream>

StateDesign::StateDesign(Shared* shared)
	: BaseState(StateType::Design, shared), m_mapSize({ 1, 1})
{
	m_playerSprite.setTexture(*m_shared->m_texMgr->getTexture("blocksheet"));
	m_playerSprite.setTextureRect({0, 0,
		(int)m_playerSprite.getTexture()->getSize().y,
		(int)m_playerSprite.getTexture()->getSize().y});

	m_wallSprite.setTexture(*m_shared->m_texMgr->getTexture("wall70px"));	
	m_unpaintedSprite.setTexture(*m_shared->m_texMgr->getTexture("san70px"));

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

	
}

void StateDesign::handleInput()
{
}

void StateDesign::update()
{
}

void StateDesign::render()
{
	static const float spriteSize = 50.f;
	static const float padding = 2.f;


	float startX = m_shared->m_window->getRenderWindow()->getDefaultView().getCenter().x -
		m_mapSize.x * (spriteSize + padding) / 2;
	float startY = m_shared->m_window->getRenderWindow()->getDefaultView().getCenter().y -
		m_mapSize.y * (spriteSize + padding) / 2;


	sf::RectangleShape sprite({ spriteSize, spriteSize });
	sprite.setPosition(startX, startY);

	for (int i = 0; i != m_mapSize.x; ++i)
	{
		for (int j = 0; j != m_mapSize.y; ++j)
		{
			//auto it = m_playerBlocks.find({ i, j });
			//if (it != m_playerBlocks.end()) {
			//	sprite.setTexture(m_shared->m_texMgr->getTexture("blocksheet"));
			//	sprite.setTextureRect({ 0, 0,
			//		(int)sprite.getTexture()->getSize().y,
			//		(int)sprite.getTexture()->getSize().y });
			//}
			//else {
				sprite.setTexture(m_shared->m_texMgr->getTexture("san70px"));
			//}

			m_shared->m_window->getRenderWindow()->draw(sprite);
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
	std::ofstream os("./Maps/newmap.txt");

	os << "--MAPFILE--\nNEXT: NULL\nSIZE: "
		<< m_mapSize.x << " " << m_mapSize.y
		<< "\nSTART: " << m_playerStart.x << " " << m_playerStart.y << std::endl;

	for (int i = 0; i != m_mapSize.x; ++i) 
	{
		for (int j = 0; j != m_mapSize.y; ++j)
		{
			//auto it = m_playerBlocks.find({ i, j });
			//if (it == m_playerBlocks.end()) {
			//	os << "TILE: " << i << " " << j << std::endl;
			//}
		}
	}

	os.close();
}

void StateDesign::clear()
{
	m_playerStart = { -1, -1 };
	//m_playerBlocks.clear();
}
