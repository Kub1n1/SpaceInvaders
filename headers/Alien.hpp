#pragma once

#include "Enemy.hpp"
#include "Hitbox.hpp"

class Alien
	: public Enemy
{
public:
	/* Constructors */
	Alien( 
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr< SpriteManager > spriteManager
	);

	/* Destructors */
	virtual ~Alien() = default;

	/* Core */
	virtual void Update(const float dt) override;
	virtual void Render(std::shared_ptr< sf::RenderTarget > target) override;
	virtual void RenderHitbox() override;

	/* Getters */
	virtual std::shared_ptr<sf::FloatRect> GetRect() const override;
	virtual int GiveScoreForDestroy();

private:
	/* Initialization */
	virtual void InitSprites() override;
	virtual void InitScore() override;
	void InitHealth();
	void InitHitbox();

	/* Updates */
	void UpdateHitbox();

	/* Renders */

private:
	/* Variables */
	std::shared_ptr<Hitbox> _hitbox;
};