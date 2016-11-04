#include "stdafx.h"
#include "Animation.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "GameController.h"

#include <iostream>

GameController::GameController(const size_t screenWidth, const size_t screenHeight, const std::string &gameTitle)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->gameTitle = gameTitle;
}

void GameController::Initialize()
{
    window.create(sf::VideoMode(screenWidth, screenHeight), gameTitle, sf::Style::Close);
    window.setFramerateLimit(60);

    // Фон для игры
    backgroundTexture.loadFromFile("resources/images/background.png");
    background.setTexture(backgroundTexture);
    background.setScale(screenWidth / background.getLocalBounds().width, screenHeight / background.getLocalBounds().height);

    // Музыкальное сопровождение для игры
    music.openFromFile("resources/sounds/theme.wav");
    music.setLoop(true);
    music.play();

    // Инициализиция корабля
    spaceShipTexture.loadFromFile("resources/images/spaceship.png");
    spaceShipTexture.setSmooth(true);
    spaceShip.Initialize(spaceShipTexture, screenWidth, screenHeight);

    // Инициализация астероидов
    asteroidTexture.loadFromFile("resources/images/asteroid.png");
    asteroidTexture.setSmooth(true);
    size_t asteroidsAmount = 6;
    for (size_t i = 0; i < asteroidsAmount; ++i)
    {
        Asteroid *asteroid = new Asteroid;
        asteroid->Initialize(asteroidTexture, screenWidth, screenHeight);
        asteroids.push_back(asteroid);
    }

    // Инициализация лазеров
    laserTexture.loadFromFile("resources/images/laser.png");
    soundBuffer.loadFromFile("resources/sounds/laser.wav");
    sound.setBuffer(soundBuffer);

    // Шрифт
    font.loadFromFile("resources/fonts/monospace.ttf");
    text.setFillColor(sf::Color::Blue);
    text.setFont(font);
    text.setCharacterSize(30);
    text.setPosition(screenWidth - 200, 40);
}

void GameController::HandleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (spaceShip.isAlive)
        {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                sound.play();

                Bullet *bullet = new Bullet;
                bullet->Initialize(laserTexture, spaceShip.angle, spaceShip.position, screenWidth, screenHeight);
                bullets.push_back(bullet);
            }
        }
    }
}

void GameController::Update()
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();

    if (elapsedTime > 0.1)
    {
        // if we hold window active we need to stop the time in game (?)
        elapsedTime = 0.1;
    }

    spaceShip.Update(elapsedTime);

    text.setString("Score: " + std::to_string(spaceShip.score));

    // Обновляем хар-ки астероидов
    for (auto bullet = bullets.begin(); bullet != bullets.end();)
    {
        Bullet *bulletPtr = *bullet;
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

    for (auto asteroid = asteroids.begin(); asteroid != asteroids.end();)
    {
        Asteroid *asteroidPtr = *asteroid;

        // Столкновение астероида с кораблём
        /*if (spaceShip.animation.sprite.getGlobalBounds().intersects(asteroidPtr->animation.sprite.getGlobalBounds()))
        {
            spaceShip.isAlive = false;
        }*/

        if (IsCollide(spaceShip, *asteroidPtr))
        {
            spaceShip.isAlive = false;
        }

        asteroidPtr->Update(elapsedTime);

        for (auto bullet = bullets.begin(); bullet != bullets.end(); ++bullet)
        {
            Bullet *bulletPtr = *bullet;

            // Столкновение пули с астероидом
            /*if (bulletPtr->animation.sprite.getGlobalBounds().intersects(asteroidPtr->animation.sprite.getGlobalBounds()))
            {
                bulletPtr->isAlive = false;
                asteroidPtr->isAlive = false;
            }*/
            if (IsCollide(*bulletPtr, *asteroidPtr))
            {
                bulletPtr->isAlive = false;
                asteroidPtr->isAlive = false;
                ++spaceShip.score;
            }
        }

        if (!asteroidPtr->isAlive)
        {
            asteroid = asteroids.erase(asteroid);
            delete asteroidPtr;
        }
        else
        {
            asteroid++;
        }
    }

    if (rand() % 150 == 0)
    {
        Asteroid *asteroid = new Asteroid;
        asteroid->Initialize(asteroidTexture, screenWidth, screenHeight);
        asteroids.push_back(asteroid);
    }
}

void GameController::Render()
{
    window.draw(background);

    for (auto asteroid : asteroids)
    {
        window.draw(asteroid->animation.sprite);
    }
    for (auto bullet : bullets)
    {
        window.draw(bullet->animation.sprite);
    }
    window.draw(spaceShip.animation.sprite);
    window.draw(text);
    window.display();
}

void GameController::EnterMainLoop()
{
    while (window.isOpen())
    {
        if (spaceShip.isAlive)
        {
            HandleEvents();
            Update();
            Render();
        }
        else
        {
            HandleEvents();
            ProcessGameOver();
        }
    }
}

bool GameController::IsCollide(SpaceShip &ship, Asteroid &asteroid)
{
    int sx = ship.position.x;
    int sy = ship.position.y;
    int ax = asteroid.position.x;
    int ay = asteroid.position.y;
    int sr = ship.radius;
    int ar = asteroid.radius;

    return (ax - sx) * (ax - sx) + (ay - sy) * (ay - sy) < (sr + ar) * (sr + ar);
}

bool GameController::IsCollide(Bullet &bullet, Asteroid &asteroid)
{
    int bx = bullet.position.x;
    int by = bullet.position.y;
    int ax = asteroid.position.x;
    int ay = asteroid.position.y;
    int br = bullet.radius;
    int ar = asteroid.radius;

    return (ax - bx) * (ax - bx) + (ay - by) * (ay - by) < (br + ar) * (br + ar);
}

void GameController::ProcessGameOver()
{
    text.setString("Game Over! Score: " + std::to_string(spaceShip.score));
    text.setCharacterSize(60);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(screenWidth / 2, screenHeight / 2 - text.getGlobalBounds().height / 2);
    window.draw(background);
    window.draw(text);
    window.display();
}
