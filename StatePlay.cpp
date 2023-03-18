#include "StatePlay.h"
#include "Map.h"
#include "Window.h"
#include "TextureManager.h"
#include "StateManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameFinished;

void StatePlay::resetPlayer()
{
	m_player.clear();
	m_player.push_back(m_gameMap->getPlayerStartingPosition());
	m_reset = false;
	m_nextStep = (Step)-1;

	m_hud.initialise(m_gameMap->getTilesToPaint());
}

void StatePlay::updateTime()
{
	auto val = m_clock.restart();
	m_elapsedTotal += val;
	m_elapsed += val;
}

void StatePlay::restartClock()
{
	m_clock.restart();
}

void StatePlay::resetTimer()
{
	m_elapsedTotal = sf::seconds(0);
}

StatePlay::~StatePlay()
{
	delete m_gameMap;
	m_gameMap = nullptr;
}

StatePlay::StatePlay(Shared* shared)
	: BaseState(StateType::Play, shared), m_hud(shared), m_nextStep((Step)-1),
	m_playerSheet(m_shared, "blocksheet", { 100.f, 100.f })
{
	m_gameMap = new Map;
	m_gameMap->loadMap();
	m_shared->m_gameMap = m_gameMap;

	resetPlayer();

}

void StatePlay::handleInput()
{

	static float timestep = .3f;
	if (m_elapsed.asSeconds() < timestep || m_player.size() == m_gameMap->getTilesToPaint())
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_reset = true;
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_nextStep = Step::Up;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_nextStep = Step::Down;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_nextStep = Step::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_nextStep = Step::Right;
	}


}

void StatePlay::update()
{
	if (m_reset)
	{
		resetPlayer();
	}	

	float timeDelta = m_elapsedTotal.asSeconds();
	updateTime();
	float secs = m_elapsedTotal.asSeconds();
	m_hud.update(secs, m_player.size());


	switch (m_nextStep)
	{
	case (Step)-1:
	{
		if(m_player.size() == m_gameMap->getTilesToPaint())
		{
			break;
		}
		else
		{
			return;
		}
	}

	case Step::Up:
	{
		//Try to paint up
		if (m_player.back().y == 0 ||
			m_gameMap->getTiles().find(m_player.back().x + (m_player.back().y - 1) * m_gameMap->getMapSize().x) != m_gameMap->getTiles().end())
			break;

		auto it = std::find_if(m_player.begin(), m_player.end(),
			[this](const sf::Vector2i& l_pos) { return l_pos == sf::Vector2i(m_player.back().x, m_player.back().y - 1); });

		if (it != m_player.end())
		{
			if (m_player.size() > 1 && *it == *(m_player.end() - 2))
			{
				m_player.pop_back();
				break;
			}

			break;
		}

		m_player.push_back({ m_player.back().x, m_player.back().y - 1 });
		break;
	}

	case Step::Down:
	{
		//Try to paint down
		if (m_player.back().y == m_gameMap->getMapSize().y - 1 ||
			m_gameMap->getTiles().find(m_player.back().x + (m_player.back().y + 1) * m_gameMap->getMapSize().x) != m_gameMap->getTiles().end())
			break;

		auto it = std::find_if(m_player.begin(), m_player.end(),
			[this](const sf::Vector2i& l_pos) { return l_pos == sf::Vector2i(m_player.back().x, m_player.back().y + 1); });

		if (it != m_player.end())
		{
			if (m_player.size() > 1 && *it == *(m_player.end() - 2))
			{
				m_player.pop_back();
				break;
			}

			break;
		}

		m_player.push_back({ m_player.back().x, m_player.back().y + 1 });
		break;
	}
	case Step::Left:
	{
		//Try to paint left		
		if (m_player.back().x == 0 ||
			m_gameMap->getTiles().find(m_player.back().x - 1 + m_player.back().y * m_gameMap->getMapSize().x) != m_gameMap->getTiles().end())
			break;

		auto it = std::find_if(m_player.begin(), m_player.end(),
			[this](const sf::Vector2i& l_pos) { return l_pos == sf::Vector2i(m_player.back().x - 1, m_player.back().y); });

		if (it != m_player.end())
		{
			if (m_player.size() > 1 && *it == *(m_player.end() - 2))
			{
				m_player.pop_back();
				break;
			}

			break;
		}

		m_player.push_back({ m_player.back().x - 1, m_player.back().y });
		break;
	}

	case Step::Right:
	{
		//Try to paint right
		if (m_player.back().x == m_gameMap->getMapSize().x - 1 ||
			m_gameMap->getTiles().find(m_player.back().x + 1 + m_player.back().y * m_gameMap->getMapSize().x) != m_gameMap->getTiles().end())
			break;

		auto it = std::find_if(m_player.begin(), m_player.end(),
			[this](const sf::Vector2i& l_pos) { return l_pos == sf::Vector2i(m_player.back().x + 1, m_player.back().y); });

		if (it != m_player.end())
		{
			if (m_player.size() > 1 && *it == *(m_player.end() - 2))
			{
				m_player.pop_back();
				break;
			}

			break;
		}

		m_player.push_back({ m_player.back().x + 1, m_player.back().y });
		break;
	}
	}

	m_nextStep = (Step)-1;

	if (m_player.size() == m_gameMap->getTilesToPaint())
	{
		m_playerSheet.setPlay(true);
		m_playerSheet.setLooping(false);

		if (m_elapsed.asSeconds() < 2.f)
		{
			//will not work
			timeDelta -= secs;
			timeDelta *= -1;
			m_playerSheet.update(timeDelta);
			return;
		}

		bool bFinishedGame = !m_gameMap->loadNext();

		resetPlayer();
		restartClock();
		resetTimer();
		m_playerSheet.setPlay(false);
		m_playerSheet.setFrame(0);

		if (bFinishedGame)
		{
			m_shared->m_stateMgr->swapState(StateType::GameComplete);
			return;
		}
	}

	m_elapsed = sf::seconds(0);
}

void StatePlay::render()
{
	float spriteSize = m_shared->m_window->getScale().y * 100;
	static const float padding = 2.f;


	float startX = m_shared->m_window->getView().getCenter().x -
		m_gameMap->getMapSize().x * (spriteSize + padding) / 2;
	float startY = m_shared->m_window->getView().getCenter().y -
		m_gameMap->getMapSize().y * (spriteSize + padding) / 2;


	sf::RectangleShape sprite({ spriteSize, spriteSize });

	for (int x = 0; x != m_gameMap->getMapSize().x; ++x)
	{
		sprite.setPosition(startX + x * (spriteSize + padding) + padding, startY + padding);
		for (int y = 0; y != m_gameMap->getMapSize().y; ++y)
		{
			if (m_gameMap->getTiles().find(x + m_gameMap->getMapSize().x * y) != m_gameMap->getTiles().end())
			{
				sprite.setTexture(m_shared->m_texMgr->getTexture("wall"));
			}
			else
			{
				sprite.setTexture(m_shared->m_texMgr->getTexture("unpainted"));
			}

			m_shared->m_window->draw(sprite);
			sprite.move({ 0.f, spriteSize + padding });
		}
	}

	m_playerSheet.getSprite().setScale(m_shared->m_window->getScale().y, m_shared->m_window->getScale().y);
	for (int i = 0; i != m_player.size(); ++i)
	{
		m_playerSheet.setPosition({ startX + m_player[i].x * (spriteSize + padding) + padding, startY + m_player[i].y * (spriteSize + padding) + padding });
		m_playerSheet.draw(*m_shared->m_window);
	}

	m_hud.draw();
}

void StatePlay::activate()
{
	BaseState::activate();
	restartClock();
}

void StatePlay::onResize()
{
	m_hud.onResize();
}
