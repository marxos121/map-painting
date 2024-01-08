#include "Game.h"
#include "Window.h"
#include "Map.h"
#include "StateManager.h"
#include "TextureManager.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Game::Game()
{
	m_shared.m_window = new GameWindow(sf::VideoMode(800, 600), "Tiles", sf::Style::Fullscreen);
	m_shared.m_window->setKeyRepeatEnabled(false);

	m_shared.m_texMgr = new TextureManager;
	m_backgroundImage.setTexture(*m_shared.m_texMgr->getTexture("background"));
	m_backgroundImage.setPosition(0, 0);

	m_shared.m_stateMgr = new StateManager(&m_shared);
	m_shared.m_stateMgr->addState<StateMainMenu>();
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
	while (m_shared.m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Resized:
			if (event.size.width < 600)
			{
				m_shared.m_window->setSize({ 600, m_shared.m_window->getSize().y });
			}
			if (event.size.height < 420)
			{
				m_shared.m_window->setSize({ m_shared.m_window->getSize().x, 420 });
			}
			m_shared.m_window->updateWindowedSize();
			onResize();
			break;
		case sf::Event::Closed:
			m_shared.m_window->close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F5)
			{
				m_shared.m_window->toggleFullscreen();
				onResize();
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
	m_shared.m_window->clear();
	m_shared.m_window->draw(m_backgroundImage);
	m_shared.m_stateMgr->render();
	m_shared.m_window->display();
}

void Game::onResize()
{
	m_backgroundImage.setScale(m_shared.m_window->getScale());
	m_shared.m_stateMgr->onResize();
}
