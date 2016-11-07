#pragma once

class CSpaceShip
{
public:
    CAnimation animation;
    CAnimation animation_stay;
    CAnimation animation_go;

    sf::Vector2f movement;
    sf::Vector2f position;

    float angle;
    float radius;
    int score;

    float translationalMotionSpeed;
    float rotationalMotionSpeed;

    bool isThrust;
    bool isAlive;

    void Initialize(const sf::Texture &texture, const float screenWidth, const float screenHeight);
    void Update(const float elapsedTime);
private:
    float screenWidth;
    float screenHeight;

    void HandleKeyPress(const float elapsedTime);
    void CalculateMovementVector(const float elapsedTime);
    void HandleOutOfScopes();
};
