#include "stdafx.h"

#include "Spaceship.h"

#include <iostream>

void CSpaceShip::Initialize()
{
    this->texture.loadFromFile("resources/images/spaceship.png");

    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.5, 0.5);
    this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);

    this->sprite.setPosition(1280 / 2, 720 / 2);

    this->dx = 0;
    this->dy = 0;

    x = 1280 / 2; y = 720 / 2;

    this->angle = 0;

    this->isThrust = false;
}
