#include "SheetAnimation.h"
#include "Shared.h"
#include "TextureManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <sstream>
#include <fstream>

SheetAnimation::SheetAnimation(Shared* shared, const std::string& filename, sf::Vector2f spriteSize)
	: m_shared(shared), m_spriteSize(spriteSize)
{
	m_sheet = m_shared->m_texMgr->getTexture(filename);
	m_currentFrame = 0;
	m_totalFrames = m_sheet->getSize().x / m_sheet->getSize().y;

	std::ifstream in("frame.txt");
	std::string frameLength;
	std::getline(in, frameLength);
	std::stringstream ss(frameLength);
	ss >> m_frameLength;
	//m_frameLength = 0.25f;

	m_currentFrameElapsedTime = 0.f;
	m_play = m_loop = false;

	m_sprite.setTexture(*m_sheet);
	crop();
}

void SheetAnimation::update(float dT)
{
	if (!m_play)
	{
		return;
	}

	m_currentFrameElapsedTime += dT;

	if (m_currentFrameElapsedTime >= m_frameLength)
	{
		++m_currentFrame;

		if (m_currentFrame >= m_totalFrames)
		{
			m_currentFrame = 0;

			if (!m_loop)
			{
				m_play = false;
			}
		}

		m_currentFrameElapsedTime = 0.f;
	}
}

void SheetAnimation::setPosition(sf::Vector2f newPos)
{
	m_sprite.setPosition(newPos);
}

void SheetAnimation::move(sf::Vector2f offset)
{
	m_sprite.move(offset);
}

void SheetAnimation::setPlay(bool play)
{
	m_play = play;
}

void SheetAnimation::setLooping(bool looping)
{
	m_loop = looping;
}

void SheetAnimation::setFrame(int frame)
{
	m_currentFrame = frame;
}

void SheetAnimation::crop()
{
	sf::IntRect rect = { (int)m_spriteSize.x * m_currentFrame, 0, (int)m_spriteSize.x, (int)m_spriteSize.y };
	m_sprite.setTextureRect(rect);
}

void SheetAnimation::draw(sf::RenderWindow& window)
{
	crop();
	window.draw(m_sprite);
}

sf::Sprite& SheetAnimation::getSprite()
{
	return m_sprite;
}

bool SheetAnimation::isPlaying() const
{
	return m_play;
}

int SheetAnimation::getCurrentFrame() const
{
	return m_currentFrame;
}