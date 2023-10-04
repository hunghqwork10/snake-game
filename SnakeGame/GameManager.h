#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <functional>

#include "GameConstant.h"
#include "GameConfig.h"
#include "Snake.h"

// khai báo kiểu con trỏ delegate
//typedef void (*event_handler) (int);

class GameManager {
private:
	std::unique_ptr<sf::RectangleShape> fruitShape; // sử dụng smart pointer
	Snake* snake;
public:
	// khai báo các event
	//void (*onHeadCollideFruit)();
	std::function<void()> onHeadCollideFruit;

public:
	GameManager();
	~GameManager();

	void Update();
	void Update(float deltaTime);

	void moveControl(float deltaTime);

	void drawSnake(sf::RenderTarget& target);
	void drawFruit(sf::RenderTarget& target);

	static void delayAndDestroy(GameManager& gameManager) {
		for (int i = 0; i < 5; i++) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			gameManager.fruitShape.reset();
			/*std::cout << "Destroy fruitShape object" << std::endl;
			gameManager.fruitShape->setFillColor(sf::Color::Blue);*/
		}
	}

	void DestroyCurrentFruit();

	void generateNewFruit();
	
	void checkHeadCollideFruit();
};