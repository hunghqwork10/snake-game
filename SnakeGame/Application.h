#pragma once

#include <SFML/Graphics.hpp>
#include <thread>

#include "imgui.h"
#include "imgui-SFML.h"

#include "LevelBorder.h"
#include "Snake.h"
#include "main.h"
#include "GameManager.h"
#include "GameConfig.h"

class Application
{
public:
	Application();
	~Application();

	void run();

	void processEvents();
	void update();
	void render();

private:
	sf::RenderWindow window;

	GameManager* gameManager;
	LevelBorder* levelBorder;
	sf::Clock clock;
};

