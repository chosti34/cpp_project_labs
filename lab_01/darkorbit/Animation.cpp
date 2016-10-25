#include "stdafx.h"
#include "Animation.h"

void Animation::SetAnimationProperties(const sf::Texture &texture, const size_t framesAmount, const float animationSpeed)
{
    // Инициализируем необходимые параметры для анимации (текстура, кол-во кадров, скорость анимации в кадрах в секунду)
    this->texture = texture;
    this->framesAmount = framesAmount;
    this->animationSpeed = animationSpeed;
}

void Animation::Initialize(const size_t start_x, const size_t start_y, const size_t width, const size_t height)
{
    currentFrame = 0;

    // Инициализируем вектор хранящий координаты каждого кадра в отдельности в структуре типа IntRect
    for (size_t i = 0; i < framesAmount; ++i)
    {
        frames.push_back(sf::IntRect(start_x + i * width, start_y, width, height));
    }

    sprite.setTexture(texture);
    sprite.setOrigin(width / 2, height / 2);

    // Инициализируем начальный кадр для спрайта
    sprite.setTextureRect(frames[0]);
}

void Animation::Update(const float elapsedTime)
{
    // Для того чтобы частота смены кадров спрайта не зависела от скорости работы процессора необходимо время,
    // прошедшее с последнего вызова функции (частота смена кадров будет равна animationSpeed единиц)

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
