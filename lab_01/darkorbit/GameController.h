#pragma once

class CGameController
{
public:
    CGameController(const float screenWidth, const float screenHeight, const std::string &gameTitle);
    void Initialize();
    void EnterMainLoop();
private:
    float screenWidth;
    float screenHeight;
    std::string gameTitle;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture spaceShipTexture;
    sf::Texture asteroidTexture;
    sf::Texture laserTexture;
    sf::Music music;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    sf::Font font;
    sf::Text text;
    sf::RenderWindow window;
    sf::Clock clock;
    CSpaceShip spaceShip;
    std::list<CAsteroid*> asteroids;
    std::list<CBullet*> bullets;
    bool m_isPlaying = true;
    void HandleEvents();
    void Update();
    void Render();
    void DrawAsteroids();
    void DrawBullets();
    bool IsShipCollidesWithAsteroid(CSpaceShip &ship, CAsteroid &asteroid);
    bool IsBulletCollidesWithAsteroid(CBullet &bullet, CAsteroid &asteroid);
    void UpdateAsteroids(const float elapsedTime);
    void UpdateBullets(const float elapsedTime);
    void ShootBullet();
    void LoadBackground();
    void LoadMusic();
    void LoadFonts();
    void InitializeShip();
    void InitializeAsteroids();
    void ProcessGameEnd();
};
