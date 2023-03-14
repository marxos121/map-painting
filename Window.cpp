#include "Window.h"
#include "Shared.h"
#include "StateManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

GameWindow::GameWindow(const std::string& l_name, unsigned int l_x, unsigned int l_y, bool l_fullscreen)
    : m_name(l_name), m_x(l_x), m_y(l_y), m_fullscreen(l_fullscreen), m_shared(nullptr)
{
    m_window.setFramerateLimit(70);
    create();
}

GameWindow::~GameWindow()
{
   destroy();
}

void GameWindow::initShared(Shared* shr)
{
    m_shared = shr;
}

void GameWindow::destroy()
{
    m_window.close();
}

void GameWindow::create()
{
    auto fullscreen = m_fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    m_window.create({ m_x, m_y, 32 }, "Tiles", fullscreen);
}

sf::RenderWindow* GameWindow::getRenderWindow()
{
    return &m_window;
}

void GameWindow::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::F5)
            {
                toggleFullscreen();
            }
            else if (event.key.code == sf::Keyboard::P)
            {
                m_shared->m_stateMgr->togglePause();
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                m_shared->m_stateMgr->swapState(StateType::MainMenu);
            }
            break;
        }
    }
}

void GameWindow::toggleFullscreen()
{
    m_fullscreen = !m_fullscreen;
    destroy();
    create();
}

bool GameWindow::isOpen() const
{
    return m_window.isOpen();
}
