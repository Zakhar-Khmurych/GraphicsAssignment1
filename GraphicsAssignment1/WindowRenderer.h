

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Frame.h"

// to do list
// keys moved away
// green square separated
// frame separated
// time-based loop instead of timeless


enum class InputAction {
    None,
    Exit,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    RotateClockwise,
    RotateCounterClockwise
};

class InputHandler {
public:
    virtual ~InputHandler() = default;

    virtual InputAction processInput(sf::RenderWindow& window) = 0;
};

class WASDInputHandler : public InputHandler {
public:
    InputAction processInput(sf::RenderWindow& window) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return InputAction::Exit;
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    return InputAction::RotateClockwise;
                }
                else {
                    return InputAction::RotateCounterClockwise;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            return InputAction::MoveUp;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            return InputAction::MoveDown;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            return InputAction::MoveLeft;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            return InputAction::MoveRight;
        }

        return InputAction::None;
    }
};

/*
auto dispatch_input(sf::RenderWindow &window) -> input_type
{
    sf::Event out_event;
    if (!window.pollEvent(out_event))
    {
        return input_type::none;
    }

    switch (out_event.type)
    {
        case sf::Event::Closed:
            return input_type::exit;
        case sf::Event::MouseWheelScrolled:
            return input_type::rotate;
        
    }
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                rotationAngle += 5.f;
            }
            else if (event.mouseWheelScroll.delta < 0) {
                rotationAngle -= 5.f;
            }
        }
    }

    square.setRotation(rotationAngle);

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
}
*/



class WindowRenderer {
    int window_width;
    int window_height;
    float rotationAngle;
    sf::Vector2f position;
    InputHandler* inputHandler;
    Square playerSquare;

    public:
        WindowRenderer(int width, int height, InputHandler* handler)
            : window_width(width), window_height(height), inputHandler(handler),
            playerSquare(sf::Vector2f(150.f, 150.f), sf::Vector2f(375.f, 275.f), 150.f, 90.f) {}



    void RunTheGame_FrameBased() {
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
        Frame frame(window_width, window_height);

        sf::RectangleShape square(sf::Vector2f(150.f, 150.f));
        square.setFillColor(sf::Color::Green);
        square.setPosition(375.f, 275.f);

        float movementSpeed = 1.5f;

        while (window.isOpen()) {
            InputAction action = inputHandler->processInput(window);

            if (action == InputAction::Exit) {
                break;
            }

            switch (action) {
            case InputAction::MoveUp:
                square.move(0.f, -movementSpeed);
                break;
            case InputAction::MoveDown:
                square.move(0.f, movementSpeed);
                break;
            case InputAction::MoveLeft:
                square.move(-movementSpeed, 0.f);
                break;
            case InputAction::MoveRight:
                square.move(movementSpeed, 0.f);
                break;
            case InputAction::RotateClockwise:
                rotationAngle += 5.f;
                break;
            case InputAction::RotateCounterClockwise:
                rotationAngle -= 5.f;
                break;
            default:
                break;
            }

            square.setRotation(rotationAngle);

            if (frame.checkCollision(square)) {
                square.setPosition(position);
                square.setFillColor(sf::Color::Red);
                movementSpeed = 0.01f;
            }
            else {
                square.setFillColor(sf::Color::Green);
                movementSpeed = 1.5f;
            }

            position = square.getPosition();

            window.clear();
            frame.draw(window);
            window.draw(square);
            window.display();
        }
    }

    void RunTheGame_interna () {
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
        Frame frame(window_width, window_height);

        sf::RectangleShape square(sf::Vector2f(150.f, 150.f));
        square.setFillColor(sf::Color::Green);
        square.setPosition(375.f, 275.f);

        float movementSpeed = 450.f; 
        float rotationSpeed = 270.f; 

        sf::Clock clock; 

        while (window.isOpen()) {
            sf::Time elapsed = clock.restart(); 
            float deltaTime = elapsed.asSeconds(); 

            InputAction action = inputHandler->processInput(window);

            if (action == InputAction::Exit) {
                break;
            }

            switch (action) {
            case InputAction::MoveUp:
                square.move(0.f, -movementSpeed * deltaTime);
                break;
            case InputAction::MoveDown:
                square.move(0.f, movementSpeed * deltaTime);
                break;
            case InputAction::MoveLeft:
                square.move(-movementSpeed * deltaTime, 0.f);
                break;
            case InputAction::MoveRight:
                square.move(movementSpeed * deltaTime, 0.f);
                break;
            case InputAction::RotateClockwise:
                rotationAngle += rotationSpeed * deltaTime;
                break;
            case InputAction::RotateCounterClockwise:
                rotationAngle -= rotationSpeed * deltaTime;
                break;
            default:
                break;
            }

            square.setRotation(rotationAngle);

            if (frame.checkCollision(square)) {
                square.setPosition(position);
                square.setFillColor(sf::Color::Red);
                movementSpeed = 50.f; 
            }
            else {
                square.setFillColor(sf::Color::Green);
                movementSpeed = 150.f;
            }

            position = square.getPosition();

            window.clear();
            frame.draw(window);
            window.draw(square);
            window.display();
        }
    }

    void RunTheGame() {
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
        Frame frame(window_width, window_height);

        sf::Clock clock;
        sf::Vector2f previousPosition = playerSquare.getPosition();
        float previousRotation = playerSquare.getRotation();

        while (window.isOpen()) {
            sf::Time elapsed = clock.restart();
            float deltaTime = elapsed.asSeconds();

            InputAction action = inputHandler->processInput(window);

            if (action == InputAction::Exit) {
                break;
            }

            previousPosition = playerSquare.getPosition();
            previousRotation = playerSquare.getRotation();

            switch (action) {
            case InputAction::MoveUp:
                playerSquare.move(0.f, -100.f, deltaTime);
                break;
            case InputAction::MoveDown:
                playerSquare.move(0.f, 100.f, deltaTime);
                break;
            case InputAction::MoveLeft:
                playerSquare.move(-100.f, 0.f, deltaTime);
                break;
            case InputAction::MoveRight:
                playerSquare.move(100.f, 0.f, deltaTime);
                break;
            case InputAction::RotateClockwise:
                playerSquare.rotate(90.f, deltaTime);
                break;
            case InputAction::RotateCounterClockwise:
                playerSquare.rotate(-90.f, deltaTime);
                break;
            default:
                break;
            }

            if (frame.checkCollision(playerSquare.getBounds())) {
                playerSquare.setPosition(previousPosition);
                playerSquare.setRotation(previousRotation);
                playerSquare.setFillColor(sf::Color::Red);
            }
            else {
                playerSquare.setFillColor(sf::Color::Green);
            }

            window.clear();
            frame.draw(window);
            playerSquare.draw(window);
            window.display();
        }
    }

};


