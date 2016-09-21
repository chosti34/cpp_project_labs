#include "stdafx.h"

float CalculateDistance(float time, float startingSpeed, float acceleration)
{
    return (startingSpeed * time) - (0.5f * (acceleration * time * time));
}

void GetMaxHeightValueFromUser(float &maxHeight)
{
    printf("Enter jump height, please: ");

    if (scanf("%f", &maxHeight) == 0)
    {
        printf("Expected floating-point or integer number\n");
        exit(1);
    }
}

void InitializeStartingValues(float &maxHeight, float &timeOfMaxHeight, float &startingSpeed)
{
    const float g = 9.81f;

    timeOfMaxHeight = sqrt((2.0f * maxHeight) / g);
    startingSpeed = g * timeOfMaxHeight;

    printf("Time when height has it's maximum value = %f\n", timeOfMaxHeight);
}

void processCurrentHeight(float timeOfMaxHeight, float &startingSpeed, float &currentHeight)
{
    const float g = 9.81f;

    currentHeight = CalculateDistance(timeOfMaxHeight, startingSpeed, g);
    printf("time = %f, height = %f\n", timeOfMaxHeight, currentHeight);
}

void CalculateJumpHeightAndTime(float &timeOfMaxHeight, float &startingSpeed)
{
    bool isMaxHeight = false;
    float currentHeight = 0;

    for (float time = 0; time < (2.0f * timeOfMaxHeight); time += 0.1f)
    {
        if ((time > timeOfMaxHeight) && (!isMaxHeight))
        {
            isMaxHeight = true;
            processCurrentHeight(timeOfMaxHeight, startingSpeed, currentHeight);
        }
        processCurrentHeight(time, startingSpeed, currentHeight);
    }
    processCurrentHeight(2 * timeOfMaxHeight, startingSpeed, currentHeight);
}

int main()
{
    float maxHeight, timeOfMaxHeight, startingSpeed;

    GetMaxHeightValueFromUser(maxHeight);
    InitializeStartingValues(maxHeight, timeOfMaxHeight, startingSpeed);
    CalculateJumpHeightAndTime(timeOfMaxHeight, startingSpeed);

    return 0;
}
