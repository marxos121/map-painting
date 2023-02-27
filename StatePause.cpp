#include "StatePause.h"
#include "Window.h"
#include "StateManager.h"

#include <SFML/Window/Keyboard.hpp>

StatePause::StatePause(Shared* shared)
	:	BaseState(StateType::Pause, shared, false, true)
{
	font.loadFromFile("./Graphics/KOMIKAP.ttf");
	text.setFont(font);
	text.setCharacterSize(32);
	text.setString("Game Paused.\nPress P to continue.");
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2,
		text.getLocalBounds().top + text.getLocalBounds().height / 2);
	text.setPosition(m_shared->m_window->getRenderWindow()->getSize().x / 2,
		m_shared->m_window->getRenderWindow()->getSize().y / 2);

	m_fill.setFillColor(sf::Color(0, 0, 0, 150));
	m_fill.setSize(sf::Vector2f(shared->m_window->getRenderWindow()->getSize().x,
		shared->m_window->getRenderWindow()->getSize().y));
}

void StatePause::handleInput()
{
}

void StatePause::update()
{
}

void StatePause::render()
{
	m_shared->m_window->getRenderWindow()->draw(m_fill);
	m_shared->m_window->getRenderWindow()->draw(text);
}
