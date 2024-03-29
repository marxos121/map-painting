#include "GameFinished.h"
#include "Shared.h"
#include "Window.h"
#include "Map.h"
#include "StatePlay.h"
#include "StateManager.h"

#include <SFML/Window/Keyboard.hpp>
#include <fstream>

GameFinished::GameFinished(Shared* shared)
	: BaseState(StateType::GameComplete, shared), m_playAgain(false)
{
	m_font.loadFromFile("./Graphics/KOMIKAP.ttf");

	m_text.setFont(m_font);
	m_text.setCharacterSize(32);
	m_text.setString("Congratulations! You beat the game!\nPress R to play again or ESC to exit.");
	m_text.setOrigin(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2,
		m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2);

	auto position = m_shared->m_window->mapPixelToCoords(sf::Vector2i(m_shared->m_window->getSize().x / 2,
		m_shared->m_window->getSize().y / 2));
	m_text.setPosition(position);

	m_shared->m_gameMap->m_nextMap = "map1.txt";
	std::ofstream os("state.txt");
	os << "map1.txt";
	os.close();
}

void GameFinished::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_playAgain = true;
	}
}

void GameFinished::update()
{ 
	if (m_playAgain)
	{
		m_shared->m_gameMap->loadNext();
		m_shared->m_stateMgr->swapState(StateType::Play);
		auto play = dynamic_cast<StatePlay*>(m_shared->m_stateMgr->m_states.back());
		play->resetPlayer();
		play->resetTimer();
	}
}

void GameFinished::render()
{
	m_shared->m_window->draw(m_text);
}

void GameFinished::activate()
{
	BaseState::activate();
	m_playAgain = false;
}
