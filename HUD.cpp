#include "HUD.h"

#include "Shared.h"
#include "Window.h"


HUD::HUD(Shared* shared)
	: m_shared(shared)
{
	
	m_font.loadFromFile("./Graphics/KOMIKAP.ttf");

	m_time.setFont(m_font);
	m_time.setCharacterSize(40);

	m_blocks.setFont(m_font);
}


void HUD::initialise(int blocks)
{
	m_blocksToPaint = blocks;
	m_blocks.setString("1/" + std::to_string(m_blocksToPaint));
	m_blocks.setCharacterSize(40);
	m_blocks.setPosition(100, 20);

	m_time.setString("0s");
	m_time.setOrigin(m_time.getLocalBounds().width, 0);
	m_time.setPosition(650, 20);
}

void HUD::update(float dT, int playerSize)
{
	m_time.setString(std::to_string(static_cast<int>(dT)) + "s");
	m_blocks.setString(std::to_string(playerSize) + '/' + std::to_string(m_blocksToPaint));
}

void HUD::draw()
{
	m_shared->m_window->getRenderWindow()->draw(m_time);
	m_shared->m_window->getRenderWindow()->draw(m_blocks);
	
}
