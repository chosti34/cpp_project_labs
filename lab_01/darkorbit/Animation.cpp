#include "stdafx.h"
#include "Animation.h"

void CAnimation::SetAnimationProperties(const sf::Texture &texture, const size_t framesAmount, const float animationSpeed)
{
    this->texture = texture;
    this->framesAmount = framesAmount;
    this->animationSpeed = animationSpeed;
}

void CAnimation::Initialize(const size_t start_x, const size_t start_y, const size_t width, const size_t height)
{
    currentFrame = 0;

    for (size_t i = 0; i < framesAmount; ++i)
    {
        frames.push_back(sf::IntRect(start_x + i * width, start_y, width, height));
    }

    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(width / 2), static_cast<float>(height / 2));

    sprite.setTextureRect(frames[0]);
}

void CAnimation::Update(const float elapsedTime)
{
    currentFrame += animationSpeed * elapsedTime;

    if (currentFrame >= framesAmount)
    {
        currentFrame -= framesAmount;
    }

    if (framesAmount > 0)
    {
        sprite.setTextureRect(frames[static_cast<int>(currentFrame)]);
    }
}
