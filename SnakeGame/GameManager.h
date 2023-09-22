#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include <thread>

#include "GameConstant.h"

class GameManager {
private:
	std::unique_ptr<sf::RectangleShape> fruitShape; // sử dụng smart pointer

public:
	GameManager();
	~GameManager();

	void drawFruit(sf::RenderTarget& target) {
		target.draw(*fruitShape);
	}

	void deplayAndDestroy();
};