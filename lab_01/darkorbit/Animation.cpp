#include "stdafx.h"
#include "Animation.h"

void Animation::SetAnimationProperties(const sf::Texture &texture, const size_t framesAmount, const float animationSpeed)
{
    // �������������� ����������� ��������� ��� �������� (��������, ���-�� ������, �������� �������� � ������ � �������)
    this->texture = texture;
    this->framesAmount = framesAmount;
    this->animationSpeed = animationSpeed;
}

void Animation::Initialize(const size_t start_x, const size_t start_y, const size_t width, const size_t height)
{
    currentFrame = 0;

    // �������������� ������ �������� ���������� ������� ����� � ����������� � ��������� ���� IntRect
    for (size_t i = 0; i < framesAmount; ++i)
    {
        frames.push_back(sf::IntRect(start_x + i * width, start_y, width, height));
    }

    sprite.setTexture(texture);
    sprite.setOrigin(width / 2, height / 2);

    // �������������� ��������� ���� ��� �������
    sprite.setTextureRect(frames[0]);
}

void Animation::Update(const float elapsedTime)
{
    // ��� ���� ����� ������� ����� ������ ������� �� �������� �� �������� ������ ���������� ���������� �����,
    // ��������� � ���������� ������ ������� (������� ����� ������ ����� ����� animationSpeed ������)

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
