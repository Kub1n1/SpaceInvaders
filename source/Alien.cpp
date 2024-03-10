#include "Alien.hpp"

/* Constructors */
Alien::Alien(
	std::shared_ptr<sf::RenderWindow> window,
	std::shared_ptr< SpriteManager > spriteManager
)
	: Enemy{window, spriteManager}
{
	this->InitSprites();
	this->InitHealth();
	this->InitHitbox();
	this->InitScore();
}

/* Core */
void Alien::Update(const float dt)
{
	Enemy::Update(dt);
	this->UpdateHitbox();
}

void Alien::Render(std::shared_ptr<sf::RenderTarget> target = nullptr)
{
	if (target == nullptr)
		target = _window;

	_spriteManager->RenderSprite(_currentSprite, _spriteData, target);
}

void Alien::RenderHitbox()
{
	_hitbox->Render(_window);
}

std::shared_ptr<sf::FloatRect> Alien::GetRect() const
{
	return std::shared_ptr<sf::FloatRect>( _hitbox->GetRect() );
}

int Alien::GiveScoreForDestroy()
{
	return _score;
}

/* Initialization */
void Alien::InitSprites()
{
	std::string spriteName{ "alien_0" };
	std::string texturePath{ "assets/sprites/enemy/alien_0.png" };

	_spriteManager->LoadSprite(texturePath, spriteName);
	_currentSprite = spriteName;

	float scale = 3.f;
	_spriteData.scale.x = scale;
	_spriteData.scale.y = scale;
	_spriteData.size = _spriteManager->GetSpriteSize(_currentSprite);

}

void Alien::InitScore()
{
	_score = 10;
}

void Alien::InitHealth()
{
	_health.maxHP = 1;
	_health.hp = _health.maxHP;
}

void Alien::InitHitbox()
{
	float width = 12.f;
	float height = 8.f;
	float scale = _spriteData.scale.x;
	float x_loc = 2.f;
	float y_loc = 4.f;
	float x_word = _spriteData.position.x + x_loc;
	float y_word = _spriteData.position.y + y_loc;

	_hitbox = std::make_shared<Hitbox>(
		(x_word * scale), (y_word * scale),
		(width * scale), (height * scale)
	);
}

/* Updates */
void Alien::UpdateHitbox()
{
	float scale = _spriteData.scale.x;

	float x_pos = _spriteData.position.x + 2.f * scale;
	float y_pos = _spriteData.position.y + 4.f * scale;

	_hitbox->Update(x_pos, y_pos);

}