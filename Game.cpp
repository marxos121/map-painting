#include "Game.h"
#include "Window.h"
#include "Map.h"
#include "StateManager.h"
#include "TextureManager.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

Game::Game()
	: m_stateMgr(&shared)
{
	shared.m_window = new GameWindow("Tiles", 1200, 900);
	shared.m_texMgr = new TextureManager;
	shared.m_stateMgr = new StateManager(&shared);

	shared.m_stateMgr->addState<StateMainMenu>();

	shared.m_window->getRenderWindow()->setKeyRepeatEnabled(false);
	shared.m_window->initShared(&shared);

	m_backgroundImage.setTexture(*shared.m_texMgr->getTexture("background"));
	m_backgroundImage.setPosition(0, 0);

	auto windowSize = shared.m_window->getRenderWindow()->getSize();
	auto textureSize = m_backgroundImage.getTexture()->getSize();
	float scaleX = float(windowSize.x) / textureSize.x;
	float scaleY = float(windowSize.y) / textureSize.y;
	m_backgroundImage.setScale(scaleX, scaleY);
}

Game::~Game()
{
	delete shared.m_texMgr;
	shared.m_texMgr = nullptr;
	delete shared.m_window;
	shared.m_window = nullptr;
	delete shared.m_stateMgr;
	shared.m_stateMgr = nullptr;
}

void Game::play()
{
	while (shared.m_window->isOpen())
	{
		handleInput();
		update();
		render();
	}
}

void Game::handleInput()
{
	shared.m_window->handleEvents();
	shared.m_stateMgr->handleInput();
}

void Game::update()
{
	shared.m_stateMgr->update();
}

void Game::render()
{
	shared.m_window->getRenderWindow()->clear();
	shared.m_window->getRenderWindow()->draw(m_backgroundImage);
	shared.m_stateMgr->render();
	shared.m_window->getRenderWindow()->display();
}
