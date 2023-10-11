#include <SFML/Graphics.hpp>
#include <thread>

#include "imgui.h"
#include "imgui-SFML.h"

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
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    
    GameManager* gameManager = new GameManager();
    
    //std::thread task(&GameManager::delayAndDestroy, std::ref(*gameManager));
    //task.detach(); // tách luồng ra khỏi đối tượng task

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

        ImGui::SFML::Update(window, deltaTimeTimer);

        //ImGui::ShowDemoWindow();
        ImGui::Begin("New Window");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        gameManager->moveControl(deltaTime);
        gameManager->Update(deltaTime);


        // render lên màn hình tất cả những gì đã tính toán xong
        window.clear();
        gameManager->drawFruit(window);
        gameManager->drawSnake(window);

        ImGui::SFML::Render(window);

        window.display();
    }

    delete gameManager;
    return 0;
}