#include "StateMainMenu.h"

#include "Window.h"
#include "StateManager.h"

#include <SFML/Window/Event.hpp>

StateMainMenu::StateMainMenu(Shared* shared)
	: BaseState(StateType::MainMenu, shared)
{
	m_font.loadFromFile("./Graphics/KOMIKAP.ttf");
	m_startGameText.setFont(m_font);
	m_designText.setFont(m_font);
	m_exitText.setFont(m_font);

	m_startGameText.setString("Start Game");
	m_designText.setString("Design Level");
	m_exitText.setString("Exit");

	m_startGameText.setCharacterSize(15); 
	m_designText.setCharacterSize(15);
	m_exitText.setCharacterSize(15);

	auto windowSize = m_shared->m_window->getRenderWindow()->getSize();
	auto startBounds = m_startGameText.getLocalBounds();
	m_startGameText.setOrigin(startBounds.left + startBounds.width / 2, startBounds.top + startBounds.height / 2);
	m_startGameText.setPosition(windowSize.x / 2, windowSize.y / 2 - startBounds.height);

	auto designBounds = m_designText.getLocalBounds();
	m_designText.setOrigin(designBounds.left + designBounds.width / 2, designBounds.top + designBounds.height / 2);
	m_designText.setPosition(windowSize.x / 2, windowSize.y / 2 + startBounds.height);

	auto exitBounds = m_exitText.getLocalBounds();
	m_exitText.setOrigin(exitBounds.left + exitBounds.width / 2, exitBounds.top + exitBounds.height / 2);
	m_exitText.setPosition(windowSize.x / 2, windowSize.y / 2 + 3 * startBounds.height);

	float padding = 2.f;

	for (auto& rect : m_rectangles)
	{
		rect.setFillColor(sf::Color::Magenta);
		rect.setSize({ designBounds.width + padding * 10, startBounds.height + padding });
		rect.setOrigin(rect.getLocalBounds().left + rect.getLocalBounds().width / 2,
			rect.getLocalBounds().top + rect.getLocalBounds().height / 2);
	}

	m_rectangles[0].setPosition(m_startGameText.getPosition());
	m_rectangles[1].setPosition(m_designText.getPosition());
	m_rectangles[2].setPosition(m_exitText.getPosition());
}

void StateMainMenu::handleInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		auto pos = sf::Mouse::getPosition(*m_shared->m_window->getRenderWindow());
		pos = sf::Vector2i(m_shared->m_window->getRenderWindow()->mapPixelToCoords(pos));

		if (pos.x > m_rectangles[0].getGlobalBounds().left
			&& pos.x < m_rectangles[0].getGlobalBounds().left + m_rectangles[0].getGlobalBounds().width
			&& pos.y > m_rectangles[0].getGlobalBounds().top
			&& pos.y < m_rectangles[0].getGlobalBounds().top + m_rectangles[0].getGlobalBounds().height)
		{
			m_shared->m_stateMgr->swapState(StateType::Play);
		}
		else if (pos.x > m_rectangles[1].getGlobalBounds().left
			&& pos.x < m_rectangles[1].getGlobalBounds().left + m_rectangles[1].getGlobalBounds().width
			&& pos.y > m_rectangles[1].getGlobalBounds().top
			&& pos.y < m_rectangles[1].getGlobalBounds().top + m_rectangles[1].getGlobalBounds().height)
		{
			m_shared->m_stateMgr->swapState(StateType::Design);
		}
		else if (pos.x > m_rectangles[2].getGlobalBounds().left
			&& pos.x < m_rectangles[2].getGlobalBounds().left + m_rectangles[2].getGlobalBounds().width
			&& pos.y > m_rectangles[2].getGlobalBounds().top
			&& pos.y < m_rectangles[2].getGlobalBounds().top + m_rectangles[2].getGlobalBounds().height)
		{
			m_shared->m_window->destroy();
		}
	}
}

void StateMainMenu::render()
{
	m_shared->m_window->getRenderWindow()->draw(m_rectangles[0]);
	m_shared->m_window->getRenderWindow()->draw(m_rectangles[1]);
	m_shared->m_window->getRenderWindow()->draw(m_rectangles[2]);
	m_shared->m_window->getRenderWindow()->draw(m_startGameText);
	m_shared->m_window->getRenderWindow()->draw(m_designText);
	m_shared->m_window->getRenderWindow()->draw(m_exitText);
}

void StateMainMenu::activate()
{
	BaseState::activate();
	if (m_shared->m_stateMgr->hasState(StateType::Play)) {
		m_startGameText.setString("Resume");
		m_startGameText.setOrigin(m_startGameText.getLocalBounds().width / 2, m_startGameText.getLocalBounds().height / 2);
		m_startGameText.setPosition(m_shared->m_window->getRenderWindow()->getSize().x / 2,
			m_shared->m_window->getRenderWindow()->getSize().y / 2 - m_startGameText.getLocalBounds().height - 2.f);
	}
}
