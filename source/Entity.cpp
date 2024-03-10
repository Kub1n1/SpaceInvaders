#include "Entity.hpp"

/* Constructors */
Entity::Entity(
	std::shared_ptr< sf::RenderWindow > window,
	std::shared_ptr< SpriteManager > spriteManager
)
	:Object{window, spriteManager}
{
	this->InitMoveComponent();
	this->InitHealth();
}

/* Initialization */
void Entity::InitMoveComponent()
{
	_moveComp.direction.x = 0.f;
	_moveComp.direction.y = 0.f;
	_moveComp.velocity.x = 0.f;
	_moveComp.velocity.y = 0.f;
	_moveComp.maxSpeed.x = 0.f;
	_moveComp.maxSpeed.y = 0.f;
	_moveComp.acceleration.x = 0.f;
	_moveComp.acceleration.y = 0.f;
	_moveComp.decceleration.x = 0.f;
	_moveComp.decceleration.y = 0.f;
}

void Entity::InitHealth()
{
	_health.maxHP = 0;
	_health.hp = _health.maxHP;
}