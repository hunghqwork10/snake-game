#include "Application.h"

Application::Application() : window(sf::VideoMode(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT), "Snake Game")
, score(0)
{
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	gameManager = new GameManager();
}

Application::~Application()
{
	delete gameManager;
}

void Application::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Application::update()
{
    sf::Time deltaTimeTimer = clock.restart(); // lấy thời gian đã trôi qua và khởi động lại
    float deltaTime = deltaTimeTimer.asSeconds();

    ImGui::SFML::Update(window, deltaTimeTimer);

    // start the Dear ImGui frame
    ImGui::Begin("Score", NULL, ImGuiWindowFlags_NoMove);

    // đặt vị trí cửa sổ ở góc trên cùng bên trái
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);

    // display the score
    ImGui::Text("Score: %d", score);

    ImGui::End();

    gameManager->moveControl(deltaTime);
    gameManager->Update(deltaTime);
}

void Application::render()
{
    // render lên màn hình tất cả những gì đã tính toán xong
    window.clear();
    gameManager->drawFruit(window);
    gameManager->drawSnake(window);

    ImGui::SFML::Render(window);

    window.display();
}

