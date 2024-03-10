#pragma once

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Hitbox.hpp"

class Player 
	: public Entity
{
public:
	/* Constructors */
	Player ( 
		std::shared_ptr< sf::RenderWindow > window,
		std::shared_ptr< SpriteManager > spriteManager
	);

	/* Destructors */
	virtual ~Player() = default;
	 
	/* Core */
	virtual void Update(const float dt) override;
	virtual void Render( std::shared_ptr< sf::RenderTarget > target ) override;
	virtual void RenderHitbox() override;
	void Move(const float x_dir, const float y_dir);
	void Shoot();
	bool CheckForHits(std::shared_ptr < sf::FloatRect > rect);
	void TakeDamage();
	void ResetHealth();

	/* Getters */
	Health GiveHealth() const;
	std::vector< std::shared_ptr<Bullet> >& GiveBullets();
	std::shared_ptr < sf::FloatRect > GiveRect();

private:
	/* Initialization */
	virtual void InitSprites() override;
	virtual void InitHitbox() override;
	void InitMoveComponent();
	void InitHealth();

	/* Updates */
	void UpdateMovement(const float dt);
	void UpdatePlayerPosition();
	void UpdateBounds();
	void UpdateBulletsBounds();
	void UpdateHitbox();

private:
	/* Variables */
	std::vector< std::shared_ptr<Bullet> > _bullets;

};
