#include <SFML/Graphics.hpp>

int main()
{
    // Создаем окно 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minimal SFML Game");
    
    // Создаем игрока (квадрат)
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.f, 300.f);
    
    // Скорость движения
    float speed = 200.f;
    
    // Игровой цикл
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Обработка ввода
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-speed * 0.016f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(speed * 0.016f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0.f, -speed * 0.016f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0.f, speed * 0.016f);
        
        // Очистка и отрисовка
        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }
    
    return 0;
}
