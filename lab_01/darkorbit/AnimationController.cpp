#include "stdafx.h"
#include "AnimationController.h"

AnimationController::AnimationController(sf::Texture &texture, int start_x, int start_y, int width, int height, int framesAmount, float animationSpeed)
{
    // Инициализирует данные необходимые для работы с анимацией объекта

    currentFrame = 0;
    frameOffset = animationSpeed;

    for (size_t i = 0; i < framesAmount; ++i)
    {
        frames.push_back(sf::IntRect(start_x + i * width, start_y, width, height));
    }

    //sprite.setTexture(texture);

    // Смещаем центр отсчёта координат для спрайта в центр картинки
    sprite.setOrigin(width / 2, height / 2);

    // Задаем начальный кадр
    sprite.setTextureRect(frames[0]);
}

void AnimationController::Update()
{
    // Каждый раз при вызове функции кадр будет изменяться

    currentFrame += frameOffset;

    if (currentFrame >= frames.size())
    {
        currentFrame -= frames.size();
    }

    if (frames.size() > 0)
    {
        sprite.setTextureRect(frames[static_cast<int>(currentFrame)]);
    }
}
