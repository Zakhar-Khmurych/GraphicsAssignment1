

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
            playerSquare(sf::Vector2f(150.f, 150.f), sf::Vector2f(375.f, 275.f), 150.f, 90.f) 
        {
            LoadGame();
        }


    void RunTheGame() {
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
        Frame frame(window_width, window_height);

        sf::Clock clock;
        sf::Vector2f previousPosition = playerSquare.getPosition();
        float previousRotation = playerSquare.getRotation();

        TextureManager textureManager;
        if (!textureManager.loadTexture("squareTexture", "Suppiluliuma.png")) {
            std::cerr << "Failed to load texture" << std::endl;
        }        
        sf::Texture* Stexture = textureManager.getTexture("squareTexture");
        if (Stexture) {
            playerSquare.setTexture(Stexture);
        }
        if (!textureManager.loadTexture("frameTexture", "Ea-Nasir.png")) {
            std::cerr << "Failed to load texture" << std::endl;
        }
        sf::Texture* Ftexture = textureManager.getTexture("frameTexture");
        if (Ftexture) {
            frame.setTexture(Ftexture);
        } 


        sf::SoundBuffer collisionBuffer;
        if (!collisionBuffer.loadFromFile("sound.wav")) {
            std::cerr << "Failed to load collision sound!" << std::endl;
            return;
        }
        sf::Sound collisionSound;
        collisionSound.setBuffer(collisionBuffer);

        while (window.isOpen()) {
            sf::Time elapsed = clock.restart();
            float deltaTime = elapsed.asSeconds();

            InputAction action = inputHandler->processInput(window);

            if (action == InputAction::Exit) {
                SaveGame();
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

            if (frame.checkCollision(playerSquare.getBounds())) { //use vector collidables for collisions with whatever
                playerSquare.setPosition(previousPosition);
                playerSquare.setRotation(previousRotation);
                playerSquare.setFillColor(sf::Color::Red);
                collisionSound.play();
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

    void SaveGame() {
        std::ofstream saveFile("savegame.txt");
        if (saveFile.is_open()) {
            sf::Vector2f pos = playerSquare.getPosition();
            float rotation = playerSquare.getRotation();
            saveFile << pos.x << ";" << pos.y << ";" << rotation << "\n";
            saveFile.close();
        }
        else {
            std::cerr << "Failed to open save file for writing!" << std::endl;
        }
    }

    void LoadGame() {
        std::ifstream saveFile("savegame.txt");
        if (saveFile.is_open()) {
            float x, y, rotation;
            char separator;
            if (saveFile >> x >> separator >> y >> separator >> rotation) {
                playerSquare.setPosition(sf::Vector2f(x, y));
                playerSquare.setRotation(rotation);
            }
            saveFile.close();
        }
        else {
            std::cerr << "No save file found, starting with default position." << std::endl;
        }
    }


};


