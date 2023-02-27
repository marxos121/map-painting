#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <string>

struct Shared;

namespace sf
{
	class RenderWindow;
}

class SheetAnimation
{
public:
	SheetAnimation(Shared* shared, const std::string& filename, sf::Vector2f spriteSize);

	void update(float dT);

	void setPosition(sf::Vector2f newPos);
	void move(sf::Vector2f offset);
	void setPlay(bool play);
	void setLooping(bool looping);
	void setFrame(int frame);

	void crop();
	void draw(sf::RenderWindow& window);


	sf::Sprite& getSprite();
	bool isPlaying() const;
	int getCurrentFrame() const;

private:
	sf::Sprite m_sprite;
	sf::Texture* m_sheet;
	sf::Vector2f m_spriteSize;

	float m_frameLength;
	float m_currentFrameElapsedTime;

	int m_totalFrames;
	int m_currentFrame;
	bool m_play;
	bool m_loop;

	Shared* m_shared;
};