#include "stdafx.h"
#include "RectangleCollection.h"

void CRectangleCollection::Initialize()
{
    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        m_collection[i].setFillColor(m_color);

        m_collection[i].setSize(sf::Vector2f(m_width, m_height));
        m_collection[i].setOrigin(m_width / 2, m_height / 2);

        m_collection[i].setPosition(
            m_leftOffset + m_collection[i].getOrigin().x + i * (m_width + m_rectangleDistance),
            m_topOffset + m_collection[i].getOrigin().y
        );

        m_collection[i].setRotation(0);
    }
}

void CRectangleCollection::Update(const float elapsedTime, const sf::Vector2f &screenSize)
{
    UpdateState(screenSize);

    UpdateMovementVector(elapsedTime);
    UpdateSpeed(elapsedTime);
    UpdateColor(elapsedTime);
    UpdateSize(elapsedTime);

    ChangeCoordinates(m_movement, elapsedTime, screenSize);
}

void CRectangleCollection::UpdateMovementVector(const float elapsedTime)
{
    if (m_state == State::DOWN)
    {
        m_movement = sf::Vector2f(0, 1);
        m_angle = 0;
    }
    else if (m_state == State::UP)
    {
        m_movement = sf::Vector2f(0, -1);
        m_angle = 0;
    }
    else if (m_state == State::RIGHT)
    {
        m_movement = sf::Vector2f(1, 0);
        m_angle = 0;
    }
    else if (m_state == State::ROTATE_RIGHT)
    {
        m_movement = sf::Vector2f(0, 0);
        m_angle += m_changeAngleSpeed * elapsedTime;
        if (m_angle > 360)
        {
            m_angle = static_cast<float>(static_cast<int>(m_angle) % 360);
        }
    }
    else if (m_state == State::LEFT_ASYNC)
    {
        m_movement = sf::Vector2f(-3, -3);
    }
    else if (m_state == State::LEFT_DIAG)
    {
        m_movement = sf::Vector2f(-1, -0.3f);
    }
    else if (m_state == State::LEFT)
    {
        m_movement = sf::Vector2f(-1, 0);
    }
}

void CRectangleCollection::ChangeCoordinates(sf::Vector2f &movement, const float elapsedTime, const sf::Vector2f &scopes)
{
    if ((m_state == State::DOWN) || (m_state == State::UP) || (m_state == State::RIGHT) || (m_state == State::LEFT_DIAG) || (m_state == State::LEFT))
    {
        for (size_t i = 0; i < m_collection.size(); ++i)
        {
            m_collection[i].setRotation(0);
            m_collection[i].setPosition(m_collection[i].getPosition() + movement * m_speedMovement * elapsedTime);
        }
    }
    else if (m_state == State::ROTATE_RIGHT)
    {
        for (size_t i = 0; i < m_collection.size(); ++i)
        {
            float dx = m_collection[m_collection.size() - 1].getPosition().x - m_collection[i].getPosition().x;
            float dy = m_collection[m_collection.size() - 1].getPosition().y - m_collection[i].getPosition().y;
            float radius = hypot(dx, dy);

            m_collection[i].setPosition(
                (scopes.x - m_width / 2 - m_leftOffset) - radius * static_cast<float>(cos(m_angle * M_PI / 180)),
                (scopes.y - m_height / 2 - m_topOffset) - radius * static_cast<float>(sin(m_angle * M_PI / 180))
            );

            m_collection[i].setRotation(m_angle);
        }
    }
    else if (m_state == State::LEFT_ASYNC)
    {
        if (m_collection[m_index].getPosition().y >= m_collection[0].getPosition().y)
        {
            m_collection[m_index].setPosition(m_collection[m_index].getPosition() + movement * m_speedMovement * elapsedTime);
        }
        else
        {
            ++m_index;
        }

        if (m_index > m_collection.size() - 1)
        {
            m_index = 1;
            m_wasAsync = true;
        }
    }
}

void CRectangleCollection::UpdateState(const sf::Vector2f &screenSize)
{
    if ((m_collection[0].getPosition().y + m_topOffset + m_collection[0].getOrigin().y >= screenSize.y) &&
        (m_state == State::DOWN))
    {
        m_state = State::RIGHT;
    }
    else if ((m_collection[0].getPosition().y - m_topOffset - m_collection[0].getOrigin().y <= 0) &&
             (m_collection[m_collection.size() - 1].getPosition().x - m_leftOffset - m_collection[0].getOrigin().x <= 0) &&
             (m_state == State::LEFT))
    {
        Initialize();
        m_state = State::DOWN;
    }
    else if ((m_collection[m_collection.size() - 1].getPosition().y + m_topOffset + m_collection[0].getOrigin().y) &&
             (m_collection[m_collection.size() - 1].getPosition().x + m_leftOffset + m_collection[m_collection.size() - 1].getOrigin().x >= screenSize.x) &&
             (m_state == State::RIGHT))
    {
        m_state = State::ROTATE_RIGHT;
    }
    else if ((m_angle >= 90) && (m_state == State::ROTATE_RIGHT))
    {
        m_angle = 0;
        m_state = State::UP;
    }
    else if ((m_collection[3].getPosition().y < screenSize.y / 2) && (m_state == State::UP))
    {
        m_state = State::LEFT_ASYNC;
    }
    else if (m_wasAsync)
    {
        m_wasAsync = false;
        m_state = State::LEFT_DIAG;
    }
    else if ((m_collection[0].getPosition().y - m_topOffset - m_collection[0].getOrigin().y <= 0) &&
             (m_state == State::LEFT_DIAG))
    {
        m_state = State::LEFT;
    }
}

void CRectangleCollection::UpdateSpeed(const float elapsedTime)
{
    if (m_state == State::RIGHT)
    {
        float minSpeed = 150.f;
        if (m_speedMovement > minSpeed)
        {
            m_speedMovement -= m_speedMovement * elapsedTime / 2;
        }
    }
    else if ((m_state == State::LEFT) || (m_state == State::LEFT_DIAG))
    {
        float maxSpeed = 300.f;
        if (m_speedMovement < maxSpeed)
        {
            m_speedMovement += m_speedMovement * elapsedTime / 2;
        }
    }
}

void CRectangleCollection::UpdateColor(const float elapsedTime)
{
    if (m_state == State::RIGHT)
    {
        const int maxRedValue = 200;
        const int minRedValue = 10;

        if ((m_color.r < maxRedValue) && (!m_isColorReachedMax))
        {
            m_color.r += sf::Uint8(m_changeColorSpeed * elapsedTime);
        }
        else if (m_color.r > minRedValue)
        {
            m_isColorReachedMax = true;
            m_color.r -= sf::Uint8(m_changeColorSpeed * elapsedTime);
        }
        else
        {
            m_isColorReachedMax = false;
        }
    }
    else if ((m_state == State::LEFT) || (m_state == State::LEFT_DIAG))
    {
        const int maxGreenValue = 150;
        const int minGreenValue = 30;

        if ((m_color.g < maxGreenValue) && (!m_isColorReachedMax))
        {
            m_color.g += sf::Uint8(m_changeColorSpeed * elapsedTime);
        }
        else if (m_color.g > minGreenValue)
        {
            m_isColorReachedMax = true;
            m_color.g -= sf::Uint8(m_changeColorSpeed * elapsedTime);
        }
        else
        {
            m_isColorReachedMax = false;
        }
    }
    else if ((m_state == State::DOWN) || (m_state == State::UP) || (m_state == State::LEFT_ASYNC) ||
             (m_state == State::ROTATE_RIGHT))
    {
        const int maxBlueValue = 200;
        const int minBlueValue = 30;

        if ((m_color.b < maxBlueValue) && (!m_isColorReachedMax))
        {
            m_color.b += sf::Uint8(m_changeColorSpeed * elapsedTime);
        }
        else if (m_color.b > minBlueValue)
        {
            m_isColorReachedMax = true;
            m_color.b -= sf::Uint8(m_changeColorSpeed * elapsedTime);
        }
        else
        {
            m_isColorReachedMax = false;
        }
    }

    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        m_collection[i].setFillColor(m_color);
    }
}

void CRectangleCollection::UpdateSize(const float elapsedTime)
{
    if (m_state == State::DOWN)
    {
        if (m_width > 30)
        {
            m_width -= changeSizeSpeed * elapsedTime;
        }
    }
    else if (m_state == State::RIGHT)
    {
        if (m_width < 60)
        {
            m_width += changeSizeSpeed * elapsedTime;
        }
    }
    else if (m_state == State::UP || m_state == State::LEFT_ASYNC)
    {
        if (m_height > 30)
        {
            m_height -= changeSizeSpeed * elapsedTime;
        }
    }
    else if (m_state == State::LEFT_DIAG || m_state == State::LEFT)
    {
        if (m_height < 60)
        {
            m_height += changeSizeSpeed * elapsedTime;
        }
    }

    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        m_collection[i].setSize(sf::Vector2f(m_width, m_height));
    }
}

void CRectangleCollection::Draw(sf::RenderWindow &window)
{
    for (size_t i = 0; i < m_collection.max_size(); ++i)
    {
        window.draw(m_collection[i]);
    }
}
