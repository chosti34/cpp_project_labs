#include "stdafx.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "AnimationController.h"
#include "AppController.h"

int main()
{
    srand(time(NULL));

    AppController controller;

    controller.Initialize();
    controller.EnterMainLoop();

    return 0;
}
