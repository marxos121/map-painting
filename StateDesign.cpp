#include "StateDesign.h"

#include "Shared.h"
#include "TextureManager.h"
#include "Window.h"

#include <SFML/Window/Mouse.hpp>

#include <fstream>
#include <filesystem>

StateDesign::StateDesign(Shared* shared)
	: BaseState(StateType::Design, shared), m_mapSize({ 1, 1})
{
	m_tiles.push_back(std::vector<sf::Sprite>(1, sf::Sprite(
		*m_shared->m_texMgr->getTexture("unpainted"))));
	onResize();
	m_tiles[0][0].setPosition(m_shared->m_window->getSize().x / 2
		- m_tiles[0][0].getGlobalBounds().width / 2,
		m_shared->m_window->getSize().y / 2
		- m_tiles[0][0].getGlobalBounds().height / 2);

	m_font.loadFromFile("./Graphics/KOMIKAP.TTF");
	m_buttons["clear"].text.setString("Clear");
	m_buttons["save"].text.setString("Save");
	m_buttons["width"].text.setString("Width:");
	m_buttons["height"].text.setString("Height:");
	m_buttons["width+"].text.setString("+");
	m_buttons["width-"].text.setString("-");
	m_buttons["undo"].text.setString("Undo");

	m_buttons["height+"] = m_buttons["width+"];
	m_buttons["height-"] = m_buttons["width-"];

	for (auto& button : m_buttons) {
		button.second.text.setFont(m_font);
		button.second.text.setCharacterSize(32);
		button.second.text.setFillColor(sf::Color::White);
		auto rect = button.second.text.getLocalBounds();
		button.second.text.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	}

	m_buttons["width"].text.setPosition(70.f, 40.f);
	m_buttons["width-"].text.setPosition(50.f, 75.f);
	m_buttons["width+"].text.setPosition(90.f, 75.f);

	m_buttons["height"].text.setPosition(70.f, 120.f);
	m_buttons["height-"].text.setPosition(50.f, 155.f);
	m_buttons["height+"].text.setPosition(90.f, 155.f);


	m_buttons["save"].text.setPosition(70.f, 200.f);
	m_buttons["undo"].text.setPosition(70.f, 250.f);
	m_buttons["clear"].text.setPosition(70.f, 300.f);

	m_sizingBackground.setPosition(m_buttons["height"].text.getGlobalBounds().left - 5,
		m_buttons["width"].text.getGlobalBounds().top - 10);
	m_sizingBackground.setSize(sf::Vector2f(m_buttons["height"].text.getGlobalBounds().width + 10, 
		m_buttons["height+"].text.getGlobalBounds().top + 2*m_buttons["height+"].text.getGlobalBounds().height - m_buttons["width"].text.getGlobalBounds().top));
	m_sizingBackground.setFillColor(sf::Color(0, 0, 0, 150));
	m_sizingBackground.setOutlineColor(sf::Color::White);
	m_sizingBackground.setOutlineThickness(2);

	sf::Vector2f buttonSize = { m_buttons["width+"].text.getLocalBounds().width + 4,  m_buttons["width+"].text.getLocalBounds().height + 4 };
	m_buttons["width+"].background.setSize(buttonSize);
	m_buttons["width-"].background.setSize(buttonSize);
	m_buttons["height+"].background.setSize(buttonSize);
	m_buttons["height-"].background.setSize(buttonSize);

	m_buttons["save"].background.setPosition(m_buttons["height"].text.getGlobalBounds().left - 5, m_buttons["save"].text.getGlobalBounds().top - 5);
	m_buttons["save"].background.setSize(sf::Vector2f(m_buttons["height"].text.getGlobalBounds().width + 10, m_buttons["save"].text.getGlobalBounds().height + 10));

	m_buttons["undo"].background.setPosition(m_buttons["height"].text.getGlobalBounds().left - 5, m_buttons["undo"].text.getGlobalBounds().top - 5);
	m_buttons["undo"].background.setSize(sf::Vector2f(m_buttons["height"].text.getGlobalBounds().width + 10, m_buttons["undo"].text.getGlobalBounds().height + 10));

	m_buttons["clear"].background.setPosition(m_buttons["height"].text.getGlobalBounds().left - 5, m_buttons["clear"].text.getGlobalBounds().top - 5);
	m_buttons["clear"].background.setSize(sf::Vector2f(m_buttons["height"].text.getGlobalBounds().width + 10, m_buttons["clear"].text.getGlobalBounds().height + 10));

	m_buttons["width+"].background.setOrigin(m_buttons["width+"].background.getLocalBounds().left +
		m_buttons["width+"].background.getLocalBounds().width / 2, 
		m_buttons["width+"].background.getLocalBounds().top +
		m_buttons["width+"].background.getLocalBounds().height / 2);
	m_buttons["width+"].background.setPosition(m_buttons["width+"].text.getPosition());

	m_buttons["width-"].background.setOrigin(m_buttons["width-"].background.getLocalBounds().left +
		m_buttons["width-"].background.getLocalBounds().width / 2,
		m_buttons["width-"].background.getLocalBounds().top +
		m_buttons["width-"].background.getLocalBounds().height / 2);
	m_buttons["width-"].background.setPosition(m_buttons["width-"].text.getPosition());

	m_buttons["height+"].background.setOrigin(m_buttons["height+"].background.getLocalBounds().left +
		m_buttons["height+"].background.getLocalBounds().width / 2,
		m_buttons["height+"].background.getLocalBounds().top +
		m_buttons["height+"].background.getLocalBounds().height / 2);
	m_buttons["height+"].background.setPosition(m_buttons["height+"].text.getPosition());

	m_buttons["height-"].background.setOrigin(m_buttons["height-"].background.getLocalBounds().left +
		m_buttons["height-"].background.getLocalBounds().width / 2,
		m_buttons["height-"].background.getLocalBounds().top +
		m_buttons["height-"].background.getLocalBounds().height / 2);
	m_buttons["height-"].background.setPosition(m_buttons["height-"].text.getPosition());


	for (auto& button : m_buttons) {
		button.second.background.setFillColor(sf::Color::Color(0, 0, 0, 150));
		button.second.background.setOutlineColor(sf::Color::White);
		button.second.background.setOutlineThickness(2);
	}

}

void StateDesign::handleInput()
{
	static bool released = true;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		released = true;
		return;
	}

	if (!released) {
		return;
	}

	released = false;

	auto pos = sf::Mouse::getPosition(*m_shared->m_window);
	pos = sf::Vector2i(m_shared->m_window->mapPixelToCoords(pos));

	for (auto& button : m_buttons) {
		if (!(pos.x > button.second.background.getGlobalBounds().left
			&& pos.x < button.second.background.getGlobalBounds().left + button.second.background.getGlobalBounds().width
			&& pos.y > button.second.background.getGlobalBounds().top
			&& pos.y < button.second.background.getGlobalBounds().top + button.second.background.getGlobalBounds().height))
		{
			continue;
		}

		if (button.first == "clear") {
			clear();
			return;
		}
	    if (button.first == "save") {
			save();
			return;
		}
		if (button.first == "width+") {
			m_mapSize.x++;
			if (m_mapSize.x > 8)
				m_mapSize.x = 8;
			m_updateTiles = true;
			return;
		}
		if (button.first == "width-") {
			m_mapSize.x--;
			if (m_mapSize.x < 1)
				m_mapSize.x = 1;
			m_updateTiles = true;
			return;
		}
		if (button.first == "height+") {
			m_mapSize.y++;
			if (m_mapSize.y > 8)
				m_mapSize.y = 8;
			m_updateTiles = true;
			return;
		}
		if (button.first == "height-") {
			m_mapSize.y--;
			if(m_mapSize.y < 1)
				m_mapSize.y = 1;
			m_updateTiles = true;
			return;
		}
		if (button.first == "undo" && !m_player.empty()) {
			m_tiles[m_player.back().y][m_player.back().x].setTexture(*m_shared->m_texMgr->getTexture("unpainted"));
			m_player.pop_back();
			return;
		}
	}

	for (int y = 0; y != m_tiles.size(); ++y) {
		for (int x = 0; x != m_tiles[y].size(); ++x) {
			auto bounds = m_tiles[y][x].getGlobalBounds();
			if (pos.x > bounds.left && pos.x < bounds.left + bounds.width
				&& pos.y > bounds.top && pos.y < bounds.top + bounds.height)
			{
				if (m_player.empty() || 
					(!m_player.empty() && (abs(x - m_player.back().x) + abs(y - m_player.back().y) == 1)
						&& std::find(m_player.cbegin(), m_player.cend(), sf::Vector2i({ x, y })) == m_player.cend()))
				{
					m_player.push_back(sf::Vector2i(x, y));
					m_tiles[y][x].setTexture(*m_shared->m_texMgr->getTexture("blocksheet"));
					m_tiles[y][x].setTextureRect({ 0, 0, 100, 100 });
					return;
				}
			}
		}
	}
}

void StateDesign::update()
{
	if (!m_updateTiles) {
		return;
	}

	if (m_mapSize.y > m_tiles.size()) {
		m_tiles.push_back(std::vector<sf::Sprite>
			(m_tiles.back().size(),
				sf::Sprite(*m_shared->m_texMgr->getTexture("unpainted"))));
	}
	else if (m_mapSize.y < m_tiles.size()) {
		m_tiles.pop_back();
	}

	if(m_mapSize.x > m_tiles.back().size()) {
		for (auto& row : m_tiles) {
			row.push_back(sf::Sprite(*m_shared->m_texMgr->getTexture("unpainted")));
		}
	}
	else if (m_mapSize.x < m_tiles.back().size()) {
		for (auto& row : m_tiles) {
			row.pop_back();
		}
	}

	onResize();
	m_updateTiles = false;
}

void StateDesign::render()
{
	for (int y = 0; y != m_tiles.size(); ++y) {
		for (int x = 0; x != m_tiles[y].size(); ++x) {

			m_shared->m_window->draw(m_tiles[y][x]);
		}
	}

	m_shared->m_window->draw(m_sizingBackground);

	for (auto& button : m_buttons) {
		m_shared->m_window->draw(button.second.background);
		m_shared->m_window->draw(button.second.text);
	}
}

void StateDesign::onResize()
{	
	//Set new positions
	float spriteSize = m_shared->m_window->getScale().x * 100;
	if (spriteSize < 40) {
		spriteSize = 40;
	}
	 
	static const float padding = 2.f;

	float startX = m_shared->m_window->getView().getCenter().x -
		m_mapSize.x * (spriteSize + padding) / 2;
	float posY = m_shared->m_window->getView().getCenter().y -
		m_mapSize.y * (spriteSize + padding) / 2;
	float posX = startX;

	for (int y = 0; y != m_tiles.size(); ++y) {
		for (int x = 0; x != m_tiles[y].size(); ++x) {
			m_tiles[y][x].setScale(spriteSize / 100, spriteSize / 100);
			m_tiles[y][x].setPosition(posX, posY);
			posX += spriteSize + padding;
		}
		posY += spriteSize + padding;
		posX = startX;
	}

}

void StateDesign::save()
{
	if (m_player.empty()) {
		return;
	}
	std::filesystem::path maps = std::filesystem::current_path() / "Maps";
	std::string newMap = "";

	int i = 1;
	while (std::filesystem::exists(maps / ("map" + std::to_string(i) + ".txt"))) {
		++i;
	}

	newMap = "map" + std::to_string(i) + ".txt";

	//If there are > 1 map, append the new map after the latest one
	if (i > 1) {
		std::string prevMap = "map" + std::to_string(i - 1) + ".txt";
		std::ifstream is_prevMap("./Maps/" + prevMap);
		std::ofstream os_prevMap("./Maps/newmap.txt");

		std::string line;
		while (std::getline(is_prevMap, line)) {
			std::stringstream ss(line);
			std::string tag;
			ss >> tag;

			if (tag == "NEXT:") {
				ss >> tag;
				if (tag != "NULL") {
					break;
				}

				line = "NEXT: " + newMap;
			}

			os_prevMap << line + '\n';
		}

		is_prevMap.close();
		os_prevMap.close();

		std::filesystem::rename(maps / "newmap.txt", maps / prevMap);
	}

	std::ofstream os("./Maps/" + newMap);

	os << "--MAPFILE--\nNEXT: NULL\nSIZE: "
		<< m_mapSize.x << " " << m_mapSize.y
		<< "\nSTART: " << m_player.front().x << " " << m_player.front().y << std::endl;
	int added = 0;
	for (int x = 0; x != m_mapSize.x; ++x) 
	{
		for (int y = 0; y != m_mapSize.y; ++y)
		{
			bool isPath = std::find(m_player.cbegin(), m_player.cend(), sf::Vector2i(x, y)) != m_player.cend();

			if (isPath) {
				continue;
			}
			os << "TILE: " << x << " " << y << std::endl;
		}
	}

	os.close();
}

void StateDesign::clear()
{
	m_player.clear();

	for (auto& row : m_tiles) {
		for (auto& cell : row) {
			cell.setTexture(*m_shared->m_texMgr->getTexture("unpainted"));
		}
	}
}
