#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class WindowRenderer
{
	int window_width;
	int window_height;
    float rotationAngle;
    sf::Vector2f position;

	public : WindowRenderer(int w, int h) {
		window_width = w;
		window_height = h;
	}

	public : void RunTheGame() {
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");

        sf::RectangleShape square(sf::Vector2f(50.f, 50.f));
        square.setFillColor(sf::Color::Green);
        square.setPosition(375.f, 275.f);

        float movementSpeed = 0.5;

        sf::RectangleShape topLine(sf::Vector2f(window_width, 15.f));   
        topLine.setPosition(0.f, 0.f);
        topLine.setFillColor(sf::Color::Yellow);

        sf::RectangleShape bottomLine(sf::Vector2f(window_width, 15.f)); 
        bottomLine.setPosition(0.f, window_height - 15.f);
        bottomLine.setFillColor(sf::Color::Yellow);

        sf::RectangleShape leftLine(sf::Vector2f(15.f, window_height)); 
        leftLine.setPosition(0.f, 0.f);
        leftLine.setFillColor(sf::Color::Yellow);

        sf::RectangleShape rightLine(sf::Vector2f(15.f, window_height)); 
        rightLine.setPosition(window_width - 15.f, 0.f);
        rightLine.setFillColor(sf::Color::Yellow);

        while (window.isOpen()) //прибити до тіків
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseWheelScrolled) {
                    if (event.mouseWheelScroll.delta > 0) {
                        rotationAngle += 15.f; 
                    }
                    else if (event.mouseWheelScroll.delta < 0) {
                        rotationAngle -= 15.f; 
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                square.move(0.f, -movementSpeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                square.move(0.f, movementSpeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                square.move(-movementSpeed, 0.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                square.move(movementSpeed, 0.f);
            }

            square.setRotation(rotationAngle);

            if (square.getGlobalBounds().intersects(topLine.getGlobalBounds()) ||
                square.getGlobalBounds().intersects(bottomLine.getGlobalBounds()) ||
                square.getGlobalBounds().intersects(leftLine.getGlobalBounds()) ||
                square.getGlobalBounds().intersects(rightLine.getGlobalBounds())) 
            {
                square.setPosition(position);
                square.setFillColor(sf::Color::Red); 
                movementSpeed = 0.01;
                // maybe move back
            }
            else {
                square.setFillColor(sf::Color::Green);
                movementSpeed = 0.5;
            }

            position = square.getPosition();
            std::cout << "Square position: (" << position.x << ", " << position.y << ")" << std::endl;


            window.clear();

            window.draw(topLine);
            window.draw(bottomLine);
            window.draw(leftLine);
            window.draw(rightLine);


            window.draw(square);
            window.display();
        }
	}

};

