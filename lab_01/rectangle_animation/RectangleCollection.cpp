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

void CRectangleCollection::Update(const float elapsedTime)
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

    ChangeCoordinates(movement, elapsedTime);
    ChangeColor(elapsedTime);
}

void CRectangleCollection::ChangeCoordinates(sf::Vector2f &movement, const float elapsedTime)
{
    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        m_collection[i].setPosition(m_collection[i].getPosition() + movement * m_speedMovement * elapsedTime);
    }
}

void CRectangleCollection::ProcessOutOfScopes(const sf::Vector2f &scopes)
{
    if (m_collection[0].getPosition().y + m_topOffset + m_collection[0].getOrigin().y >= scopes.y)
    {
        m_state = State::UP;
    }
    else if (m_collection[0].getPosition().y - m_topOffset - m_collection[0].getOrigin().y <= 0)
    {
        m_state = State::DOWN;
    }
}

void CRectangleCollection::ChangeColor(const float elapsedTime)
{
    for (size_t i = 0; i < m_collection.size(); ++i)
    {
        if (m_state == State::DOWN)
        {

        }
        else if (m_state == State::UP)
        {

        }

        m_collection[i].setFillColor(m_color);
    }
}
