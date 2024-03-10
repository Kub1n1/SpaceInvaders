#include "Hitbox.hpp"

/* Constructors */
Hitbox::Hitbox(float x, float y, float width, float height)
	:_position{x, y}, _size{width, height}
{
	this->IntiShape();
	this->InitRect();
}

/* Core */
void Hitbox::Update(const float x, const float y)
{
	_position.x = x;
	_position.y = y;
	_rect->left = x;
	_rect->top = y;

	this->UpdatesPos();
}

void Hitbox::Render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(*_shape);
}

/* Getters */
bool Hitbox::IsHit(std::shared_ptr < sf::FloatRect > rect) const
{
	return _rect->intersects(*rect);
}

std::shared_ptr<sf::FloatRect> Hitbox::GetRect() const
{
	return _rect;
}

/* Initialization */
void Hitbox::IntiShape()
{
	_shape = std::make_shared< sf::RectangleShape >();
	_shape->setSize(_size);
	_shape->setFillColor(sf::Color::Transparent);
	_shape->setOutlineThickness(1.f);
	_shape->setOutlineColor(sf::Color::Magenta);
	_shape->setPosition(_position);
}

void Hitbox::InitRect()
{
	_rect = std::make_shared< sf::FloatRect>(_position, _size);
}

/* Updates */
void Hitbox::UpdatesPos()
{
	_shape->setPosition(_position);
	_rect->left = _position.x;
	_rect->top = _position.y;
}
