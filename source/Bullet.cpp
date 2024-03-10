#include "Bullet.hpp"

/* Constructor */
Bullet::Bullet(
	std::shared_ptr<sf::RenderWindow> window,
	std::shared_ptr< SpriteManager > spriteManager
)
	:Object{window, spriteManager}
{
	this->InitSprites();
	this->InitMoveComponent();
	this->InitHitbox();
}

/* Core */
void Bullet::Update(const float dt)
{
	this->UpdateMovement(dt);
	this->UpdateHitbox();
}

void Bullet::Render( std::shared_ptr<sf::RenderTarget> target = nullptr)
{
	if (target == nullptr)
		target = _window;

	_spriteManager->RenderSprite(_currentSprite, _spriteData, target);
}

void Bullet::RenderHitbox()
{
	_hitbox->Render(_window);
}

/* Getters */
bool Bullet::CheckHit(std::shared_ptr < sf::FloatRect > rect) const
{
	return _hitbox->IsHit(rect);
}

std::shared_ptr<sf::FloatRect> Bullet::GiveRect()
{
	return _hitbox->GetRect();
}

void Bullet::ChangeDirection()
{
	_moveComp.direction.y *= -1.f;
}

/* Initialization */
void Bullet::InitHitbox()
{
	float width = 2.f;
	float height = 2.f;
	float scale = _spriteData.scale.x;

	_hitbox = std::make_shared<Hitbox>(
		-1.f - width * scale, -1.f - height * scale,
		width * scale, height * scale
	);

}

void Bullet::InitSprites()
{	
	std::string spriteName{ "bullet_0" };
	std::string texturePath{ "assets/sprites/bullet/bullet_0.png" };

	_spriteManager->LoadSprite(texturePath, spriteName);
	_currentSprite = spriteName;

	float scale = 3.f;
	_spriteData.scale.x = scale;
	_spriteData.scale.y = scale;
	_spriteData.size = _spriteManager->GetSpriteSize(_currentSprite);
}

void Bullet::InitMoveComponent()
{
	_moveComp.acceleration.y = 800.f;
	_moveComp.direction.y = 1.f;
}

/* Updates */
void Bullet::UpdateMovement(const float dt)
{
	_moveComp.velocity.y = -_moveComp.acceleration.y * dt * _moveComp.direction.y;
	_spriteData.position += _moveComp.velocity;
}

void Bullet::UpdateHitbox()
{
	float scale = _spriteData.scale.x;
	float x_pos = _spriteData.position.x + 7.f * scale;
	float y_pos = _spriteData.position.y + 7.f * scale;

	if (x_pos == 0.f && y_pos == 0.f)
		return;
	
	_hitbox->Update(x_pos, y_pos);
}