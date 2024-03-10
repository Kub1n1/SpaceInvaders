#pragma once

#include "Libraries.hpp"

struct SpriteData
{
	sf::Vector2f scale;
	sf::Vector2f position;
	sf::Vector2f size;
};

class SpriteManager
{
public:
	/* Constructors */
	SpriteManager() = default;

	/* Destructors */
	virtual ~SpriteManager() = default;

	/* Core */
	void LoadSprite(std::string texturePath, std::string spriteName);
	void RenderSprite(
		std::string spriteName, SpriteData spriteData,
		std::shared_ptr<sf::RenderTarget> target
	);

	/* Getters */
	sf::Vector2f GetSpriteSize(std::string spriteName);

private:
	/* Variables */
	std::unordered_map<std::string, std::shared_ptr < sf::Texture > > _textures;
	std::unordered_map<std::string, std::shared_ptr < sf::Sprite > > _sprites;
};