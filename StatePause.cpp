#include "StatePause.h"
#include "Window.h"
#include "StateManager.h"

#include <SFML/Window/Keyboard.hpp>

StatePause::StatePause(Shared* shared)
	:	BaseState(StateType::Pause, shared, false, true)
{
	font.loadFromFile("./Graphics/KOMIKAP.ttf");
	text.setFont(font);
	text.setString("Game Paused.\nPress P to continue.");
	onResize();

	m_fill.setFillColor(sf::Color(0, 0, 0, 150));
}

void StatePause::handleInput()
{
}

void StatePause::update()
{
}

void StatePause::render()
{
	m_shared->m_window->draw(m_fill);
	m_shared->m_window->draw(text);
}

void StatePause::onResize()
{
	m_fill.setSize(sf::Vector2f(m_shared->m_window->getSize().x,
		m_shared->m_window->getSize().y));
	if (m_shared->m_window->getSize().x >= 600)
		text.setCharacterSize(32);
	else
		text.setCharacterSize(20);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2,
		text.getLocalBounds().top + text.getLocalBounds().height / 2);
	auto position = m_shared->m_window->getView().getCenter();
	text.setPosition(position);
}
