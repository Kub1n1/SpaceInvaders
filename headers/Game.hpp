#pragma once

#include "Time.hpp"
#include "GameManager.hpp"
#include "Player.hpp"
#include "Alien.hpp"
#include "Shield.hpp"

class Game
{
public:
	/* Constructors */
	Game();

	/* Destructors */
	virtual ~Game() = default;

	/* Core */
	void Run();
	void Update();
	void Render();

private:
	/* Initialization */
	void InitWindowSettings();
	void InitWindow();
	void InitTime();
	void InitSpriteManager();
	void InitGameManager();
	void InitPlayer();
	void InitEnemies();
	void InitScore();
	void InitPlayerHealth();
	void InitShields();

	/* Updates */
	void UpdateTime();
	void UpdateEvents();
	void UpdateMovement();
	void UpdateEntities();
	void UpdateEnemies();
	void UpdateEnemiesDrop(int validIndex);
	void UpdateEnemiesSpeed();
	void UpdateShooting();
	void UpdateRenderHitbox();
	void UpdatePlayerHits();
	void UpdateDefenseLine();
	void UpdateScore();
	void UpdateShields();
	void UpdateEnemiesBullets();
	void UpdateEnemiesBulletsBounds();
	void UpdateEnemiesHits();
	void UpdateGameState();

	/* Renders */
	void RenderPlayer();
	void RenderEnemies();
	void RenderHitboxes();
	void RenderTexts();
	void RenderHP();
	void RenderShields();
	void RenderShieldsArmor();
	void RenderEnemiesBullets();

	/* Reset */
	void ResetGame();
	void ResetBoard();
	void ResetEnemies();
	void ResetShields();
	
private:
	/* Variables */
	std::shared_ptr< sf::RenderWindow > _window;
	WindowSettings _windSett;
	sf::Event _event;
	Time _time;
	GameManager _gameManager;
	std::shared_ptr< SpriteManager > _spriteManager;
	std::shared_ptr < Player > _player;
	std::vector< std::vector< std::shared_ptr < Enemy > > > _enemies;
	std::vector< std::shared_ptr<Bullet> > _enemiesBullets;
	std::string _playerHPSprite;
	SpriteData _hpSpriteData;
	std::shared_ptr<sf::Font> _font;
	std::shared_ptr<sf::Text> _scoreText;
	std::shared_ptr<sf::Text> _healthText;
	std::shared_ptr<sf::Text> _shieldsArmor;
	std::shared_ptr<sf::Text> _mainMenuText;
	std::vector< std::shared_ptr< Shield > > _shields;
};