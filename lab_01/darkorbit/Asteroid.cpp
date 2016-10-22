#include "stdafx.h"
#include "Asteroid.h"

void Asteroid::Initialize(int x, int y, float angle, int radius)
{
    //this->animation = rockAnimation;
    this->position.x = x;
    this->position.y = y;
    this->angle = angle;
    this->radius = radius;

    movement.x = rand() % 8 - 4;
    movement.y = rand() % 8 - 4;
}

void Asteroid::Update()
{
    //this->animation.Update();

    position.x += movement.x;
    position.y += movement.y;

    if (position.x > 1280) position.x = 0;  if (position.x < 0) position.x = 1280;
    if (position.y > 768) position.y = 0;  if (position.y < 0) position.y = 768;

    animation.sprite.setPosition(position);
    animation.sprite.setRotation(angle + 90);

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(255,0,0,170));
    circle.setPosition(position);
    circle.setOrigin(radius, radius);
}

void Asteroid::Draw(sf::RenderWindow &window)
{
    window.draw(this->animation.sprite);
}
