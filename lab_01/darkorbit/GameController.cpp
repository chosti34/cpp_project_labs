#include "stdafx.h"
#include "Animation.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "GameController.h"

CGameController::CGameController(const float screenWidth, const float screenHeight, const std::string &gameTitle)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->gameTitle = gameTitle;
}

void CGameController::Initialize()
{
    window.create(sf::VideoMode(static_cast<size_t>(screenWidth), static_cast<size_t>(screenHeight)), gameTitle, sf::Style::Close);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    LoadBackground();
    LoadMusic();
    LoadFonts();

    InitializeShip();
    InitializeAsteroids();
}

void CGameController::LoadBackground()
{
    backgroundTexture.loadFromFile("resources/images/background.png");
    background.setTexture(backgroundTexture);
    background.setScale(screenWidth / background.getLocalBounds().width, screenHeight / background.getLocalBounds().height);
}

void CGameController::LoadMusic()
{
    music.openFromFile("resources/sounds/theme.wav");
    music.setLoop(true);
    music.play();

    laserTexture.loadFromFile("resources/images/laser.png");
    soundBuffer.loadFromFile("resources/sounds/laser.wav");
    sound.setBuffer(soundBuffer);
}

void CGameController::LoadFonts()
{
    font.loadFromFile("resources/fonts/monospace.ttf");
    text.setFillColor(sf::Color::Green);
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setOutlineColor(sf::Color::Magenta);
    text.setOutlineThickness(2);
    text.setCharacterSize(30);
}

void CGameController::InitializeShip()
{
    spaceShipTexture.loadFromFile("resources/images/spaceship.png");
    spaceShipTexture.setSmooth(true);
    spaceShip.Initialize(spaceShipTexture, screenWidth, screenHeight);
}

void CGameController::InitializeAsteroids()
{
    asteroidTexture.loadFromFile("resources/images/asteroid.png");
    asteroidTexture.setSmooth(true);

    for (size_t i = 0; i < 6; ++i)
    {
        CAsteroid *asteroid = new CAsteroid;
        asteroid->Initialize(asteroidTexture, screenWidth, screenHeight);
        asteroids.push_back(asteroid);
    }
}

void CGameController::HandleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if ((spaceShip.isAlive) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
        {
            ShootBullet();
        }
        if ((!m_isPlaying) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
        {
            InitializeShip();
            InitializeAsteroids();
            m_isPlaying = true;
        }
    }
}

void CGameController::Update()
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();

    if (elapsedTime > 0.1)
    {
        elapsedTime = 0.1f;
    }

    spaceShip.Update(elapsedTime);
    UpdateBullets(elapsedTime);
    UpdateAsteroids(elapsedTime);

    text.setOrigin(text.getGlobalBounds().width, text.getGlobalBounds().height);
    text.setCharacterSize(30);
    text.setPosition(screenWidth - 25, 40);
    text.setString("Score: " + std::to_string(spaceShip.score));
}

void CGameController::UpdateBullets(const float elapsedTime)
{
    for (auto bullet = bullets.begin(); bullet != bullets.end();)
    {
        CBullet *bulletPtr = *bullet;
        bulletPtr->Update(elapsedTime);

        if (!bulletPtr->isAlive)
        {
            bullet = bullets.erase(bullet);
            delete bulletPtr;
        }
        else
        {
            bullet++;
        }
    }
}

void CGameController::ShootBullet()
{
    sound.play();
    CBullet *bullet = new CBullet;
    bullet->Initialize(laserTexture, spaceShip.angle, spaceShip.position, screenWidth, screenHeight);
    bullets.push_back(bullet);
}

void CGameController::UpdateAsteroids(const float elapsedTime)
{
    for (auto asteroid = asteroids.begin(); asteroid != asteroids.end();)
    {
        CAsteroid *asteroidPtr = *asteroid;
        if (IsShipCollidesWithAsteroid(spaceShip, *asteroidPtr))
        {
            spaceShip.isAlive = false;
            m_isPlaying = false;
            asteroids.clear();
            bullets.clear();
            break;
        }
        asteroidPtr->Update(elapsedTime);
        for (auto bullet = bullets.begin(); bullet != bullets.end(); ++bullet)
        {
            CBullet *bulletPtr = *bullet;
            if (IsBulletCollidesWithAsteroid(*bulletPtr, *asteroidPtr))
            {
                bulletPtr->isAlive = false;
                asteroidPtr->isAlive = false;
            }
        }
        if (!asteroidPtr->isAlive)
        {
            asteroid = asteroids.erase(asteroid);
            delete asteroidPtr;
            ++spaceShip.score;
        }
        else
        {
            asteroid++;
        }
    }

    if (rand() % 150 == 0)
    {
        CAsteroid *asteroid = new CAsteroid;
        asteroid->Initialize(asteroidTexture, screenWidth, screenHeight);
        asteroids.push_back(asteroid);
    }
}

void CGameController::DrawAsteroids()
{
    for (auto asteroid : asteroids)
    {
        window.draw(asteroid->animation.sprite);
    }
}

void CGameController::DrawBullets()
{
    for (auto bullet : bullets)
    {
        window.draw(bullet->animation.sprite);
    }
}

void CGameController::Render()
{
    window.draw(background);
    DrawAsteroids();
    DrawBullets();
    window.draw(spaceShip.animation.sprite);
    window.draw(text);
    window.display();
}

void CGameController::EnterMainLoop()
{
    while (window.isOpen())
    {
        HandleEvents();

        if (m_isPlaying)
        {
            Update();
            Render();
        }
        else
        {
            ProcessGameEnd();
        }
    }
}

void CGameController::ProcessGameEnd()
{
    text.setString("Score: " + std::to_string(spaceShip.score) + "\nPress space\nto restart");
    text.setCharacterSize(60);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(screenWidth / 2, screenHeight / 2 - text.getGlobalBounds().height / 2 + 50);
    window.draw(background);
    window.draw(text);
    window.display();
}

bool CGameController::IsShipCollidesWithAsteroid(CSpaceShip &ship, CAsteroid &asteroid)
{
    return ((asteroid.position.x - ship.position.x) * (asteroid.position.x - ship.position.x) +
            (asteroid.position.y - ship.position.y) * (asteroid.position.y - ship.position.y) <
            (ship.radius + asteroid.radius) * (ship.radius + asteroid.radius));
}

bool CGameController::IsBulletCollidesWithAsteroid(CBullet &bullet, CAsteroid &asteroid)
{
    return ((asteroid.position.x - bullet.position.x) * (asteroid.position.x - bullet.position.x) +
            (asteroid.position.y - bullet.position.y) * (asteroid.position.y - bullet.position.y) <
            (bullet.radius + asteroid.radius) * (bullet.radius + asteroid.radius));
}
