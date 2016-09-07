#include "stdafx.h"

// This program takes max jump height from input and prints
// jump height for every time point with step 0.1 seconds.
// Program should print all time points when height is min and max.
//
// TODO: Fix all warnings on high warning level (/W4, -Wall -Wextra).
// TODO: Rename variables and split to several functions,
// see also https://ps-group.github.io/sfml/coding_conventions.html
// TODO: fix negative height values, fix heigh values higher than max height.

int main()
{
    const float g = 9.8f;

    float maxHeight, timeOfMaxHeight;

    printf("Enter jump height, please: ");

    if (scanf("%f", &maxHeight) == 0)
    {
        printf("Expected floating-point or integer number\n");
        exit(1);
    }

    // T - time point when height is at maximum.
    // t - current time point
    // v(t) == v0 - g * t
    // v0 = g * T
    // s(t) == v0 * t - 0.5 * g * t * t

    timeOfMaxHeight = sqrt(maxHeight * 2 / g);
    printf("Time when height has it's maximum value = %f\n", timeOfMaxHeight);

    bool flag = false;
    for (float time = 0; time < timeOfMaxHeight * 2; time += 0.1f)
    {
        if (time > timeOfMaxHeight && !flag)
        {
            flag = true;
            float startingSpeed = g * timeOfMaxHeight;
            float currentHeight = (startingSpeed * timeOfMaxHeight) - (0.5f * g * timeOfMaxHeight * timeOfMaxHeight);
            printf("time = %f, height = %f\n", timeOfMaxHeight, currentHeight);
        }

        float startingSpeed = g * timeOfMaxHeight;
        float currentHeight = (startingSpeed * time) - (0.5f * g * time * time);
        printf("time = %f, height = %f\n", time, currentHeight);
    }

    float startingSpeed = g * timeOfMaxHeight;
    float currentHeight = (startingSpeed * (2 * timeOfMaxHeight)) - 0.5f * g * (timeOfMaxHeight * 2) * (timeOfMaxHeight * 2);
    printf("time = %f, height = %f\n", 2 * timeOfMaxHeight, currentHeight);

    return 0;
}