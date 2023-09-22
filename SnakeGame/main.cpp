#include <SFML/Graphics.hpp>
#include <thread>

#include "LevelBorder.h"
#include "Snake.h"
#include "main.h"
#include "GameManager.h"
#include "GameConfig.h"

// khai báo hàm (function declaration)
void moveControl(Snake& snake, float speed, float deltaTime);

int main()
{
    sf::RenderWindow window(sf::VideoMode(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT), "Snake Game");
    
    SnakeSegment snakeSegment(50, 50);
    snakeSegment.setFillColor(sf::Color::Red);
    
    GameManager gameManager;
    /*std::thread task(&gameManager.deplayAndDestroy, gameManager);
    task.join();*/

    Snake snake(25, 25, sf::Color::Green, 20);

    LevelBorder levelBorder;
    
    sf::Clock clock; // bắt đầu đồng hồ

    float tickDelayTime = 0.5f;
    //float elapsed;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTimeTimer = clock.restart(); // lấy thời gian đã trôi qua và khởi động lại
        float deltaTime = deltaTimeTimer.asSeconds();

        float speed = 200.f; // tốc độ di chuyển (pixel/giây)

        moveControl(snake, speed, deltaTime);

        snake.update(deltaTime);

        // render lên màn hình tất cả những gì đã tính toán xong
        window.clear();
        //window.draw(snakeSegment);
        gameManager.drawFruit(window);
        window.draw(snake);
        window.display();
    }

    return 0;
}

void moveControl(Snake& snake, float speed, float deltaTime)
{
    // Di chuyển phần của con rắn khi nhấn các phím mũi tên
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        snake.changeDirection(Snake::Up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        snake.changeDirection(Snake::Down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        snake.changeDirection(Snake::Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        snake.changeDirection(Snake::Right);
    }
}