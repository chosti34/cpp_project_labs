#pragma once

class Animation
{
public:
    void SetAnimationProperties(const sf::Texture &texture, const size_t framesAmount, const float animationSpeed);
    void Initialize(const size_t start_x, const size_t start_y, const size_t width, const size_t height);
    void Update(const float elapsedTime = 0);

    sf::Sprite sprite;
private:
    sf::Texture texture;

    float animationSpeed;
    float currentFrame;

    size_t framesAmount;

    std::vector<sf::IntRect> frames;
};
