#pragma once

#include "Libraries.hpp"

struct WindowSettings
{
	sf::VideoMode resolution;
	bool isFullscreen;
	unsigned int frameLimit;
	std::string title;
};