#pragma once

class SpaceShip
{
public:
    sf::Sprite sprite;

    sf::Vector2f movement;
    sf::Vector2f position;

    float angle;

    bool isThrust;

    void Initialize(const size_t screenWidth, const size_t screenHeight);
    void CalculateMovementVector();
private:
    sf::Texture texture;

    size_t gameScreenWidth;
    size_t gameScreenHeight;
};
