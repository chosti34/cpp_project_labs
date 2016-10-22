#include "stdafx.h"
#include "Spaceship.h"

void SpaceShip::Initialize(const size_t screenWidth, const size_t screenHeight)
{
    this->gameScreenHeight = screenHeight;
    this->gameScreenWidth = screenWidth;

    texture.loadFromFile("resources/images/spaceship.png");

    texture.setSmooth(true);

    sprite.setTexture(this->texture);
    sprite.setScale(0.5, 0.5);
    sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);

    // перемещаем координаты спрайта в центр экрана
    sprite.setPosition(gameScreenWidth / 2, gameScreenHeight / 2);

    movement.x = 0;
    movement.y = 0;

    // перемещаем координаты (еще не связаны со спрайтом) корабля в центр экрана
    position.x = gameScreenWidth / 2;
    position.y = gameScreenHeight / 2;

    angle = 0;

    isThrust = false;
}

void SpaceShip::CalculateMovementVector()
{
    if (isThrust)
    {
        movement.x += cos(angle * 3.14 / 180);
        movement.y += sin(angle * 3.14 / 180);
    }
    else
    {
        movement.x *= 0.9;
        movement.y *= 0.9;
    }

    int maxSpeed = 15;

    float speed = sqrt((movement.x * movement.x) + (movement.y * movement.y));

    if (speed > maxSpeed)
    {
        movement.x *= maxSpeed / speed;
        movement.y *= maxSpeed / speed;
    }
}
