#pragma once

#include "SpriteManager.hpp"

class Object
{
public:
	/* Constructor */
	Object(
		std::shared_ptr< sf::RenderWindow > window,
		std::shared_ptr< SpriteManager > spriteManager
	);

	/* Destructor */
	virtual ~Object() = default;

	/* Core */
	virtual void Update(const float dt) = 0;
	virtual void Render(std::shared_ptr< sf::RenderTarget > target) = 0;
	virtual void RenderHitbox() = 0;

	/* Setters */
	void SetPos(float x, float y);

	/* Getters */
	sf::Vector2f GetPos() const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetScale() const;

private:
	/* Initialization */
	virtual void InitHitbox() = 0;
	virtual void InitSprites() = 0;
	void InitSpriteData();

protected:
	/* Variables */
	std::shared_ptr< sf::RenderWindow > _window;
	std::shared_ptr< SpriteManager > _spriteManager;
	std::shared_ptr< Hitbox > _hitbox;
	std::string _currentSprite;
	SpriteData _spriteData;
};