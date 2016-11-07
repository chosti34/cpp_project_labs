#pragma once

class CBullet
{
public:
    CBullet();

    CAnimation animation;

    float speed;
    float angle;
    float radius;

    bool isAlive;

    sf::Vector2f position;
    sf::Vector2f movement;

    void Initialize(const sf::Texture &texture, const float angle, const sf::Vector2f &shipPosition, const float screenWidth, const float screenHeight);
    void Update(const float elapsedTime);
private:
    float screenWidth;
    float screenHeight;

    void HandleOutOfScopes();
};
