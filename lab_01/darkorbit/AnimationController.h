#pragma once

class AnimationController
{
public:

    AnimationController() {};
    AnimationController(sf::Texture &texture, int start_x, int start_y, int width, int height, int framesAmount, float animationSpeed);

    float currentFrame;
    float frameOffset;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;

    void Update();
};
