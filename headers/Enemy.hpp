#pragma once

#include "Entity.hpp"
#include "Bullet.hpp"

class Enemy
	: public Entity
{
public:
	/* Constructor */
	Enemy(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr< SpriteManager > spriteManager
	);

	/* Destructor */
	virtual ~Enemy() = default;

	/* Core */
	virtual void Update(const float dt) override;
	virtual void Move();
	virtual void Drop(const float dt);
	virtual void SpeedUp();
	void Shoot(
		std::vector< std::shared_ptr<Bullet> >& enemiesBullets
	);

	/* Getters */
	bool IsRight() const;
	bool GoDown() const;
	virtual std::shared_ptr<sf::FloatRect> GetRect() const = 0;
	virtual int GiveScoreForDestroy() = 0;

private:
	/* Initialization */
	virtual void InitMoveComponent();
	virtual void InitScore() = 0;

	/* Updates */
	virtual void UpdateMovement(const float dt);
	virtual void UpdatePosition();
	virtual void UpdateBounds();

protected:
	/* Variables */
	static bool _goRight;
	static bool _goDown;
	bool _move;
	int _score;

};