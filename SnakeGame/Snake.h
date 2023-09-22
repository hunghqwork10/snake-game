#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class SnakeSegment : public sf::Drawable, public sf::Transformable {
private:
	float width;
	float height;

	mutable sf::RectangleShape segmentShape;

public:
	SnakeSegment(float width, float height) {
		this->width = width;
		this->height = height;
		this->setPosition(50.f, 50.f);
		segmentShape.setSize(sf::Vector2f(width, height));
	}

	float getWidth() {
		return this->width;
	}

	void setWidth(float _value) {
		this->width = _value;
	}

	float getHeight() {
		return this->height;
	}

	void setHeight(float _value) {
		this->height = _value;
	}

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setFillColor(const sf::Color& color);
};

class Snake : public sf::Drawable
{
public:
	enum Direction {
		Up, Down, Left, Right
	};

private:
	std::vector<SnakeSegment> segments; // danh sach cac segment cua con ran
	SnakeSegment* head;
	sf::Color color; // mau sac con ran
	float speed;
	sf::Vector2f direction; // huong di chuyen

	float elapsed;
	float delay;

	Direction currentDirection;

public:
	Snake(float width, float height, sf::Color color, float speed);

	void moveSnake();

	// hàm để cập nhật vị trí con rắn theo hướng đi chuyển
	void update(float deltaTime);

	void changeDirection(Direction direction);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

