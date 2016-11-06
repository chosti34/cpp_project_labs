#include "stdafx.h"
#include "RectangleCollection.h"

CRectangleCollection::CRectangleCollection()
{
}

CRectangleCollection::~CRectangleCollection()
{
}

void CRectangleCollection::Initialize()
{
    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        m_collection[i].setFillColor(m_color);
        m_collection[i].setSize(sf::Vector2f(m_width, m_height));
        m_collection[i].setOrigin(m_width / 2, m_height / 2);
        m_collection[i].setPosition(m_leftOffset + m_collection[i].getOrigin().x + i * (m_width + m_rectangleDistance), m_topOffset + m_collection[i].getOrigin().y);
    }
}

void CRectangleCollection::Draw(sf::RenderWindow &window)
{
    for (size_t i = 0; i < m_collection.max_size(); ++i)
    {
        window.draw(m_collection[i]);
    }
}

void CRectangleCollection::Update(const float elapsedTime, const sf::Vector2f &scopes)
{
    sf::Vector2f movement;

    if (m_state == State::DOWN)
    {
        movement = sf::Vector2f(0, 1);
        m_angle = 0;
    }
    else if (m_state == State::UP)
    {
        movement = sf::Vector2f(0, -1);
        m_angle = 0;
    }
    else if (m_state == State::RIGHT)
    {
        movement = sf::Vector2f(1, 0);
        m_angle = 0;
    }
    else if (m_state == State::ROTATE_RIGHT)
    {
        movement = sf::Vector2f(0, 0);
        m_angle += m_changeAngleSpeed * elapsedTime;
        if (m_angle > 360)
        {
            m_angle = static_cast<float>(static_cast<int>(m_angle) % 360);
        }
    }
    else if (m_state == State::LEFT_ASYNC)
    {
        movement = sf::Vector2f(-3, -3);
    }
    else if (m_state == State::LEFT_DIAG)
    {
        movement = sf::Vector2f(-1, -0.3);
    }
    else if (m_state == State::LEFT)
    {
        movement = sf::Vector2f(-1, 0);
    }

    ProcessOutOfScopes(scopes);
    ChangeCoordinates(movement, elapsedTime, scopes);
    ChangeColor(elapsedTime);
    ChangeSize(elapsedTime);
}

void CRectangleCollection::ChangeCoordinates(sf::Vector2f &movement, const float elapsedTime, const sf::Vector2f &scopes)
{
    if ((m_state == State::DOWN) || (m_state == State::UP) || (m_state == State::RIGHT) || (m_state == State::LEFT_DIAG) || (m_state == State::LEFT))
    {
        for (size_t i = 0; i < m_collection.size(); ++i)
        {
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
        if (static_cast<int>(m_collection[m_index].getPosition().y) > static_cast<int>(m_collection[0].getPosition().y))
        {
            m_collection[m_index].setPosition(m_collection[m_index].getPosition() + movement * m_speedMovement * elapsedTime);
        }
        else
        {
            m_collection[m_index].setPosition(m_collection[m_index].getPosition().x, m_collection[0].getPosition().y);
            ++m_index;
        }

        if (m_index > m_collection.size() - 1)
        {
            m_index = 1;
            m_wasAsync = true;
        }
    }
}

void CRectangleCollection::ProcessOutOfScopes(const sf::Vector2f &scopes)
{
    if ((m_collection[0].getPosition().y + m_topOffset + m_collection[0].getOrigin().y >= scopes.y) && (m_collection[0].getPosition().x - m_leftOffset - m_collection[0].getOrigin().x <= 0))
    {
        m_state = State::RIGHT;
    }
    else if ((m_collection[0].getPosition().y - m_topOffset - m_collection[0].getOrigin().y <= 0) && (m_collection[m_collection.size() - 1].getPosition().x - m_leftOffset - m_collection[0].getOrigin().x <= 0) && (m_state == State::LEFT))
    {
        Initialize();
        m_state = State::DOWN;
    }
    else if ((m_collection[m_collection.size() - 1].getPosition().y + m_topOffset + m_collection[0].getOrigin().y) && (m_collection[m_collection.size() - 1].getPosition().x + m_leftOffset + m_collection[m_collection.size() - 1].getOrigin().x >= scopes.x) && (m_state == State::RIGHT))
    {
        m_state = State::ROTATE_RIGHT;
    }
    else if ((m_state == State::ROTATE_RIGHT) && (m_angle >= 90))
    {
        m_angle = 0;
        m_state = State::UP;
    }
    else if ((m_state == State::UP) && (m_collection[4].getPosition().y < scopes.y / 2))
    {
        m_state = State::LEFT_ASYNC;
    }
    else if (m_wasAsync)
    {
        m_wasAsync = false;
        m_state = State::LEFT_DIAG;
    }
    else if ((m_state == State::LEFT_DIAG) && (m_collection[0].getPosition().y - m_topOffset - m_collection[0].getOrigin().y <= 0))
    {
        m_state = State::LEFT;
    }
}

void CRectangleCollection::ChangeColor(const float elapsedTime)
{
    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        m_collection[i].setFillColor(m_color);
    }
}

void CRectangleCollection::ChangeSize(const float elapsedTime)
{
    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        m_collection[i].setSize(sf::Vector2f(m_width, m_height));
    }
}
