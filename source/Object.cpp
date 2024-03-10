#include "Object.hpp"

/* Constructor */
Object::Object(
	std::shared_ptr< sf::RenderWindow > window,
	std::shared_ptr< SpriteManager > spriteManager
)
	:_window{ window }, _spriteManager{ spriteManager }, _hitbox{ nullptr }
{
	this->InitSpriteData();
}

/* Settters */
void Object::SetPos(float x, float y)
{
	_spriteData.position = { x, y };
}

/* Getters */
sf::Vector2f Object::GetPos() const
{
	return _spriteData.position;
}

sf::Vector2f Object::GetSize() const
{
	return _spriteData.size;
}

sf::Vector2f Object::GetScale() const
{
	return _spriteData.scale;
}

/* Initialization */
void Object::InitSpriteData()
{
	_spriteData.scale.x = 0.f;
	_spriteData.scale.y = 0.f;
	_spriteData.position.x = 0.f;
	_spriteData.position.y = 0.f;
	_spriteData.size.x = 0.f;
	_spriteData.size.y = 0.f;
}
