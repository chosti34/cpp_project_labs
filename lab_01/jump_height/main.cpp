#include "stdafx.h"

float calculateDistance(float time, float startingSpeed, float acceleration)
{
    return (startingSpeed * time) - (0.5f * (acceleration * time * time));
}

int main()
{
    const float g = 9.81f;

    float currentHeight, maxHeight, timeOfMaxHeight, startingSpeed;
    bool isMaxHeight;

    printf("Enter jump height, please: ");

    if (scanf("%f", &maxHeight) == 0)
    {
        printf("Expected floating-point or integer number\n");
        exit(1);
    }

    timeOfMaxHeight = sqrt((2.0f * maxHeight) / g);
    startingSpeed = g * timeOfMaxHeight;

    printf("Time when height has it's maximum value = %f\n", timeOfMaxHeight);

    isMaxHeight = false;

    for (float time = 0; time < (2.0f * timeOfMaxHeight); time += 0.1f)
    {
        if ((time > timeOfMaxHeight) && (!isMaxHeight))
        {
            isMaxHeight = true;

            currentHeight = calculateDistance(timeOfMaxHeight, startingSpeed, g);
            printf("time = %f, height = %f\n", timeOfMaxHeight, currentHeight);
        }

        currentHeight = calculateDistance(time, startingSpeed, g);
        printf("time = %f, height = %f\n", time, currentHeight);
    }

    currentHeight = calculateDistance(2.0f * timeOfMaxHeight, startingSpeed, g);
    printf("time = %f, height = %f\n", 2 * timeOfMaxHeight, currentHeight);

    return 0;
}