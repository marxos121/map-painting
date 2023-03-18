#include "Game.h"
#include "Window.h"
#include "Map.h"
#include "StateManager.h"
#include "TextureManager.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

Game::Game()
{
	m_shared.m_window = new GameWindow("Tiles", 1200, 900);
	m_shared.m_texMgr = new TextureManager;
	m_shared.m_stateMgr = new StateManager(&m_shared);

	m_shared.m_stateMgr->addState<StateMainMenu>();

	m_shared.m_window->getRenderWindow()->setKeyRepeatEnabled(false);
	m_shared.m_window->initShared(&m_shared);

	m_backgroundImage.setTexture(*m_shared.m_texMgr->getTexture("background"));
	m_backgroundImage.setPosition(0, 0);
	auto windowSize = m_shared.m_window->getRenderWindow()->getSize();
	auto textureSize = m_backgroundImage.getTexture()->getSize();
	float scaleX = float(windowSize.x) / textureSize.x;
	float scaleY = float(windowSize.y) / textureSize.y;
	m_backgroundImage.setScale(scaleX, scaleY);
}

Game::~Game()
{
	delete m_shared.m_texMgr;
	m_shared.m_texMgr = nullptr;
	delete m_shared.m_window;
	m_shared.m_window = nullptr;
	delete m_shared.m_stateMgr;
	m_shared.m_stateMgr = nullptr;
}

void Game::play()
{
	while (m_shared.m_window->isOpen())
	{
		handleInput();
		update();
		render();
	}
}

void Game::handleInput()
{
	sf::Event event;
	while (m_shared.m_window->getRenderWindow()->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Resized:
			if (m_shared.m_window->getRenderWindow()->getSize().x < 600)
			{
				m_shared.m_window->getRenderWindow()->setSize({ 600, m_shared.m_window->getRenderWindow()->getSize().y });
			}
			if (m_shared.m_window->getRenderWindow()->getSize().y < 420)
			{
				m_shared.m_window->getRenderWindow()->setSize({ m_shared.m_window->getRenderWindow()->getSize().x, 420 });

			}
			m_shared.m_window->getRenderWindow()->setView(sf::View(
				{ 0, 0, (float)m_shared.m_window->getRenderWindow()->getSize().x, (float)m_shared.m_window->getRenderWindow()->getSize().y }));
			m_backgroundImage.setScale(m_shared.m_window->getScale());
			m_shared.m_stateMgr->onResize();
			break;
		case sf::Event::Closed:
			m_shared.m_window->destroy();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F5)
			{
				m_shared.m_window->toggleFullscreen();
			}
			else if (event.key.code == sf::Keyboard::P)
			{
				m_shared.m_stateMgr->togglePause();
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				m_shared.m_stateMgr->swapState(StateType::MainMenu);
			}
			break;
		}
	}
	m_shared.m_stateMgr->handleInput();
}

void Game::update()
{
	m_shared.m_stateMgr->update();
}

void Game::render()
{
	m_shared.m_window->getRenderWindow()->clear();
	m_shared.m_window->getRenderWindow()->draw(m_backgroundImage);
	m_shared.m_stateMgr->render();
	m_shared.m_window->getRenderWindow()->display();
}
