#pragma once

#include "Object.hpp"

struct Armor
{
	int maxArmor;
	int armor;
};

class Shield
	: public Object
{
public:
	/* Constructors */
	Shield(
		std::shared_ptr< sf::RenderWindow > window,
		std::shared_ptr< SpriteManager > spriteManager,
		sf::Vector2f startPosition
	);

	/* Destructors */
	virtual ~Shield() = default;

	/* Core */
	virtual void Update(const float dt) override;
	virtual void Render( std::shared_ptr< sf::RenderTarget > target ) override;
	virtual void RenderHitbox() override;
	void ReduceArmor();

	/* Getters */
	std::shared_ptr< sf::FloatRect > GetRect();
	Armor GetArmor() const;

private:
	/* Initialization */
	virtual void InitSprites() override;
	virtual void InitHitbox() override;
	void InitStartPosition(sf::Vector2f startPosition);
	void InitArmor();

private:
	/* Variables */
	Armor _armor;

};