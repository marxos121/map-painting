#include "StateMainMenu.h"

#include "Window.h"
#include "StateManager.h"

#include <SFML/Window/Event.hpp>

StateMainMenu::StateMainMenu(Shared* shared)
	: BaseState(StateType::MainMenu, shared)
{
	m_font.loadFromFile("./Graphics/KOMIKAP.ttf");
	m_startGameText.setFont(m_font);
	m_exitText.setFont(m_font);

	m_startGameText.setString("Start Game");
	m_exitText.setString("Exit");

	m_startGameText.setCharacterSize(15);
	m_exitText.setCharacterSize(15);

	auto windowSize = m_shared->m_window->getRenderWindow()->getSize();
	auto startBounds = m_startGameText.getLocalBounds();
	m_startGameText.setOrigin(startBounds.left + startBounds.width / 2, startBounds.top + startBounds.height / 2);
	m_startGameText.setPosition(windowSize.x / 2, windowSize.y / 2 - startBounds.height);

	auto exitBounds = m_exitText.getLocalBounds();
	m_exitText.setOrigin(exitBounds.left + exitBounds.width / 2, exitBounds.top + exitBounds.height / 2);
	m_exitText.setPosition(windowSize.x / 2, windowSize.y / 2 + startBounds.height);

	float padding = 2.f;

	for (auto& rect : m_rectangles)
	{
		rect.setFillColor(sf::Color::Magenta);
		rect.setSize({ startBounds.width + padding, startBounds.height + padding });
		rect.setOrigin(rect.getLocalBounds().left + rect.getLocalBounds().width / 2,
			rect.getLocalBounds().top + rect.getLocalBounds().height / 2);
	}

	m_rectangles[0].setPosition(m_startGameText.getPosition());
	m_rectangles[1].setPosition(m_exitText.getPosition());
}

void StateMainMenu::handleInput()
{
	/*
	sf::Event event;
	while (m_shared->m_window->getRenderWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			auto pos = event.mouseButton;

			if (pos.x > m_rectangles[0].getPosition().x - m_rectangles[0].getSize().x / 2
				&& pos.x < m_rectangles[0].getPosition().x + m_rectangles[0].getSize().x / 2
				&& pos.y > m_rectangles[0].getPosition().y - m_rectangles[0].getSize().y / 2
				&& pos.y > m_rectangles[0].getPosition().y + m_rectangles[0].getSize().y / 2)
			{
				m_shared->m_stateMgr->swapState(StateType::Play);
			}
			else if (pos.x > m_rectangles[1].getPosition().x - m_rectangles[1].getSize().x / 2
				&& pos.x < m_rectangles[1].getPosition().x + m_rectangles[1].getSize().x / 2
				&& pos.y > m_rectangles[1].getPosition().y - m_rectangles[1].getSize().y / 2
				&& pos.y > m_rectangles[1].getPosition().y + m_rectangles[1].getSize().y / 2)
			{
				m_shared->m_window->destroy();
			}
		}
	}*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		auto pos = sf::Mouse::getPosition(*m_shared->m_window->getRenderWindow());
		sf::FloatRect mouseBounds = { float(pos.x), float(pos.y), 1.f, 1.f };
		if (mouseBounds.intersects(m_rectangles[0].getGlobalBounds()))
		{
			m_shared->m_stateMgr->swapState(StateType::Play);
		}
		else if (mouseBounds.intersects(m_rectangles[1].getGlobalBounds()))
		{
			m_shared->m_window->destroy();
		}
		/*
		if (pos.x > m_rectangles[0].getPosition().x - m_rectangles[0].getSize().x / 2
			&& pos.x < m_rectangles[0].getPosition().x + m_rectangles[0].getSize().x / 2
			&& pos.y > m_rectangles[0].getPosition().y - m_rectangles[0].getSize().y / 2
			&& pos.y > m_rectangles[0].getPosition().y + m_rectangles[0].getSize().y / 2)
		{
			m_shared->m_stateMgr->swapState(StateType::Play);
		}
		else if (pos.x > m_rectangles[1].getPosition().x - m_rectangles[1].getSize().x / 2
			&& pos.x < m_rectangles[1].getPosition().x + m_rectangles[1].getSize().x / 2
			&& pos.y > m_rectangles[1].getPosition().y - m_rectangles[1].getSize().y / 2
			&& pos.y > m_rectangles[1].getPosition().y + m_rectangles[1].getSize().y / 2)
		{
			m_shared->m_window->destroy();
		}*/
	}
}

void StateMainMenu::render()
{
	m_shared->m_window->getRenderWindow()->draw(m_rectangles[0]);
	m_shared->m_window->getRenderWindow()->draw(m_rectangles[1]);
	m_shared->m_window->getRenderWindow()->draw(m_startGameText);
	m_shared->m_window->getRenderWindow()->draw(m_exitText);
}
