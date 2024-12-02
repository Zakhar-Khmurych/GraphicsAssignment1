#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;

public:
    bool loadTexture(const std::string& name, const std::string& filePath) {
        sf::Texture texture;
        if (!texture.loadFromFile(filePath)) {
            return false; 
        }
        textures[name] = std::move(texture); 
        return true;
    }
    sf::Texture* getTexture(const std::string& name) {
        auto it = textures.find(name);
        if (it != textures.end()) {
            return &it->second;
        }
        return nullptr;
    }
};

