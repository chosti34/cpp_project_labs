#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

struct Circle
{
    const int radius = 250;
    const float PI = 3.1415927;
    float angle = 0.0;
    int x = 0;
    int y = 0;
};

struct Clocks
{
    const int mainCircleRadius = 250;
    const int centerCircleRadius = 10;

    CircleShape dot[60];
    CircleShape mainCircle;
    CircleShape centerCircle;

    RectangleShape hourHand;
    RectangleShape minuteHand;
    RectangleShape secondsHand;
};

void InitializeClockDots(RenderWindow &window, CircleShape dot[60])
{
    Circle clock;

    for (int i = 0; i < 60; ++i)
    {
        clock.x = (clock.radius - 10) * cos(clock.angle);
        clock.y = (clock.radius - 10) * sin(clock.angle);

        if ((i % 5) == 0)
        {
            dot[i] = CircleShape(3);
        }
        else
        {
            dot[i] = CircleShape(1);
        }

        dot[i].setFillColor(Color::Black);
        dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
        dot[i].setPosition(clock.x + window.getSize().x / 2, clock.y + window.getSize().y / 2);

        clock.angle = clock.angle + ((2 * clock.PI) / 60);
    }
}

void ProcessClockCircles(RenderWindow &window, Vector2f &windowCenter, CircleShape &mainCircle, CircleShape &centerCircle)
{
    const int clockCircleThickness = 2;

    mainCircle.setPointCount(100);
    mainCircle.setOutlineThickness(clockCircleThickness);
    mainCircle.setOutlineColor(sf::Color::Black);
    mainCircle.setOrigin(mainCircle.getGlobalBounds().width / 2, mainCircle.getGlobalBounds().height / 2);
    mainCircle.setPosition(window.getSize().x / 2 + clockCircleThickness, window.getSize().y / 2 + clockCircleThickness);

    centerCircle.setPointCount(100);
    centerCircle.setFillColor(sf::Color::Red);
    centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
    centerCircle.setPosition(windowCenter);
}

void ProcessClockHands(Vector2f &windowCenter, RectangleShape &hourHand, RectangleShape &minuteHand, RectangleShape &secondsHand)
{
    hourHand.setFillColor(Color::Black);
    minuteHand.setFillColor(Color::Black);
    secondsHand.setFillColor(Color::Red);

    hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
    minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
    secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);

    hourHand.setPosition(windowCenter);
    minuteHand.setPosition(windowCenter);
    secondsHand.setPosition(windowCenter);
}

void SetTimeForClockHands(RectangleShape &hourHand, RectangleShape &minuteHand, RectangleShape &secondsHand)
{
    std::time_t currentTime = std::time(NULL);
    struct tm *ptm = localtime(&currentTime);

    hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
    minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
    secondsHand.setRotation(ptm->tm_sec * 6);
}

void ProcessClockDigits(RenderWindow &window)
{
    Circle clock;
    int charSize = 16;

    Font font;
    Text text;
    String str;

    if (!font.loadFromFile("resources/fonts/arial.ttf"))
    {
        exit(EXIT_FAILURE);
    }

    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setColor(Color::Black);

    int digit = 12;

    str = std::to_string(digit);
    text.setString(str);

    for (int i = 0; i < 60; ++i)
    {
        clock.x = (clock.radius - 35) * cos(clock.angle - clock.PI / 2);
        clock.y = (clock.radius - 35) * sin(clock.angle - clock.PI / 2);

        if ((i % 5) == 0)
        {
            text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
            text.setPosition(clock.x + window.getSize().x / 2, clock.y + window.getSize().y / 2);
            window.draw(text);

            ++digit;

            if (digit == 13)
            {
                digit = 1;
            }

            str = std::to_string(digit);
            text.setString(str);
        }

        clock.angle = clock.angle + ((2 * clock.PI) / 60);
    }
}

void ProcessEvents(RenderWindow &window)
{
    Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void DrawClocks(RenderWindow &window, Clocks &clocks)
{
    window.draw(clocks.mainCircle);
    window.draw(clocks.hourHand);
    window.draw(clocks.minuteHand);
    window.draw(clocks.secondsHand);
    window.draw(clocks.centerCircle);
    ProcessClockDigits(window);

    for (int i = 0; i < 60; ++i)
    {
        window.draw(clocks.dot[i]);
    }
}

void InitializeClocks(RenderWindow &window, Clocks &clocks)
{
    const int mainCircleRadius = 250;
    const int centerCircleRadius = 10;

    Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    InitializeClockDots(window, clocks.dot);

    clocks.mainCircle.setRadius(mainCircleRadius);
    clocks.centerCircle.setRadius(centerCircleRadius);
    ProcessClockCircles(window, windowCenter, clocks.mainCircle, clocks.centerCircle);

    clocks.hourHand.setSize(Vector2f(5, 180));
    clocks.minuteHand.setSize(Vector2f(3, 220));
    clocks.secondsHand.setSize(Vector2f(2, 230));
    ProcessClockHands(windowCenter, clocks.hourHand, clocks.minuteHand, clocks.secondsHand);
}

void ApplicationMainLoop(RenderWindow &window, Clocks &clocks)
{
    while (window.isOpen())
    {
        ProcessEvents(window);
        SetTimeForClockHands(clocks.hourHand, clocks.minuteHand, clocks.secondsHand);

        window.clear(Color::White);
        DrawClocks(window, clocks);
        window.display();
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(screenWidth, screenHeight), "SFML Analog Clock", Style::Close, settings);

    Clocks clocks;
    InitializeClocks(window, clocks);

    Music clockTick;
    if (!clockTick.openFromFile("resources/sounds/clock-1.wav"))
    {
        exit(EXIT_FAILURE);
    }
    clockTick.setLoop(true);
    clockTick.play();

    ApplicationMainLoop(window, clocks);

    return EXIT_SUCCESS;
}
