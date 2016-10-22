#pragma once

#include "AnimationController.h"

class AppController
{
public:
    void Initialize();
    void EnterMainLoop();
private:
    const std::string title = "Darkorbit";

    const size_t screenWidth = 1280;
    const size_t screenHeight = 720;

    sf::RenderWindow window;
    sf::Clock clock;

    SpaceShip ship;
    AnimationController asteroidAnimation;

    std::list<Asteroid*> asteroids;

    void HandleEvents();
    void Render();
    void Update();
    void HandleKeyboard();
    void CheckScopes();
};
