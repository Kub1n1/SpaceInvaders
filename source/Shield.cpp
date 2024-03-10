#include "Shield.hpp"

/* Constructors */
Shield::Shield(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SpriteManager> spriteManager, sf::Vector2f startPosition)
	: Object{ window, spriteManager }
{
	this->InitSprites();
	this->InitHitbox();
	this->InitStartPosition(startPosition);
	this->InitArmor();
}

/* Core */
void Shield::Update(const float dt)
{

}

void Shield::Render(std::shared_ptr<sf::RenderTarget> target = nullptr)
{
	if (target == nullptr)
		target = _window;

	_spriteManager->RenderSprite(
		_currentSprite, _spriteData, target
	);
}

void Shield::RenderHitbox()
{
	_hitbox->Render(_window);
}

void Shield::ReduceArmor()
{
	_armor.armor--;
}

std::shared_ptr<sf::FloatRect> Shield::GetRect()
{
	return _hitbox->GetRect();
}

Armor Shield::GetArmor() const
{
	return _armor;
}

/* Initialization */
void Shield::InitSprites()
{
	std::string spriteName{ "shield_0" };
	std::string texturePath{ "assets/sprites/shield/shield_0.png" };

	_spriteManager->LoadSprite(
		texturePath, spriteName
	);

	_currentSprite = spriteName;

	float scale = 5.f;
	_spriteData.scale.x = scale;
	_spriteData.scale.y = scale;
	_spriteData.size = _spriteManager->GetSpriteSize(_currentSprite);
}

void Shield::InitHitbox()
{
	std::ifstream ifs;
	ifs.open("assets/sprites/shield/shield_0.sprite");

	if (!ifs.is_open())
		throw "ERROR::SHIELD::INIT_HITBOX::FILE_NOT_OPENED";

	float width{}, height{}, x{}, y{};

	std::string value{};
	while ( ifs >> value )
	{
		if (value == "width")
			ifs >> width;
		else if (value == "height")
			ifs >> height;
		else if (value == "x")
			ifs >> x;
		else if (value == "y")
			ifs >> y;
	}

	ifs.close();

	float scale{ _spriteData.scale.x };

	_hitbox = std::make_shared<Hitbox>(
		x * scale, y * scale,
		width * scale, height * scale
	);
}

void Shield::InitStartPosition(sf::Vector2f startPosition)
{
	_spriteData.position = startPosition;
	_hitbox->Update(startPosition.x + 5.f, startPosition.y + 10.f);
}

void Shield::InitArmor()
{
	_armor.maxArmor = 10;
	_armor.armor = _armor.maxArmor;
}
