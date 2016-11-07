#pragma once

enum class State
{
    UP,
    DOWN,
    RIGHT,
    ROTATE_RIGHT,
    LEFT_ASYNC,
    LEFT_DIAG,
    LEFT
};

class CRectangleCollection
{
public:
    void Initialize();
    void Draw(sf::RenderWindow &window);
    void Update(const float elapsedTime, const sf::Vector2f &screenSize);
private:
    std::array<sf::RectangleShape, 8> m_collection;
    float m_width = 60;
    float m_height = 60;
    const float m_leftOffset = 10;
    const float m_topOffset = 10;
    const float m_rectangleDistance = 10;
    float m_angle = 0;
    float m_speedMovement = 300;
    float m_changeAngleSpeed = 50;
    const float m_changeColorSpeed = 500;
    const float changeSizeSpeed = 10;
    sf::Vector2f m_movement;
    sf::Color m_color = sf::Color(0, 100, 255, 255);
    State m_state = State::DOWN;
    size_t m_index = 1;
    bool m_wasAsync = false;
    bool m_isColorReachedMax = false;
    bool m_isSizeReachedMax = false;
    void ChangeCoordinates(sf::Vector2f &movement, const float elapsedTime, const sf::Vector2f &scopes);
    void UpdateState(const sf::Vector2f &screenSize);
    void UpdateMovementVector(const float elapsedTime);
    void UpdateSpeed(const float elapsedTime);
    void UpdateColor(const float elapsedTime);
    void UpdateSize(const float elapsedTime);
};
