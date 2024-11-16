#include <SFML/Graphics.hpp>
#include <vector>

sf::Color operator*(float value, sf::Color color)
{
    return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

template<class T>
T lerp(const T& start, const T& end, float alpha)
{
    return (1 - alpha) * start + alpha * end;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Smooth Trail Effect");

    const int numBalls = 5;
    const float ballRadius = 20.f;

    std::vector<sf::CircleShape> balls(numBalls, sf::CircleShape(ballRadius));
    for (auto& ball : balls)
        ball.setOrigin(ballRadius, ballRadius);

    std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta };
    for (int i = 0; i < numBalls; ++i)
        balls[i].setFillColor(colors[i]);

    std::vector<sf::Vector2f> positions(numBalls, sf::Vector2f(400, 300)); 
    std::vector<sf::Vector2f> velocities(numBalls, sf::Vector2f(0, 0));

    const float smoothness = 0.5f; 
    const float followSpeed = 0.05f; 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        positions[0] = lerp(positions[0], mousePosition, smoothness); 

       
        for (int i = 1; i < numBalls; ++i)
        {
            positions[i] = lerp(positions[i], positions[i - 1], followSpeed);
        }

       
        for (int i = 0; i < numBalls; ++i)
        {
            balls[i].setPosition(positions[i]);
        }

  
        window.clear();
        for (const auto& ball : balls)
            window.draw(ball);
        window.display();
    }

    return 0;
}
