#include "Player.hpp"

/* Constructors */
Player::Player(
	std::shared_ptr< sf::RenderWindow > window,
	std::shared_ptr< SpriteManager > spriteManager
)
	:Entity{ window, spriteManager}
{
	this->InitSprites();
	this->InitMoveComponent();
	this->InitHealth();
	this->InitHitbox();
}

/* Core */
void Player::Update(const float dt)
{
	this->UpdateMovement(dt);
	this->UpdatePlayerPosition();
	this->UpdateBounds();
	this->UpdateHitbox();

	if (!_bullets.empty())
	{
		this->UpdateBulletsBounds();
		for (const auto& bullet : _bullets)
			bullet->Update(dt);
	}
}

void Player::Render(std::shared_ptr< sf::RenderTarget > target = nullptr)
{
	if (target == nullptr)
		target = _window;

	if (!_bullets.empty())
		for (const auto& bullet : _bullets)
			bullet->Render(target);

	_spriteManager->RenderSprite(_currentSprite, _spriteData, target);
}

void Player::RenderHitbox()
{
	_hitbox->Render(_window);

	if ( !_bullets.empty() )
		for (const auto& bullet : _bullets)
			bullet->RenderHitbox();
}

void Player::Move(const float x_dir, const float y_dir)
{
	_moveComp.direction.x = x_dir;
	_moveComp.direction.y = y_dir;
}

void Player::Shoot()
{
	_bullets.push_back( std::make_shared<Bullet>(_window, _spriteManager) );

	float x_pos = _spriteData.position.x;
	float y_pos = _spriteData.position.y;

	float plWidth = _spriteData.size.x;
	float bulWidth = _bullets.back()->GetSize().x;

	_bullets.back()->SetPos(x_pos, y_pos);
}

bool Player::CheckForHits(std::shared_ptr < sf::FloatRect > rect)
{
	int lastBulletIndex = static_cast<int>(_bullets.size()) - 1;
	for (int i{ lastBulletIndex }; i >= 0; i--)
	{
		if ( _bullets.at(i)->CheckHit(rect) )
		{
			_bullets.erase( _bullets.begin() + i);
			return true;
		}
	}

	return false;
}

void Player::TakeDamage()
{
	_health.hp--;
}

void Player::ResetHealth()
{
	_health.hp = _health.maxHP;
}

/* Getters */
Health Player::GiveHealth() const
{
	return _health;
}

std::vector<std::shared_ptr<Bullet>>& Player::GiveBullets()
{
	return _bullets;
}

std::shared_ptr<sf::FloatRect> Player::GiveRect()
{
	return _hitbox->GetRect();
}

/* Initialization */
void Player::InitSprites()
{
	std::string spriteName{ "player_0" };
	std::string texturePath{ "assets/sprites/player/player_0.png" };

	_spriteManager->LoadSprite(texturePath, spriteName);
	_currentSprite = spriteName;

	float scale = 3.f;
	_spriteData.scale.x = scale;
	_spriteData.scale.y = scale;
	_spriteData.size = _spriteManager->GetSpriteSize(_currentSprite);

}

void Player::InitMoveComponent()
{
	_moveComp.maxSpeed.x = 100.f;
	_moveComp.acceleration.x = 20.f;
	_moveComp.decceleration.x = .95f;
}

void Player::InitHealth()
{
	_health.maxHP = 3;
	_health.hp = _health.maxHP;
}

void Player::InitHitbox()
{
	float width = 10.f;
	float height = 13.f;
	float scale = _spriteData.scale.x;
	float x_pos = _spriteData.position.x + 3.f;
	float y_pos = _spriteData.position.y + 2.f;

	_hitbox = std::make_shared<Hitbox>(
		(x_pos - width * scale), (y_pos - height * scale),
		(width * scale), (height * scale)
	);
}

/* Updates */
void Player::UpdateMovement(const float dt)
{
	// acceleration
	_moveComp.velocity.x += _moveComp.direction.x * _moveComp.acceleration.x * dt;

	// max acceleration
	if (_moveComp.velocity.x >= _moveComp.maxSpeed.x)
		_moveComp.velocity.x = _moveComp.maxSpeed.x;

	if (_moveComp.velocity.x <= -_moveComp.maxSpeed.x)
		_moveComp.velocity.x = -_moveComp.maxSpeed.x;

	// decceleration
	_moveComp.velocity.x *= _moveComp.decceleration.x;

	if (std::abs(_moveComp.velocity.x) < 0)
		_moveComp.direction.x *= 0.f;

}

void Player::UpdatePlayerPosition()
{
	_spriteData.position += _moveComp.velocity;
}

void Player::UpdateBounds()
{
	float windWidth = static_cast<float>(_window->getSize().x);
	float windHeight = static_cast<float>(_window->getSize().y);

	float x_pos = _spriteData.position.x;
	float y_pos = _spriteData.position.y;

	float playerWidth = _spriteData.size.x * _spriteData.scale.x;
	float playerHeight = _spriteData.size.y * _spriteData.scale.y;

	if (x_pos <= 0.f)
		_spriteData.position = {0.f, y_pos};
	else if (x_pos + playerWidth >= windWidth)
		_spriteData.position = { windWidth - playerWidth, y_pos };
}

void Player::UpdateBulletsBounds()
{
	for (auto it = _bullets.rbegin(); it != _bullets.rend(); )
		if ((*it)->GetPos().y < 0.f)
			it = decltype(it)(_bullets.erase(--it.base()));
		else
			++it;
}

void Player::UpdateHitbox()
{
	float scale = _spriteData.scale.x;

	float x_pos = _spriteData.position.x + 3.f * scale;
	float y_pos = _spriteData.position.y + 2.f * scale;

	_hitbox->Update(x_pos, y_pos);
}
