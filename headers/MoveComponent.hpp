#pragma once

#include "Libraries.hpp"

struct MoveComponent
{
	sf::Vector2f direction;
	sf::Vector2f velocity;
	sf::Vector2f maxSpeed;
	sf::Vector2f acceleration;
	sf::Vector2f decceleration;
};