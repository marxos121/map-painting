#include "HUD.h"

#include "Shared.h"
#include "Window.h"


HUD::HUD(Shared* shared)
	: m_shared(shared)
{
	
	m_font.loadFromFile("./Graphics/KOMIKAP.ttf");

	m_time.setFont(m_font);

	m_blocks.setFont(m_font);
	m_blocks.setPosition(30, 20);
}


void HUD::initialise(int blocks)
{
	m_blocksToPaint = blocks;
	m_blocks.setString("1/" + std::to_string(m_blocksToPaint));

	m_time.setString("0s");
	onResize();
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

void HUD::onResize()
{
	if (m_shared->m_window->getRenderWindow()->getSize().x >= 600) {
		m_time.setCharacterSize(32);
		m_blocks.setCharacterSize(32);
	}
	else {
		m_time.setCharacterSize(20);
		m_blocks.setCharacterSize(20);
	}
	m_time.setOrigin(m_time.getLocalBounds().width, 0);
	m_time.setPosition(m_shared->m_window->getRenderWindow()->getSize().x - 30, 20);
}
