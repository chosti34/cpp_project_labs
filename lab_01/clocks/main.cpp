#define _USE_MATH_DEFINES

#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

struct Circle
{
    static const int radius = 250;

    Vector2f point;
};

struct Clocks
{
    static const int mainCircleRadius = 250;
    static const int centerCircleRadius = 10;
    static const int amountOfDots = 60;

    CircleShape dot[amountOfDots];
    CircleShape mainCircle;
    CircleShape centerCircle;

    RectangleShape hourHand;
    RectangleShape minuteHand;
    RectangleShape secondsHand;
};

struct Files
{
    Music clockTick;
    Font font;
};

void InitializeClockDots(RenderWindow &window, CircleShape dot[60])
{
    const int amountOfDots = 60;
    const int dotPositionOffset = 10;

    Circle clock;
    float angle = 0.f;

    for (int i = 0; i < amountOfDots; ++i)
    {
        clock.point.x = (clock.radius - dotPositionOffset) * cos(angle);
        clock.point.y = (clock.radius - dotPositionOffset) * sin(angle);

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
        dot[i].setPosition(clock.point.x + window.getSize().x / 2, clock.point.y + window.getSize().y / 2);

        angle += + ((2 * M_PI) / 60);
    }
}

void ProcessClockCircles(RenderWindow &window, const Vector2f &windowCenter, CircleShape &mainCircle, CircleShape &centerCircle)
{
    const int clockCircleThickness = 2;
    const int amountOfPolygons = 100;

    mainCircle.setPointCount(amountOfPolygons);
    mainCircle.setOutlineThickness(clockCircleThickness);
    mainCircle.setOutlineColor(sf::Color::Black);
    mainCircle.setOrigin(mainCircle.getGlobalBounds().width / 2, mainCircle.getGlobalBounds().height / 2);
    mainCircle.setPosition(window.getSize().x / 2 + clockCircleThickness, window.getSize().y / 2 + clockCircleThickness);

    centerCircle.setPointCount(amountOfPolygons);
    centerCircle.setFillColor(sf::Color::Red);
    centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
    centerCircle.setPosition(windowCenter);
}

void ProcessClockHands(const Vector2f &windowCenter, RectangleShape &hourHand, RectangleShape &minuteHand, RectangleShape &secondsHand)
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

void ProcessClockDigits(RenderWindow &window, Files &files)
{
    Text text;
    String str;

    const int charSize = 16;

    text.setFont(files.font);
    text.setCharacterSize(charSize);
    text.setColor(Color::Black);

    int digit = 12;

    str = std::to_string(digit);
    text.setString(str);

    Circle clock;
    float angle = 0.f;
    const int amountOfClockDots = 60;
    const int numbersOffset = 35;

    for (int i = 0; i < amountOfClockDots; ++i)
    {
        clock.point.x = (clock.radius - numbersOffset) * cos(angle - (M_PI / 2));
        clock.point.y = (clock.radius - numbersOffset) * sin(angle - (M_PI / 2));

        if ((i % 5) == 0)
        {
            text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
            text.setPosition(clock.point.x + window.getSize().x / 2, clock.point.y + window.getSize().y / 2);
            window.draw(text);

            ++digit;
            digit %= 12;

            str = std::to_string(digit);
            text.setString(str);
        }

        angle += ((2 * M_PI) / 60);
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

void DrawClocks(RenderWindow &window, Clocks &clocks, Files &files)
{
    window.draw(clocks.mainCircle);
    window.draw(clocks.hourHand);
    window.draw(clocks.minuteHand);
    window.draw(clocks.secondsHand);
    window.draw(clocks.centerCircle);
    ProcessClockDigits(window, files);

    const int amountOfClockDots = 60;

    for (int i = 0; i < amountOfClockDots; ++i)
    {
        window.draw(clocks.dot[i]);
    }
}

void InitializeClocks(RenderWindow &window, Clocks &clocks)
{
    const int mainCircleRadius = 250;
    const int centerCircleRadius = 10;

    const Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    InitializeClockDots(window, clocks.dot);

    clocks.mainCircle.setRadius(mainCircleRadius);
    clocks.centerCircle.setRadius(centerCircleRadius);
    ProcessClockCircles(window, windowCenter, clocks.mainCircle, clocks.centerCircle);

    const Vector2f hourHandSize = Vector2f(5, 180);
    const Vector2f minuteHandSize = Vector2f(3, 220);
    const Vector2f secondsHandSize = Vector2f(3, 230);

    clocks.hourHand.setSize(hourHandSize);
    clocks.minuteHand.setSize(minuteHandSize);
    clocks.secondsHand.setSize(secondsHandSize);
    ProcessClockHands(windowCenter, clocks.hourHand, clocks.minuteHand, clocks.secondsHand);
}

void EnterApplicationMainLoop(RenderWindow &window, Clocks &clocks, Files &files)
{
    files.clockTick.setLoop(true);
    files.clockTick.play();

    while (window.isOpen())
    {
        ProcessEvents(window);
        SetTimeForClockHands(clocks.hourHand, clocks.minuteHand, clocks.secondsHand);

        window.clear(Color::White);
        DrawClocks(window, clocks, files);
        window.display();
    }
}

void LoadFromFiles(Files &files)
{
    if (!files.clockTick.openFromFile("resources/sounds/clock-1.wav"))
    {
        exit(EXIT_FAILURE);
    }

    if (!files.font.loadFromFile("resources/fonts/arial.ttf"))
    {
        exit(EXIT_FAILURE);
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

    Files files;
    LoadFromFiles(files);

    EnterApplicationMainLoop(window, clocks, files);

    return EXIT_SUCCESS;
}
