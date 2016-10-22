#include "stdafx.h"
#include "AnimationController.h"
#include "spaceship.h"
#include "Asteroid.h"
#include "AppController.h"
#include <iostream>

void AppController::Initialize()
{
    window.create(sf::VideoMode(screenWidth, screenHeight), title);
    window.setFramerateLimit(60);

    ship.Initialize(screenWidth, screenHeight);

    // инициализация камней
    /*for (size_t i = 0; i < 5; ++i)
    {
        Asteroid *asteroid = new Asteroid();
        asteroid->Initialize(rand() % screenWidth, rand() % screenHeight, rand() % 360, 15);
        asteroids.push_back(asteroid);
    }*/

    sf::Texture asteroidTexture;
    asteroidTexture.loadFromFile("resources/images/rock.png");

    AnimationController asteroidAnimation(asteroidTexture, 20, 0, 30, 30, 8, 0.2);
    asteroidAnimation.sprite.setPosition(300, 400);
}

void AppController::HandleEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void AppController::Render()
{
    window.clear(sf::Color::Black);
    window.draw(ship.sprite);
    window.draw(asteroidAnimation.sprite);
    window.display();
}

void AppController::HandleKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship.angle += 3;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ship.angle -= 3;
    }

    ship.isThrust = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
}

void AppController::CheckScopes()
{
    if (ship.position.x > screenWidth)
    {
        ship.position.x = 0;
    }
    else if (ship.position.x < 0)
    {
        ship.position.x = screenWidth;
    }

    if (ship.position.y > screenHeight)
    {
        ship.position.y = 0;
    }
    else if (ship.position.y < 0)
    {
        ship.position.y = screenHeight;
    }
}

void AppController::Update()
{
    asteroidAnimation.Update();

    HandleKeyboard();

    ship.CalculateMovementVector();
    ship.position.x += ship.movement.x;
    ship.position.y += ship.movement.y;

    CheckScopes();

    ship.sprite.setPosition(ship.position);

    // здесь угол используется только для визуального отображения корабля
    ship.sprite.setRotation(ship.angle + 90);
}

void AppController::EnterMainLoop()
{
    while (window.isOpen())
    {
        HandleEvents();
        Update();
        Render();
    }
}
