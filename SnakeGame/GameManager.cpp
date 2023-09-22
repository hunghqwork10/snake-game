#include "GameManager.h"

GameManager::GameManager()
{
	fruitShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(GameConstant::SEGMENT_WIDTH, GameConstant::SEGMENT_HEIGHT));
	fruitShape->setFillColor(sf::Color::Red);
	fruitShape->setPosition(0, 0);
}

GameManager::~GameManager()
{
	//delete fruitShape;
}

void GameManager::deplayAndDestroy() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	fruitShape.reset();
}
