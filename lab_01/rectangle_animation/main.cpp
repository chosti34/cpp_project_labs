// rectangle_animation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "const.h"

void InitializeRectangles(sf::RectangleShape rectangles[5])
{
    for (size_t i = 0; i < 5; ++i)
    {
        rectangles[i].setFillColor(START_COLOR);
        rectangles[i].setSize(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
        rectangles[i].setOrigin(RECTANGLE_WIDTH / 2, RECTANGLE_HEIGHT / 2);
        rectangles[i].setPosition(10 + i * (RECTANGLE_WIDTH + RECTANGLE_DISTANCE) + rectangles[i].getOrigin().x, 10 + rectangles[i].getOrigin().y);
    }
}

void DrawRectangles(sf::RenderWindow &window, sf::RectangleShape rectangles[5])
{
    for (size_t i = 0; i < 5; ++i)
    {
        window.draw(rectangles[i]);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Rectangle Animation");

    sf::RectangleShape rectangles[5];
    InitializeRectangles(rectangles);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        DrawRectangles(window, rectangles);
        window.display();
    }

    return 0;
}
