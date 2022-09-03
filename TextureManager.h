//
// Created by Cathy Quan on 12/6/21.
//

#ifndef MAIN_CPP_TEXTUREMANAGER_H
#define MAIN_CPP_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;

class TextureManager {
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};

#endif //MAIN_CPP_TEXTUREMANAGER_H