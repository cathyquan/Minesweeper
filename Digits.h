//
// Created by Cathy Quan on 12/8/21.
//

#ifndef PROJECT3_NEW_DIGITS_H
#define PROJECT3_NEW_DIGITS_H
#include "TextureManager.h"

class Digits {
    int numMines;
    int hundredsDigit;
    int tensDigit;
    int onesDigit;
    bool isNegative;
    sf::Sprite negative;
    sf::Sprite hundreds;
    sf::Sprite tens;
    sf::Sprite ones;
public:
    Digits(int numMines) {
        this->numMines = numMines;
        hundredsDigit = numMines / 100;
        tensDigit = numMines % 100 / 10;
        onesDigit = numMines % 10;
        isNegative = false;
    }
    int GetNumMines() {
        return numMines;
    }
    void SetupDigits(int num)
    {
        this->numMines = num;
        if (num < 0) {
            isNegative = true;
            num = -1 * num;
        }
        hundredsDigit = num / 100;
        tensDigit = num % 100 / 10;
        onesDigit = num % 10;
    }
    void DrawDigit(sf::Sprite& num, int digit) {
        switch(digit) {
            case 0:
                num.setTextureRect(sf::Rect<int>(21 * 0, 0, 21, 32));
                break;
            case 1:
                num.setTextureRect(sf::Rect<int>(21 * 1, 0, 21, 32));
                break;
            case 2:
                num.setTextureRect(sf::Rect<int>(21 * 2, 0, 21, 32));
                break;
            case 3:
                num.setTextureRect(sf::Rect<int>(21 * 3, 0, 21, 32));
                break;
            case 4:
                num.setTextureRect(sf::Rect<int>(21 * 4, 0, 21, 32));
                break;
            case 5:
                num.setTextureRect(sf::Rect<int>(21 * 5, 0, 21, 32));
                break;
            case 6:
                num.setTextureRect(sf::Rect<int>(21 * 6, 0, 21, 32));
                break;
            case 7:
                num.setTextureRect(sf::Rect<int>(21 * 7, 0, 21, 32));
                break;
            case 8:
                num.setTextureRect(sf::Rect<int>(21 * 8, 0, 21, 32));
                break;
            case 9:
                num.setTextureRect(sf::Rect<int>(21 * 9, 0, 21, 32));
                break;
            case 10:
                num.setTextureRect(sf::Rect<int>(21 * 10, 0, 21, 32));
                break;
            default:
                num.setTextureRect(sf::Rect<int>(21 * 10, 0, 21, 32));
                break;
        }
    }
    void DrawNegative() {
        sf::Sprite negativeTemp(TextureManager::GetTexture("digits"));
        negative = negativeTemp;
        DrawDigit(negative, 10);
        negative.setPosition(0, 512);
    }
    void DrawHundred() {
        sf::Sprite hundredsTemp(TextureManager::GetTexture("digits"));
        hundreds = hundredsTemp;
        DrawDigit(hundreds, hundredsDigit);
        hundreds.setPosition(21, 512);
    }
    void DrawTens() {
        sf::Sprite tensTemp(TextureManager::GetTexture("digits"));
        tens = tensTemp;
        DrawDigit(tens, tensDigit);
        tens.setPosition(42, 512);
    }
    void DrawOnes() {
        sf::Sprite onesTemp(TextureManager::GetTexture("digits"));
        ones = onesTemp;
        DrawDigit(ones, onesDigit);
        ones.setPosition(63, 512);
    }
    void DrawNumMines(sf::RenderWindow& window) {
        if(isNegative) {
            DrawNegative();
            window.draw(negative);
        }
        DrawHundred();
        DrawTens();
        DrawOnes();
        window.draw(hundreds);
        window.draw(tens);
        window.draw(ones);
    }
};

#endif //PROJECT3_NEW_DIGITS_H
