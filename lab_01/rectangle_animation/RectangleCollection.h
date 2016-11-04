#pragma once

enum class State
{
    UP,
    DOWN
};

class CRectangleCollection
{
public:
    CRectangleCollection();
    ~CRectangleCollection();
    void Initialize();
    void Draw(sf::RenderWindow &window);
    void Update(const float elapsedTime);
    void ProcessOutOfScopes(const sf::Vector2f &scopes);
private:
    std::array<sf::RectangleShape, 8> m_collection;
    const float m_width = 60;
    const float m_height = 60;
    const float m_leftOffset = 10;
    const float m_topOffset = 10;
    const float m_rectangleDistance = 10;
    float m_angle = 0;
    const float m_speedMovement = 150;
    const float m_speedColorChange = 1000000;
    sf::Color m_color = sf::Color(0, 100, 255, 255);
    State m_state = State::DOWN;
    void ChangeCoordinates(sf::Vector2f &movement, const float elapsedTime);
    void ChangeColor(const float elapsedTime);
};
