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

    if (elapsedTime > 0.3)
    {
        elapsedTime = 0.3;
    }

    collection.Update(elapsedTime, sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
}

void Render(sf::RenderWindow &window, CRectangleCollection &collection)
{
    window.clear(sf::Color::Black);
    collection.Draw(window);
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Rectangle Animation", sf::Style::Close);
    sf::Clock clock;

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
