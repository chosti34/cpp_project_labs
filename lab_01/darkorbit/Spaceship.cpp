#include "stdafx.h"
#include "Animation.h"
#include "SpaceShip.h"

void CSpaceShip::Initialize(const sf::Texture &texture, const float screenWidth, const float screenHeight)
{
    this->translationalMotionSpeed = 70;
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

    this->animation_stay.SetAnimationProperties(texture, 1, 0);
    this->animation_stay.Initialize(0, 0, 190, 190);
    this->animation_stay.sprite.setScale(0.5, 0.5);

    this->animation_go.SetAnimationProperties(texture, 1, 0);
    this->animation_go.Initialize(190, 0, 190, 210);
    this->animation_go.sprite.setScale(0.5, 0.5);

    this->animation = animation_stay;
    this->animation.sprite.setPosition(position);
}

void CSpaceShip::HandleOutOfScopes()
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

void CSpaceShip::CalculateMovementVector(const float elapsedTime)
{
    if (isThrust)
    {
        movement.x += static_cast<float>(cos(angle * M_PI / 180) * rotationalMotionSpeed * elapsedTime);
        movement.y += static_cast<float>(sin(angle * M_PI / 180) * rotationalMotionSpeed * elapsedTime);
    }
    else
    {
        movement.x *= 0.9f;
        movement.y *= 0.9f;
    }

    float currentSpeed = sqrt((movement.x * movement.x) + (movement.y * movement.y));

    float maxSpeed = 15;

    if (currentSpeed > maxSpeed)
    {
        movement *= maxSpeed / currentSpeed;
    }
}

void CSpaceShip::HandleKeyPress(const float elapsedTime)
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

void CSpaceShip::Update(const float elapsedTime)
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
