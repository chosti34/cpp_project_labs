#include "stdafx.h"

#include "Spaceship.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 768;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Darkorbit");

    window.setFramerateLimit(60);

    CSpaceShip spaceShip;
    spaceShip.Initialize();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            spaceShip.angle += 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            spaceShip.angle -= 3;
        }
        spaceShip.isThrust = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

        if (spaceShip.isThrust)
        {
            spaceShip.dx += cos(spaceShip.angle * 3.14 / 180);
            spaceShip.dy += sin(spaceShip.angle * 3.14 / 180);
        }
        else
        {
            spaceShip.dx *= 0.99;
            spaceShip.dy *= 0.99;
        }

        int maxSpeed = 15;

        float speed = sqrt((spaceShip.dx * spaceShip.dx) + (spaceShip.dy * spaceShip.dy));

        if (speed > maxSpeed)
        {
            spaceShip.dx *= maxSpeed / speed;
            spaceShip.dy *= maxSpeed / speed;
        }

        spaceShip.x += spaceShip.dx;
        spaceShip.y += spaceShip.dy;

        if (spaceShip.x > 1280) spaceShip.x = 0;
        if (spaceShip.x < 0) spaceShip.x = 1280;
        if (spaceShip.y > 768) spaceShip.y = 0;
        if (spaceShip.y < 0) spaceShip.y = 768;

        spaceShip.sprite.setPosition(spaceShip.x, spaceShip.y);
        spaceShip.sprite.setRotation(spaceShip.angle + 90);

        window.clear(sf::Color::Black);
        window.draw(spaceShip.sprite);
        window.display();
    }

    return 0;
}
