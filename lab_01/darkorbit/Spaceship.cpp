#include "stdafx.h"
#include "Animation.h"
#include "SpaceShip.h"

void SpaceShip::Initialize(const sf::Texture &texture, const float screenWidth, const float screenHeight)
{
    // pixels per second (?)
    this->translationalMotionSpeed = 70;
    // degrees per second (?)
    this->rotationalMotionSpeed = 120;

    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    this->angle = 0;
    this->isThrust = false;
    this->isAlive = true;
    this->radius = 30;

    this->score = 0;

    this->movement = {0, 0};
    this->position = {this->screenWidth / 2, this->screenHeight / 2};

    // Инициализация анимации
    this->animation_stay.SetAnimationProperties(texture, 1, 0);
    this->animation_stay.Initialize(0, 0, 190, 190);
    this->animation_stay.sprite.setScale(0.5, 0.5);

    this->animation_go.SetAnimationProperties(texture, 1, 0);
    this->animation_go.Initialize(190, 0, 190, 210);
    this->animation_go.sprite.setScale(0.5, 0.5);

    this->animation = animation_stay;
    this->animation.sprite.setPosition(position);
}

void SpaceShip::HandleOutOfScopes()
{
    if (position.x > screenWidth)
    {
        position.x = 0;
    }
    else if (position.x < 0)
    {
        position.x = screenWidth;
    }

    if (position.y > screenHeight)
    {
        position.y = 0;
    }
    else if (position.y < 0)
    {
        position.y = screenHeight;
    }
}

void SpaceShip::CalculateMovementVector(const float elapsedTime)
{
    // Если есть осевая нагрузка на корабль, то он его координаты изменяются в завимимости от направления оси (угла если смотреть сверху)
    // Иначе корабль медленно замедляется
    if (isThrust)
    {
        movement.x += cos(angle * M_PI / 180) * rotationalMotionSpeed * elapsedTime;
        movement.y += sin(angle * M_PI / 180) * rotationalMotionSpeed * elapsedTime;
    }
    else
    {
        movement.x *= 0.9;
        movement.y *= 0.9;
    }

    // Если скорость корабля выше заданной, тогда какой эффект ускорения/замедления
    float currentSpeed = sqrt((movement.x * movement.x) + (movement.y * movement.y));

    float maxSpeed = 15;

    if (currentSpeed > maxSpeed)
    {
        movement.x *= maxSpeed / currentSpeed;
        movement.y *= maxSpeed / currentSpeed;
    }
}

void SpaceShip::HandleKeyPress(const float elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        angle += rotationalMotionSpeed * elapsedTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        angle -= rotationalMotionSpeed * elapsedTime;
    }

    isThrust = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

    if (isThrust)
    {
        animation = animation_go;
    }
    else
    {
        animation = animation_stay;
    }
}

void SpaceShip::Update(const float elapsedTime)
{
    HandleKeyPress(elapsedTime);

    animation.Update();
    CalculateMovementVector(elapsedTime);
    HandleOutOfScopes();

    position.x += movement.x * translationalMotionSpeed * elapsedTime;
    position.y += movement.y * translationalMotionSpeed * elapsedTime;

    animation.sprite.setPosition(position);
    animation.sprite.setRotation(angle + 90);
}
