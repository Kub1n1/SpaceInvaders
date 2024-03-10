#include "Enemy.hpp"

bool Enemy::_goRight = true;
bool Enemy::_goDown = false;

/* Constructor */
Enemy::Enemy(
	std::shared_ptr<sf::RenderWindow> window,
	std::shared_ptr< SpriteManager > spriteManager
)
	:Entity{window, spriteManager}
{
	_move = false;
	this->InitMoveComponent();
}

/* Core */
void Enemy::Update(const float dt)
{
	this->UpdateMovement(dt);
	this->UpdateBounds();
	this->UpdatePosition();
}

void Enemy::Move()
{
	_move = true;
}

void Enemy::Drop(const float dt)
{
	_moveComp.velocity.y = _moveComp.acceleration.y * dt;
}

void Enemy::SpeedUp()
{
	float speedUp{ 150.f };
	_moveComp.acceleration.x += speedUp;
}

void Enemy::Shoot(
	std::vector< std::shared_ptr<Bullet> >& enemiesBullets
)
{
	enemiesBullets.push_back(std::make_shared<Bullet>(_window, _spriteManager));

	float x_pos = _spriteData.position.x;
	float y_pos = _spriteData.position.y;

	enemiesBullets.back()->SetPos(x_pos, y_pos);
	enemiesBullets.back()->ChangeDirection();
}

/* Getters */
bool Enemy::IsRight() const
{
	return _goRight;
}

bool Enemy::GoDown() const
{
	return _goDown;
}

/* Initialization */
void Enemy::InitMoveComponent()
{
	_score = 0;

	_moveComp.acceleration.x = 400.f;
	_moveComp.acceleration.y = 3000.f;
}

/* Updates */
void Enemy::UpdateMovement(const float dt)
{
	if (!_move)
		return;

	if (_goRight)
		_moveComp.velocity.x = _moveComp.acceleration.x * dt;
	else
		_moveComp.velocity.x = -_moveComp.acceleration.x * dt;

	_move = false;
}

void Enemy::UpdatePosition()
{
	_spriteData.position += _moveComp.velocity;
	_moveComp.velocity.x = 0.f;
	_moveComp.velocity.y = 0.f;
}

void Enemy::UpdateBounds()
{
	float windWidth = static_cast<float>(_window->getSize().x);
	float windHeight = static_cast<float>(_window->getSize().y);

	float x_pos = _spriteData.position.x;
	float y_pos = _spriteData.position.y;

	float scale = _spriteData.scale.x;

	float alienWidth = _spriteData.size.x * scale;
	float alienHeight = _spriteData.size.y * scale;

	if (x_pos <= 0.f)
	{
		_goRight = true;
		_goDown = true;
	}
	else if (x_pos + alienWidth >= windWidth)
	{
		_goRight = false;
		_goDown = true;
	}
}
