#include "Game.hpp"

/* Constructors */
Game::Game()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	this->InitWindowSettings();
	this->InitWindow();
	this->InitTime();
	this->InitSpriteManager();
	this->InitGameManager();
	this->InitPlayer();
	this->InitEnemies();
	this->InitScore();
	this->InitPlayerHealth();
	this->InitShields();
}

/* Core */
void Game::Run()
{
	while (_window->isOpen())
	{
		this->Update();
		this->Render();
	
	}
}

void Game::Update()
{
	this->UpdateTime();
	this->UpdateEvents();
	this->UpdateMovement();
	this->UpdateEntities();
	this->UpdateShooting();
	this->UpdateRenderHitbox();
	this->UpdatePlayerHits();
	this->UpdateDefenseLine();
	this->UpdateScore();
	this->UpdateShields();
	this->UpdateEnemiesBullets();
	this->UpdateEnemiesHits();
	this->UpdateGameState();
}

void Game::Render()
{
	_window->clear();

	this->RenderPlayer();
	this->RenderEnemies();
	this->RenderTexts();
	this->RenderHP();
	this->RenderShields();
	this->RenderShieldsArmor();
	this->RenderEnemiesBullets();

	if (_gameManager.renderHitboxes)
		this->RenderHitboxes();
	
	_window->display();
}

/* Initialization */
void Game::InitWindowSettings()
{
	_windSett.resolution = sf::VideoMode(900, 800);
	_windSett.isFullscreen = false;
	_windSett.frameLimit = 120;
	_windSett.title = "Space Invaders";
}

void Game::InitWindow()
{
	_window = std::make_shared< sf::RenderWindow >(
		_windSett.resolution, _windSett.title, 
		sf::Style::Titlebar | sf::Style::Close
	);
	_window->setFramerateLimit(_windSett.frameLimit);
}

void Game::InitTime()
{
	_time.deltaTime = 0.f;
	_time.enemyMoveTime = .1f;
	_time.enemyMoveTimer = 0.f;
	_time.playerShootTime = .2f;
	_time.playerShootTimer = _time.playerShootTime;
	_time.hitboxViewTime = .1f;
	_time.hitboxViewTimer = _time.hitboxViewTime;
	_time.enemiesShootTime = .1f;
	_time.enemiesShootTimer = 0.f;
}

void Game::InitSpriteManager()
{
	_spriteManager = std::make_shared<SpriteManager>();
	_gameManager.renderHitboxes = false;
}

void Game::InitGameManager()
{
	_gameManager.baseEnemies = 0;
	_gameManager.currentEnemies = 0;
	_gameManager.defeatedEnemies = 0;
	_gameManager.dropEnemies = false;
	_gameManager.renderHitboxes = false;
	_gameManager.score = 0;
	_gameManager.defenseLinePosition = _windSett.resolution.height * .8f;
}

void Game::InitPlayer()
{
	_player = std::make_shared<Player>( _window, _spriteManager );

	float windWidth = static_cast<float>( _window->getSize().x );
	float windHeight = static_cast<float>( _window->getSize().y );

	float plWidth = _player->GetSize().x;
	float plHeight = _player->GetSize().y;

	float x_0 = ( windWidth / 2.f ) - (plWidth / 2);
	float y_0 = ( windHeight * .92f);

	_player->SetPos(x_0, y_0);

	_playerHPSprite = "HP_0";
	std::string texturePath{ "assets/sprites/player/HP_0.png" };

	_spriteManager->LoadSprite(texturePath, _playerHPSprite);
	float scale = 3.f;
	_hpSpriteData.scale.x = scale;
	_hpSpriteData.scale.y = scale;
	_hpSpriteData.size = _spriteManager->GetSpriteSize(_playerHPSprite);
	_hpSpriteData.position = { _windSett.resolution.width * .04f , _windSett.resolution.height * .02f };
}

void Game::InitEnemies()
{
	_gameManager.dropEnemies = true;

	int enemiesInRow = 11;
	int rows = 5;

	_gameManager.baseEnemies = enemiesInRow * rows;
	_gameManager.currentEnemies = _gameManager.baseEnemies;

	float windWidth = static_cast<float>(_window->getSize().x);
	float windHeight = static_cast<float>(_window->getSize().y);

	Alien tmpAlien(_window, _spriteManager);

	float alWidth = tmpAlien.GetSize().x;
	float alHeight = tmpAlien.GetSize().y;

	float widthSeparator = alWidth * 3.f;
	float heightSeparator = alHeight * 3.f;

	for (int i{}; i < rows; i++)
	{
		float y_0 = windHeight * 0.1f + (i * heightSeparator);

		_enemies.emplace_back();

		for (int j{}; j < enemiesInRow; j++)
		{
			float x_0 = (j + 1) * widthSeparator + (j * alWidth);

			_enemies.at(i).push_back( std::make_shared<Alien>( _window, _spriteManager ) );
			_enemies.at(i).at(j)->SetPos( x_0, y_0 );
		}
	}
}

void Game::InitScore()
{
	_font = std::make_shared<sf::Font>();

	if (!_font->loadFromFile("assets/fonts/orange_juice.ttf"))
		throw "ERROR::INIT_SCORE::FILE_NOT_OPENED";

	_scoreText = std::make_shared<sf::Text>();
	_scoreText->setFont(*_font);
	_scoreText->setString( "Score: " + std::to_string(_gameManager.score));
	_scoreText->setCharacterSize(40);
	_scoreText->setFillColor(sf::Color::White);

	float x_pos = _windSett.resolution.width * .33f;
	float y_pos = _windSett.resolution.height * .02f;

	_scoreText->setPosition(x_pos, y_pos);
}

void Game::InitPlayerHealth()
{
	_healthText = std::make_shared<sf::Text>();
	_healthText->setFont(*_font);
	_healthText->setString("HP: ");
	_healthText->setCharacterSize(40);
	_healthText->setFillColor(sf::Color::White);

	float x_pos = _windSett.resolution.width * .02f;
	float y_pos = _windSett.resolution.height * .02f;

	_healthText->setPosition(x_pos, y_pos);
}

void Game::InitShields()
{
	sf::Vector2f startPosition;

	startPosition.x = _windSett.resolution.width * .05f;
	startPosition.y = _windSett.resolution.height * .8f;

	int shieldsNumber{ 5 };

	for (int i{}; i < shieldsNumber; i++)
	{
		_shields.push_back(
			std::make_shared< Shield >(
				_window, _spriteManager, startPosition
			)
		);

		startPosition.x += (_windSett.resolution.width * .1f) * 2.f ;
	}

	_shieldsArmor = std::make_shared<sf::Text>();
	_shieldsArmor->setFont(*_font);
	_shieldsArmor->setCharacterSize(30);
	_shieldsArmor->setFillColor(sf::Color::Black);
}

/* Updates */
void Game::UpdateTime()
{
	_time.deltaTime = _time.clock.restart().asSeconds();
	_time.enemyMoveTimer += _time.deltaTime;
	_time.playerShootTimer += _time.deltaTime;
	_time.hitboxViewTimer += _time.deltaTime;
	_time.enemiesShootTimer += _time.deltaTime;
}

void Game::UpdateEvents()
{
	while ( _window->pollEvent( _event ))
	{
		if (_event.type == sf::Event::Closed)
			_window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window->close();
	}
}

void Game::UpdateMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_player->Move(-1.f, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_player->Move(1.f, 0.f);
	else
		_player->Move(0.f, 0.f);

	if (_time.enemyMoveTimer >= _time.enemyMoveTime)
	{
		if (_enemies.empty())
			return;

		for (size_t i{}; i < _enemies.size(); i++)
			for (size_t j{}; j < _enemies.at(i).size(); j++)
				_enemies.at(i).at(j)->Move();

		_time.enemyMoveTimer = 0.f;
	}

}

void Game::UpdateEntities()
{
	_player->Update( _time.deltaTime );

	this->UpdateEnemies();
	
}

void Game::UpdateEnemies()
{
	if (_gameManager.currentEnemies <= 0)
		this->ResetBoard();

	if (_enemies.empty())
		return;

	int validIndex{ -1 };

	for (size_t i{}; i < _enemies.size(); i++)
	{
		if (!_enemies.at(i).empty())
		{
			validIndex = static_cast<int>(i);
			break;
		}
	}

	if (validIndex < 0)
		return;

	this->UpdateEnemiesDrop(validIndex);
	this->UpdateEnemiesSpeed();

	int enemiesRows{ static_cast<int>(_enemies.size() - 1) };
	int enemiesCols{};

	for (int i{ enemiesRows }; i >= 0; i--)
	{
		enemiesCols = static_cast<int>(_enemies.at(i).size() - 1);
		for (int j{ enemiesCols }; j >= 0; j--)
		{
			_enemies.at(i).at(j)->Update(_time.deltaTime);
		}
	}

	
}

void Game::UpdateEnemiesDrop(int validIndex)
{
	if (_enemies.at(validIndex).back()->IsRight() != _gameManager.dropEnemies)
	{
		for (size_t i{}; i < _enemies.size(); i++)
			for (size_t j{}; j < _enemies.at(i).size(); j++)
				_enemies.at(i).at(j)->Drop(_time.deltaTime);

		_gameManager.dropEnemies = _enemies.at(validIndex).back()->IsRight();
	}
}

void Game::UpdateEnemiesSpeed()
{
	int delta{ static_cast<int>( _gameManager.baseEnemies * .1f ) };

	if ( _gameManager.defeatedEnemies >= delta)
	{
		int enemiesRows{ static_cast<int>(_enemies.size() - 1) };
		int enemiesCols{};

		for (int i{ enemiesRows }; i >= 0; i--)
		{
			enemiesCols = static_cast<int>(_enemies.at(i).size() - 1);
			for (int j{ enemiesCols }; j >= 0; j--)
			{
				_enemies.at(i).at(j)->SpeedUp();
			}
		}

		_gameManager.defeatedEnemies = 0;
	}
}

void Game::UpdateShooting()
{
	if ( _time.playerShootTimer >= _time.playerShootTime )
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			_player->Shoot();

		_time.playerShootTimer = 0.f;
	}

	if (_time.enemiesShootTimer >= _time.enemiesShootTime)
	{
		for (size_t i{}; i < _enemies.size(); i++)
		{
			for (size_t j{}; j < _enemies.at(i).size(); j++)
			{
				float probability = .001f;
				float randomValue = static_cast<float>(std::rand()) / RAND_MAX;
				if (randomValue < probability)
				{
					_enemies.at(i).at(j)->Shoot(_enemiesBullets);
					break;
				}
			}
		}

		_time.enemiesShootTimer = 0.f;
	}
}

void Game::UpdateRenderHitbox()
{
	if (_time.hitboxViewTimer >= _time.hitboxViewTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			if (_gameManager.renderHitboxes)
				_gameManager.renderHitboxes = false;
			else
				_gameManager.renderHitboxes = true;
		}

		_time.hitboxViewTimer = 0.f;
	}
}

void Game::UpdatePlayerHits()
{
	if (_enemies.empty())
		return;

	int lastEnemyColIndex{}, lastEnemyRowIndex{ static_cast<int>( _enemies.size() - 1 )};
	for (int i{ lastEnemyRowIndex }; i >= 0; i--)
	{
		lastEnemyColIndex = static_cast<int>(_enemies.at(i).size() - 1);
		for (int j{ lastEnemyColIndex }; j >= 0; j--)
		{
			if ( _player->CheckForHits( _enemies.at(i).at(j)->GetRect() ) )
			{
				_gameManager.score += _enemies.at(i).at(j)->GiveScoreForDestroy();
				_enemies.at(i).erase(_enemies.at(i).begin() + j);
				_gameManager.defeatedEnemies++;
				_gameManager.currentEnemies--;
			}
		}
	}

	int lastShieldsIndex{ static_cast<int>(_shields.size()) - 1 };
	for (int i{ lastShieldsIndex }; i >= 0; i--)
	{
		if (_player->CheckForHits(_shields.at(i)->GetRect()))
			_shields.at(i)->ReduceArmor();
	}
}

void Game::UpdateDefenseLine()
{
	int validIndex{ -1 };

	for (int i{ static_cast<int>(_enemies.size() - 1) }; i >= 0; i--)
	{
		if (!_enemies.at(i).empty())
		{
			validIndex = i;
			break;
		}
	}

	if (validIndex < 0)
		return;

	float y_pos = _enemies.at(validIndex).back()->GetPos().y + _enemies.at(validIndex).back()->GetSize().y * _enemies.at(validIndex).back()->GetScale().y;

	if (y_pos >= _gameManager.defenseLinePosition)
		this->ResetGame();
}

void Game::UpdateScore()
{
	_scoreText->setString( "Score: " + std::to_string(_gameManager.score) );
}

void Game::UpdateShields()
{
	int lastShieldsIndex{ static_cast<int>(_shields.size()) - 1 };
	for (int i{ lastShieldsIndex }; i >= 0; i--)
	{
		if (_shields.at(i)->GetArmor().armor <= 0)
			_shields.erase(_shields.begin() + i);
	}
}

void Game::UpdateEnemiesBullets()
{
	if (!_enemiesBullets.empty())
	{
		this->UpdateEnemiesBulletsBounds();
		for (const auto& bullet : _enemiesBullets)
			bullet->Update(_time.deltaTime);
	}
}

void Game::UpdateEnemiesBulletsBounds()
{
	int size = static_cast<int>( _enemiesBullets.size() );
	for (int i{ size - 1 }; i > 0; i--)
		if (_enemiesBullets.at(i)->GetPos().y > _windSett.resolution.height)
			_enemiesBullets.erase(_enemiesBullets.begin() + i);
}

void Game::UpdateEnemiesHits()
{
	int size = static_cast<int>(_enemiesBullets.size());
	for (int i{ size - 1 }; i >= 0; i--)
	{
		if ( _enemiesBullets.at(i)->CheckHit( _player->GiveRect() ) )
		{
			_enemiesBullets.erase(_enemiesBullets.begin() + i);
			_player->TakeDamage();
		}
		
	}

	int size1 = static_cast<int>(_enemiesBullets.size());
	for (int i{ size1 - 1 }; i >= 0; i--)
	{
		int lastShieldsIndex{ static_cast<int>( _shields.size()) };
		for (int j{ lastShieldsIndex - 1}; j >= 0; j--)
		{
			if (_enemiesBullets.at(i)->CheckHit(_shields.at(j)->GetRect()))
			{
				_enemiesBullets.erase(_enemiesBullets.begin() + i);
				_shields.at(j)->ReduceArmor();
				break;
			}
		}
	}
}

void Game::UpdateGameState()
{
	if (_player->GiveHealth().hp <= 0)
		this->ResetGame();
}

/* Renders */
void Game::RenderPlayer()
{
	_player->Render(_window);
}

void Game::RenderEnemies()
{
	if (_enemies.empty())
		return;

	for (size_t i{}; i < _enemies.size(); i++)
		for (size_t j{}; j < _enemies.at(i).size(); j++)
			_enemies.at(i).at(j)->Render( _window );
}

void Game::RenderHitboxes()
{
	_player->RenderHitbox();

	if (_enemies.empty())
		return;

	for (size_t i{}; i < _enemies.size(); i++)
		for (size_t j{}; j < _enemies.at(i).size(); j++)
			_enemies.at(i).at(j)->RenderHitbox();

	for (const auto& shield : _shields)
		shield->RenderHitbox();
}

void Game::RenderTexts()
{
	_window->draw(*_scoreText);
	_window->draw(*_healthText);
	this->RenderShieldsArmor();
}

void Game::RenderHP()
{
	float x = _windSett.resolution.width * .1f;
	float y = _windSett.resolution.height * .02f;

	for (int i{}; i < _player->GiveHealth().hp; i++)
	{
		_hpSpriteData.position = { x, y };
		x += .1f + _hpSpriteData.size.x * _hpSpriteData.scale.x;
		_spriteManager->RenderSprite(_playerHPSprite, _hpSpriteData, _window);
	}
}

void Game::RenderShields()
{
	for (const auto& shield : _shields)
		shield->Render(_window);
}

void Game::RenderShieldsArmor()
{
	for (const auto& shield : _shields)
	{
		std::string tmp{
			std::to_string(shield->GetArmor().armor) + "/" +
			std::to_string(shield->GetArmor().maxArmor)
		};

		_shieldsArmor->setString(tmp);

		float x = shield->GetPos().x + shield->GetSize().x * .6f;
		float y = shield->GetPos().y + shield->GetSize().y * .9f;

		_shieldsArmor->setPosition(x, y);
		_window->draw(*_shieldsArmor);
	}
}

void Game::RenderEnemiesBullets()
{
	for (const auto& bullet : _enemiesBullets)
		bullet->Render(_window);
}

/* Reset */
void Game::ResetGame()
{
	_player->ResetHealth();
	_gameManager.score = 0;

	this->ResetEnemies();
	this->ResetShields();
}

void Game::ResetBoard()
{
	this->ResetEnemies();
}

void Game::ResetEnemies()
{
	if (!_enemies.empty())
		_enemies.clear();

	this->InitEnemies();
}

void Game::ResetShields()
{
	if (!_shields.empty())
		_shields.clear();

	this->InitShields();
}