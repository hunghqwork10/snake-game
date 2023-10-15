#include "GameManager.h"
#include <imgui.h>

GameManager::GameManager()
{
	snake = new Snake(GameConstant::SEGMENT_WIDTH, GameConstant::SEGMENT_HEIGHT, sf::Color::Green, 20);
	// gán các event delegate
	snake->onEachStepMoved = [this]() -> void { checkHeadCollideFruit(); };

	generateNewFruit();
}

GameManager::~GameManager()
{
	//delete fruitShape;
	delete snake;
}

void GameManager::Update()
{
}

void GameManager::Update(float deltaTime)
{
	snake->update(deltaTime);
}

void GameManager::moveControl(float deltaTime)
{
	// Di chuyển phần của con rắn khi nhấn các phím mũi tên
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		snake->changeDirection(Snake::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		snake->changeDirection(Snake::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		snake->changeDirection(Snake::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		snake->changeDirection(Snake::Right);
	}
}

void GameManager::drawSnake(sf::RenderTarget& target)
{
	target.draw(*snake);
}

void GameManager::drawFruit(sf::RenderTarget& target) {
	if (fruitShape != nullptr) {
		target.draw(*fruitShape);
	}
}

void GameManager::checkHeadCollideFruit()
{
	//std::cout << "checkHeadCollideFruit..." << std::endl;
	SnakeSegment* snakeHead = snake->getSnakeHead();
	if (snakeHead->getPosition() == fruitShape->getPosition()) {
		std::cout << "Collided..." << std::endl;
		snake->increaseOneSegment();
		generateNewFruit();
		//// invoke event
		//onHeadCollideFruit();
	}
}

void GameManager::DestroyCurrentFruit() {
	if (fruitShape != nullptr) {
		fruitShape.reset();
	}
}

void GameManager::generateNewFruit() {

	DestroyCurrentFruit();

	std::cout << "Grid width: " << GameConfig::WINDOW_WIDTH / GameConstant::SEGMENT_WIDTH << std::endl;

	std::random_device rd; // sử dụng để khởi tạo bộ sinh số ngẫu nhiên
	std::mt19937 gen(rd()); // Mersenne Twister 19937 generator, khởi tạo bằng rd()
	std::uniform_int_distribution<> dis(0, GameConfig::WINDOW_WIDTH / (int)GameConstant::SEGMENT_WIDTH - 1);

	//std::cout << "Random number: " << dis(gen) << std::endl;
	int random_X = dis(gen);
	int random_Y = dis(gen);

	fruitShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(GameConstant::SEGMENT_WIDTH, GameConstant::SEGMENT_HEIGHT));
	fruitShape->setFillColor(sf::Color::Red);
	fruitShape->setPosition(random_X * GameConstant::SEGMENT_WIDTH, random_Y * GameConstant::SEGMENT_HEIGHT);
}
