#pragma once

#include <SFML/Graphics/Text.hpp>

struct Shared;


class HUD
{
public:
	HUD(Shared*);

	void initialise(int blocks);
	
	void update(float dT, int playerSize);
	void draw();
	void onResize();

private:
	sf::Font m_font;
	sf::Text m_time;
	sf::Text m_blocks;

	int m_blocksToPaint;
	Shared* m_shared;
};