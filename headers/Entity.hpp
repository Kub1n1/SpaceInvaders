#pragma once

#include "MoveComponent.hpp"
#include "Health.hpp"
#include "Object.hpp"

class Entity
	: public Object
{
public:
	/* Constructors */
	Entity( 
		std::shared_ptr< sf::RenderWindow > window,
		std::shared_ptr< SpriteManager > spriteManager
	);

	/* Destructors */
	virtual ~Entity() = default;

private:
	/* Initialization */
	void InitMoveComponent();
	void InitHealth();

protected:
	/* Variables */
	MoveComponent _moveComp;
	Health _health;
};