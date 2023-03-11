#include "StateDesign.h"

#include "Shared.h"
#include "TextureManager.h"

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
