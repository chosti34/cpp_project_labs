#pragma once

class CSpaceShip
{
public:
    sf::Texture texture;
    sf::Sprite sprite;

    float dx;
    float dy;

    float x, y;

    float angle;

    bool isThrust;

    void Initialize();
};
