#include "Snake.h"

void SnakeSegment::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// vẽ đoạn (segment) của rắn bằng cách tạo ra một hình chữ nhật với vị trí và kích thước cho trước
	segmentShape.setPosition(getPosition());
	target.draw(segmentShape, states);
}

void SnakeSegment::setFillColor(const sf::Color& color)
{
	segmentShape.setFillColor(color);
}

Snake::Snake(float width, float height, sf::Color color, float speed) {
	// khởi tạo con rắn với các tham số cho trước
	this->color = color;
	this->speed = speed;
	this->direction = sf::Vector2f(1, 0);
	this->currentDirection = Down;

	elapsed = 0;
	delay = 0.5f;

	// tạo ra 3 đoạn đầu tiên cho con rắn giữa màn hình
	for (int i = 0; i < 3; i++) {
		SnakeSegment segment(width, height);
		segment.setFillColor(sf::Color::Green);
		segment.setPosition(100 + i * width, 0);
		segments.push_back(segment);
	}

	// con trỏ head (đầu con rắn) tham chiếu đến phần từ đầu tiên của mảng
	head = &segments[0];
	head->setFillColor(sf::Color::Yellow);
}

Snake::~Snake()
{
	//delete head;
}

void Snake::draw(RenderTarget& target, RenderStates states) const
{
	for (int i = 0; i < segments.size(); i++) {
		target.draw(segments[i]);
	}
}

// hàm để cập nhật vị trí con rắn theo hướng đi chuyển
void Snake::update(float deltaTime) {
	// cộng dồn thời gian trôi qua vào biến elapsed
	elapsed += deltaTime;

	// nếu elapsed vượt quá delay thì tiến hành cập nhật vị trí
	if (elapsed > delay) {
		// lưu trạng thái của đốt đầu trước khi di chuyển
		sf::Vector2f previousPosition = head->getPosition();

		// di chuyển con rắn sang ô tiếp theo
		//std::cout << head->getHeight() << std::endl;
		switch (currentDirection)
		{
		case Snake::Up:
			head->move(sf::Vector2f(0, -head->getHeight()));
			break;
		case Snake::Down:
			head->move(sf::Vector2f(0, head->getHeight()));
			break;
		case Snake::Left:
			head->move(sf::Vector2f(-head->getWidth(), 0));
			break;
		case Snake::Right:
			head->move(sf::Vector2f(head->getWidth(), 0));
			break;
		default:
			break;
		}

		for (int i = 1; i < segments.size(); i++) {
			// lưu trạng thái của đốt hiện tại trước khi di chuyển
			sf::Vector2f tempPosition = segments[i].getPosition();

			// di chuyển đốt hiện tại đến vị trí của đốt đứng trước nó
			segments[i].setPosition(previousPosition);

			// cập nhật previousPosition để sử dụng cho đốt tiếp theo
			previousPosition = tempPosition;
		}

		// mỗi lần move thì kiểm tra xem phần đầu đã collide với fruit chưa
		// bắn event onEachStepMoved
		onEachStepMoved();

		elapsed = 0;
	}
}

void Snake::changeDirection(Direction direction)
{
	currentDirection = direction;
}
