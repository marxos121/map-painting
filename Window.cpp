#include "Window.h"

GameWindow::GameWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style)
    : m_bIsFullscreen(false)
{
    m_windowedSize = { mode.width, mode.height };
    if (style == sf::Style::Fullscreen)
    {
        m_bIsFullscreen = true;
        mode = sf::VideoMode::getDesktopMode();
        m_windowedSize = { 1200, 900 };
    }

    create(mode, title, style);
    setFramerateLimit(70);
    setKeyRepeatEnabled(false);
}

void GameWindow::toggleFullscreen()
{
    if (m_bIsFullscreen) {
        create(sf::VideoMode(getWindowedSize().x, getWindowedSize().y), "Tiles", sf::Style::Default);
    }
    else {
        create(sf::VideoMode::getDesktopMode(), "Tiles", sf::Style::Fullscreen);
    }
    setView(sf::View({ 0.f, 0.f, (float)getSize().x, (float)getSize().y }));
    m_bIsFullscreen = !m_bIsFullscreen;
}

void GameWindow::updateWindowedSize()
{
    if (!m_bIsFullscreen)
    {
        m_windowedSize = getSize();
        setView(sf::View({ 0.f, 0.f, (float)getSize().x, (float)getSize().y }));
    }
}

bool GameWindow::isFullscreen() const
{
    return m_bIsFullscreen;
}

sf::Vector2u GameWindow::getWindowedSize() const
{
    return m_windowedSize;
}

sf::Vector2f GameWindow::getScale() const
{
    return { getSize().x / (float)sf::VideoMode::getDesktopMode().width, getSize().y / (float)sf::VideoMode::getDesktopMode().height };
}
