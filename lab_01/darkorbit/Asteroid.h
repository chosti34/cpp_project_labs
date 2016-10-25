#pragma once

class Asteroid
{
public:
    Asteroid();

    Animation animation;

    float speed;
    bool isAlive;

    sf::Vector2f position;
    sf::Vector2f movement;

    void Initialize(const sf::Texture &texture, const float screenWidth, const float screenHeight);
    void Update(const float elapsedTime);
private:
    float screenWidth;
    float screenHeight;

    void HandleOutOfScopes();
};
