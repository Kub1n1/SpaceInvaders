#pragma once

#include "Libraries.hpp"

class Hitbox
{
public:
	/* Constructors */
	Hitbox(float x, float y, float width, float height);

	/* Destructors */
	virtual ~Hitbox() = default;

	/* Core */
	void Update(const float x, const float y);
	void Render(std::shared_ptr< sf::RenderTarget > target);

	/* Getters */
	bool IsHit(std::shared_ptr < sf::FloatRect > rect) const;
	std::shared_ptr<sf::FloatRect> GetRect() const;

private:
	/* Initialization */
	void IntiShape();
	void InitRect();

	/* Updates */
	void UpdatesPos();

private:
	/* Variables */
	sf::Vector2f _position;
	sf::Vector2f _size;
	std::shared_ptr < sf::RectangleShape > _shape;
	std::shared_ptr<sf::FloatRect> _rect;
};