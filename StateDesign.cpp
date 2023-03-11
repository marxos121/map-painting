#include "StateDesign.h"

#include "Shared.h"
#include "TextureManager.h"
#include "Window.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <fstream>

StateDesign::StateDesign(Shared* shared)
	: BaseState(StateType::Design, shared), m_mapSize({ 1, 1})
{
	m_playerSprite.setTexture(*m_shared->m_texMgr->getTexture("blocksheet"));
	m_playerSprite.setTextureRect({0.f, 0.f,
		m_playerSprite.getTexture()->getSize().y,
		m_playerSprite.getTexture()->getSize().y});

	m_wallSprite.setTexture(*m_shared->m_texMgr->getTexture("wall70px"));	
	m_unpaintedSprite.setTexture(*m_shared->m_texMgr->getTexture("san70px"));
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
	sprite.setPosition(padding, padding);

	for (int i = 0; i != m_mapSize.x; ++i)
	{
		for (int j = 0; j != m_mapSize.y; ++j)
		{
			auto it = m_playerBlocks.find({ i, j });
			if (it != m_playerBlocks.end()) {
				sprite.setTexture(m_shared->m_texMgr->getTexture("blocksheet"));
				sprite.setTextureRect({ 0.f, 0.f,
					sprite.getTexture()->getSize().y,
					sprite.getTexture()->getSize().y });
			}
			else {
				sprite.setTexture(m_shared->m_texMgr->getTexture("san70px"));
			}

			m_shared->m_window->getRenderWindow()->draw(sprite);
		}
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
			auto it = m_playerBlocks.find({ i, j });
			if (it == m_playerBlocks.end()) {
				os << "TILE: " << i << " " << j << std::endl;
			}
		}
	}

	os.close();
}

void StateDesign::clear()
{
	m_playerStart = { -1, -1 };
	m_playerBlocks.clear();
}
