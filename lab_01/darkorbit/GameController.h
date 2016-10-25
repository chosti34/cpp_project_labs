#pragma once

class GameController
{
public:
    GameController(const size_t screenWidth, const size_t screenHeight, const std::string &gameTitle);

    void Initialize();
    void EnterMainLoop();
private:
    size_t screenWidth;
    size_t screenHeight;
    std::string gameTitle;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Texture spaceShipTexture;
    sf::Texture asteroidTexture;
    sf::Texture laserTexture;

    sf::Music music;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    sf::RenderWindow window;

    sf::Clock clock;

    SpaceShip spaceShip;
    std::list<Asteroid*> asteroids;
    std::list<Bullet*> bullets;

    void HandleEvents();
    void Update();
    void Render();
};
