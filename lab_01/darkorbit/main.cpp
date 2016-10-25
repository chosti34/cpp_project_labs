#include "stdafx.h"
#include "Animation.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "GameController.h"

int main()
{
    srand(time(NULL));

    const size_t screenWidth = 1280;
    const size_t screenHeight = 720;
    const std::string gameTitle = "DarkOrbit";

    GameController controller(screenWidth, screenHeight, gameTitle);

    controller.Initialize();
    controller.EnterMainLoop();

    return 0;
}
