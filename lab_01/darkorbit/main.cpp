#include "stdafx.h"
#include "Animation.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "GameController.h"

int main()
{
    srand(static_cast<size_t>(time(NULL)));

    const float screenWidth = 1280;
    const float screenHeight = 720;
    const std::string gameTitle = "DarkOrbit";

    CGameController controller(screenWidth, screenHeight, gameTitle);

    controller.Initialize();
    controller.EnterMainLoop();

    return 0;
}
