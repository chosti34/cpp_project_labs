#include "stdafx.h"
#include "Animation.h"
#include "Asteroid.h"

CAsteroid::CAsteroid()
{
    this->speed = 50;
    this->radius = 15;

    this->movement.x = static_cast<float>((rand() % 8) - 4);
    this->movement.y = static_cast<float>((rand() % 8) - 4);
}

void CAsteroid::Initialize(const sf::Texture &texture, const float screenWidth, const float screenHeight)
{
    this->isAlive = true;

    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    this->animation.SetAnimationProperties(texture, 16, 20);
    this->animation.Initialize(0, 0, 64, 64);
    this->animation.sprite.setScale(0.8f, 0.8f);

    this->position.x = static_cast<float>(rand() % static_cast<int>(this->screenWidth));
    this->position.y = static_cast<float>(rand() % static_cast<int>(this->screenHeight));
}

void CAsteroid::HandleOutOfScopes()
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

void CAsteroid::Update(const float elapsedTime)
{
    animation.Update(elapsedTime);

    HandleOutOfScopes();

    position.x += movement.x * speed * elapsedTime;
    position.y += movement.y * speed * elapsedTime;

    animation.sprite.setPosition(position);
}
