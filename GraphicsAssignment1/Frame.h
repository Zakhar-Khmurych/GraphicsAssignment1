

#pragma once
#include <SFML/Graphics.hpp>

class Frame {
    sf::RectangleShape topLine;
    sf::RectangleShape bottomLine;
    sf::RectangleShape leftLine;
    sf::RectangleShape rightLine;

public:
    Frame(int windowWidth, int windowHeight) {
        topLine.setSize(sf::Vector2f(windowWidth, 15.f));
        topLine.setPosition(0.f, 0.f);
        topLine.setFillColor(sf::Color::Yellow);

        bottomLine.setSize(sf::Vector2f(windowWidth, 15.f));
        bottomLine.setPosition(0.f, windowHeight - 15.f);
        bottomLine.setFillColor(sf::Color::Yellow);

        leftLine.setSize(sf::Vector2f(15.f, windowHeight));
        leftLine.setPosition(0.f, 0.f);
        leftLine.setFillColor(sf::Color::Yellow);

        rightLine.setSize(sf::Vector2f(15.f, windowHeight));
        rightLine.setPosition(windowWidth - 15.f, 0.f);
        rightLine.setFillColor(sf::Color::Yellow);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(topLine);
        window.draw(bottomLine);
        window.draw(leftLine);
        window.draw(rightLine);
    }

    bool checkCollision(const sf::RectangleShape& object) const {
        return object.getGlobalBounds().intersects(topLine.getGlobalBounds()) ||
            object.getGlobalBounds().intersects(bottomLine.getGlobalBounds()) ||
            object.getGlobalBounds().intersects(leftLine.getGlobalBounds()) ||
            object.getGlobalBounds().intersects(rightLine.getGlobalBounds());
    }

    bool checkCollision(const sf::FloatRect& rect) const {
        return rect.intersects(topLine.getGlobalBounds()) ||
            rect.intersects(bottomLine.getGlobalBounds()) ||
            rect.intersects(leftLine.getGlobalBounds()) ||
            rect.intersects(rightLine.getGlobalBounds());
    }
};


class Square {
private:
    sf::RectangleShape squareShape;
    float rotationAngle;
    sf::Vector2f position;
    float movementSpeed;
    float rotationSpeed;

public:
    Square(sf::Vector2f size, sf::Vector2f startPosition, float moveSpeed, float rotateSpeed)
        : rotationAngle(0.f), position(startPosition), movementSpeed(moveSpeed), rotationSpeed(rotateSpeed) {
        squareShape.setSize(size);
        squareShape.setFillColor(sf::Color::Green);
        squareShape.setPosition(startPosition);
    }

    void move(float dx, float dy, float deltaTime) {
        squareShape.move(dx * deltaTime, dy * deltaTime);
        position = squareShape.getPosition();
    }

    void rotate(float angle, float deltaTime) {
        rotationAngle += angle * deltaTime;
        squareShape.setRotation(rotationAngle);
    }

    void setPosition(sf::Vector2f newPosition) {
        position = newPosition;
        squareShape.setPosition(newPosition);
    }

    void setRotation(float rotation) {
        squareShape.setRotation(rotation);
    }

    void setFillColor(sf::Color color) {
        squareShape.setFillColor(color);
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    float getRotation() {
        return squareShape.getRotation();
    }

    sf::FloatRect getBounds() const {
        return squareShape.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(squareShape);
    }
};
