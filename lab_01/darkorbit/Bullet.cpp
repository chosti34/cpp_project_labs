#include "stdafx.h"
#include "Animation.h"
#include "Bullet.h"

Bullet::Bullet()
{
    // pixels per second
    this->speed = 1200;

    this->radius = 5;
}

void Bullet::Initialize(const sf::Texture &texture, const float angle, const sf::Vector2f &shipPosition, const float screenWidth, const float screenHeight)
{
    this->isAlive = true;
    this->angle = angle;

    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    this->animation.SetAnimationProperties(texture, 16, 20);
    this->animation.Initialize(0, 0, 32, 64);
    this->animation.sprite.setRotation(angle + 90);

    this->position = shipPosition;
}

void Bullet::HandleOutOfScopes()
{
    if ((position.x > screenWidth) || (position.x < 0))
    {
        isAlive = false;
    }

    if ((position.y > screenHeight) || (position.y < 0))
    {
        isAlive = false;
    }
}

void Bullet::Update(const float elapsedTime)
{
    animation.Update(elapsedTime);

    HandleOutOfScopes();

    movement.x = cos(angle * M_PI / 180);
    movement.y = sin(angle * M_PI / 180);

    position.x += movement.x * speed * elapsedTime;
    position.y += movement.y * speed * elapsedTime;

    animation.sprite.setPosition(position);
}
