#pragma once

#include "WindowSettings.hpp"

struct Time
{
	float deltaTime;
	sf::Clock clock;
	float enemyMoveTime;
	float enemyMoveTimer;
	float playerShootTime;
	float playerShootTimer;
	float hitboxViewTime;
	float hitboxViewTimer;
	float enemiesShootTime;
	float enemiesShootTimer;
};