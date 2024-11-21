

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
};

