#include "stdafx.h"
#include "RectangleCollection.h"

void HandleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Update(sf::RenderWindow &window, sf::Clock &clock, CRectangleCollection &collection)
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();

    if (elapsedTime > 0.1f)
    {
        elapsedTime = 0.1f;
    }

    const float screenWidth = static_cast<float>(window.getSize().x);
    const float screenHeight = static_cast<float>(window.getSize().y);

    const sf::Vector2f screenSize(screenWidth, screenHeight);

    collection.Update(elapsedTime, screenSize);
}

void Render(sf::RenderWindow &window, CRectangleCollection &collection)
{
    window.clear(sf::Color::Black);
    collection.Draw(window);
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Rectangle Animation", sf::Style::Close, settings);
    sf::Clock clock;

    window.setFramerateLimit(60);

    CRectangleCollection collection;
    collection.Initialize();

    while (window.isOpen())
    {
        HandleEvents(window);
        Update(window, clock, collection);
        Render(window, collection);
    }

    return 0;
}
