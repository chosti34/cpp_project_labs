#pragma once

#include "AnimationController.h"

class Asteroid
{
public:

    sf::Vector2f position;
    sf::Vector2f movement;

    float radius;

    float angle;

    bool isAlive;
    std::string name;
    AnimationController animation;

    void Initialize(int x, int y, float angle, int radius);
    void Update();
    void Draw(sf::RenderWindow &window);
};
