#pragma once

#include <SFML/Graphics.hpp>

class LevelBorder : public sf::Drawable
{
private:
	sf::VertexArray lines;

public:
	LevelBorder() {
        // tạo một LineStrip dùng để vẽ border của level
        lines = sf::VertexArray(sf::LineStrip, 5);

        // đặt vị trí cho các điểm
        lines[0].position = sf::Vector2f(10, 10);
        lines[1].position = sf::Vector2f(400, 10);
        lines[2].position = sf::Vector2f(400, 400);
        lines[3].position = sf::Vector2f(10, 400);
        lines[4].position = sf::Vector2f(10, 10);

        // đặt màu cho các điểm
        for (int i = 0; i < 5; i++) {
            lines[i].color = sf::Color::Red;
        }
	}

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(lines, states);
    }
};

