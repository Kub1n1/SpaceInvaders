#pragma once

#include "Object.hpp"

class Bullet
	: public Object
{
public:
	/* Constructor */
	Bullet(
		std::shared_ptr< sf::RenderWindow > window,
		std::shared_ptr< SpriteManager > spriteManager
	);

	/* Destructor */
	virtual ~Bullet() = default;

	/* Core */
	virtual void Update( const float dt ) override;
	virtual void Render( std::shared_ptr< sf::RenderTarget > target ) override;
	virtual void RenderHitbox() override;

	/* Getters */
	bool CheckHit(std::shared_ptr < sf::FloatRect > rect) const;
	std::shared_ptr< sf::FloatRect > GiveRect();
	void ChangeDirection();

private:
	/* Initialization */
	virtual void InitHitbox() override;
	virtual void InitSprites() override;
	void InitMoveComponent();

	/* Updates */
	void UpdateMovement( const float dt );
	void UpdateHitbox();

private:
	/* Variables */
	std::string _currentSprite;
	MoveComponent _moveComp;
};