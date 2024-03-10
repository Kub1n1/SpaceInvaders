#include "SpriteManager.hpp"

/* Core */
void SpriteManager::LoadSprite(std::string texturePath, std::string spriteName)
{
	_textures[spriteName] = std::make_shared<sf::Texture>();

	if (!_textures.at(spriteName)->loadFromFile(texturePath))
	{
		throw (
			"ERROR::SPRITE_MANGER::LOAD_SPRITE::TEXTURE( "
			+ spriteName + " )::NOT_OPENED( " + texturePath + " )"
			);

		return;
	}

	_sprites[spriteName] = std::make_shared<sf::Sprite>();
	_sprites.at(spriteName)->setTexture(*_textures.at(spriteName));
}

void SpriteManager::RenderSprite(
	std::string spriteName, SpriteData spriteData,
	std::shared_ptr<sf::RenderTarget> target
)
{
	if (target == nullptr)
	{
		throw "ERROR::SPRITE_MANGER::RENDER_SPRITE::TARGE_IS_NULL";
		return;
	}

	_sprites.at(spriteName)->setScale(spriteData.scale);
	_sprites.at(spriteName)->setPosition(spriteData.position);

	target->draw( *_sprites.at(spriteName) );
}

/* Getters */
sf::Vector2f SpriteManager::GetSpriteSize( std::string spriteName )
{
	return { 
		_sprites.at(spriteName)->getGlobalBounds().width, 
		_sprites.at(spriteName)->getGlobalBounds().height
	};
}