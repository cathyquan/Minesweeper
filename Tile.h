//
// Created by Cathy Quan on 12/7/21.
//

#ifndef MAIN_CPP_TILE_H
#define MAIN_CPP_TILE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "TextureManager.h"

using namespace std;

class Tile {
public:
    sf::Sprite reveal;
    sf::Vector2f position;
    bool isMine; // 0 if not mine, 1 if mine
    int row;
    int col;
    int mineNum;
    int tileStatus; // 0 if original, 1 if marked with flag, 2 if revealed
public:
    vector<Tile*> neighbors;

    Tile(sf::Vector2f position) {
        row = int (position.y / 32 + 0.5);
        col = int (position.x / 32 + 0.5);
        this->position = position;
        tileStatus = 0;
        isMine = 0;
    }

    void OutputTile() {
        cout << "tile position: " << "(" << row << ", " << col << ")" << endl;
        cout << "tile status: " << tileStatus << endl;
        if(isMine)
            cout << "IS MINE" << endl;
        else
            cout << "NOT A MINE" << endl;
        cout << "neighboring mines: " << mineNum << endl;
        cout << "" << endl;
    }

    void SetMineNum(int n) {
        mineNum = n;
    }

    int GetMineNum() {
        return mineNum;
    }

    void SetPosition(float xPosition, float yPosition) {
        position.x = xPosition;
        position.y = yPosition;
    }

    void DrawHiddenTile(sf::RenderWindow& window) {
        sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
        reveal = hiddenTile;
        reveal.setPosition(position);
//        cout << "row: " << position.x << ", col: " << position.y << endl;
        window.draw(reveal);
    }

    void DrawEmpty(sf::RenderWindow& window) {
        sf::Sprite emptyMine(TextureManager::GetTexture("tile_revealed"));
        emptyMine.setPosition(position);
        window.draw(emptyMine);
        reveal = emptyMine;
    }

    void DrawNumber(sf::RenderWindow& window, int num) {
        switch(num) {
            case 1: {
                sf::Sprite mine1(TextureManager::GetTexture("number_1"));
                mine1.setPosition(position.x, position.y);
                window.draw(mine1);
                break;
            }
            case 2: {
                sf::Sprite mine2(TextureManager::GetTexture("number_2"));
                mine2.setPosition(position.x, position.y);
                window.draw(mine2);
                break;
            }
            case 3: {
                sf::Sprite mine3(TextureManager::GetTexture("number_3"));
                mine3.setPosition(position.x, position.y);
                window.draw(mine3);
                break;
            }
            case 4: {
                sf::Sprite mine4(TextureManager::GetTexture("number_4"));
                mine4.setPosition(position.x, position.y);
                window.draw(mine4);
                break;
            }
            case 5: {
                sf::Sprite mine5(TextureManager::GetTexture("number_5"));
                mine5.setPosition(position.x, position.y);
                window.draw(mine5);
                break;
            }
            case 6: {
                sf::Sprite mine6(TextureManager::GetTexture("number_6"));
                mine6.setPosition(position.x, position.y);
                window.draw(mine6);
                break;
            }
            case 7: {
                sf::Sprite mine7(TextureManager::GetTexture("number_7"));
                mine7.setPosition(position.x, position.y);
                window.draw(mine7);
                break;
            }
            case 8: {
                sf::Sprite mine8(TextureManager::GetTexture("number_8"));
                mine8.setPosition(position.x, position.y);
                window.draw(mine8);
                break;
            }
            default:
                break;
        }
    }

    void DrawFlag(sf::RenderWindow& window) {
        sf::Sprite flag(TextureManager::GetTexture("flag"));
        flag.setPosition(position);
        window.draw(flag);
    }

    void DrawMine(sf::RenderWindow& window) {
        sf::Sprite hiddenTile(TextureManager::GetTexture("mine"));
        reveal = hiddenTile;
        reveal.setPosition(position);
        window.draw(reveal);
    }

    sf::FloatRect GetBounds() {
        return reveal.getGlobalBounds();
    }
};

class TileArray {
    int rowNum;
    int colNum;
    int minesLeft;
    int flagNum;
public:
    vector<Tile*> tArray;

    TileArray(int r, int c, int mineNumber) {
        rowNum = r;
        colNum = c;
        minesLeft = mineNumber;
    }

    void SetMinesLeft(int n) {
        minesLeft = n;
    }

    int GetMinesLeft() {
        return minesLeft;
    }

    int SetTiles(int r, int c, int mineNumber) // r = total rows, c = total columns, mineNumber = number of mines
    {
        sf::Vector2f position;
        for (int row = 0; row < r; row++) {
            for (int col = 0; col < c; col++) {
                position.x = col * 32;
                position.y = row * 32;
                Tile *t = new Tile(position);
                tArray.push_back(t);
            }
        }
//        cout << "size of tArray: " << tArray.size() << endl;

        minesLeft = mineNumber;
        flagNum = 0;
        return 0;
    }

    int SetNeighboringTiles(int r, int c, int mineNumber) {
        for (int row = 0; row < r; row++) {
            for (int col = 0; col < c; col++) {
                if (row - 1 >= 0 && row - 1 < rowNum && col - 1 >= 0 && col - 1 < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row - 1, col - 1));
                }
                if (row - 1 >= 0 && row - 1 < rowNum && col >= 0 && col < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row - 1, col));
                }
                if (row - 1 >= 0 && row - 1 < rowNum && col + 1 >= 0 && col + 1 < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row - 1, col + 1));
                }
                if (row >= 0 && row < rowNum && col - 1 >= 0 && col - 1 < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row, col - 1));
                }
                if (row >= 0 && row < rowNum && col + 1 >= 0 && col + 1 < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row, col + 1));
                }
                if (row + 1 >= 0 && row + 1 < rowNum && col - 1 >= 0 && col - 1 < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row + 1, col - 1));
                }
                if (row + 1 >= 0 && row + 1 < rowNum && col >= 0 && col < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row + 1, col));
                }
                if (row + 1 >= 0 && row + 1 < rowNum && col + 1 >= 0 && col + 1 < colNum) {
                    GetTile(row, col)->neighbors.push_back(GetTile(row + 1, col + 1));
                }
            }
        }
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                int mines = 0;
                for(int k = 0; k < tArray[i * c + j]->neighbors.size(); k++) {
                    if(tArray[i * c + j]->neighbors[k]->isMine == 1) {
                        mines++;
                    }
                }
                tArray[i * c + j]->SetMineNum(mines);
            }
        }
        return 0;
    }

    Tile* GetTile(int r, int c) {
        return tArray[r * colNum + c];
    }

    void Draw(sf::RenderWindow& window, bool isDebug, bool isReset, bool &isGameLost) {
        if (isReset) {
            for (int i = 0; i < rowNum; i++) {
                for (int j = 0; j < colNum; j++) {
                    tArray[i * colNum + j]->DrawHiddenTile(window);
                    tArray[i * colNum + j]->tileStatus = 0;
                    if(isDebug && tArray[i * colNum + j]->isMine)
                        tArray[i * colNum + j]->DrawMine(window);
                }
            }
            return;
        }
        else {
            //cout << "hello" << endl;
            for (int i = 0; i < rowNum; i++) {
                for (int j = 0; j < colNum; j++) {
//                    cout << "i: " << i << ", j: " << j << endl;
                    if (tArray[i * colNum + j]->tileStatus == 1) {
                        tArray[i * colNum + j]->DrawFlag(window);
                    }
                    if (tArray[i * colNum + j]->tileStatus == 2) {
                        if(tArray[i * colNum + j]->isMine) { // mineNum = 0
                            tArray[i * colNum + j]->DrawEmpty(window);
                            tArray[i * colNum + j]->DrawMine(window);
                            isGameLost = true;
                            GameLost(window);
                        }
                        else { // check tileStatus
                            if(tArray[i * colNum + j]->GetMineNum() > 0) {
//                                cout << "draw number" << endl;
                                tArray[i * colNum + j]->DrawEmpty(window);
                                tArray[i * colNum + j]->DrawNumber(window, tArray[i * colNum + j]->GetMineNum());
                            }
                            else {
//                                cout << "draw empty" << endl;
                                tArray[i * colNum + j]->DrawEmpty(window);
//                                cout << "i: " << i << ", j: " << j << endl;
                            }
                        }
                    }
                    if (isDebug && tArray[i * colNum + j]->isMine)
                        tArray[i * colNum + j]->DrawMine(window);
                }
            }
        }
    }

    void CheckTileStatus(int row, int col) // input row and column of the tile
    {
//        tArray[row * colNum + col]->DrawEmpty(window);
        if(tArray[row * colNum + col]->tileStatus == 2 || tArray[row * colNum + col]->tileStatus == 1) {
            return;
        }
        tArray[row * colNum + col]->tileStatus = 2;
        if (tArray[row * colNum + col]->GetMineNum() > 0) {
//            tArray[row * colNum + col]->DrawNumber(window, tArray[row * colNum + col]->GetMineNum());
            return;
        }
        else {
            if (row - 1 >= 0 && row - 1 < rowNum && col - 1 >= 0 && col - 1 < colNum) {
                CheckTileStatus(row - 1, col - 1);
            }
//            cout << "1" << endl;
            if (row - 1 >= 0 && row - 1 < rowNum && col >= 0 && col < colNum) {
                CheckTileStatus(row - 1, col);
            }
//            cout << "2" << endl;
            if (row - 1 >= 0 && row - 1 < rowNum && col + 1 >= 0 && col + 1 < colNum) {
                CheckTileStatus(row - 1, col + 1);
            }
//            cout << "3" << endl;
            if (row >= 0 && row < rowNum && col - 1 >= 0 && col - 1 < colNum) {
                CheckTileStatus(row, col - 1);
            }
//            cout << "4" << endl;
            if (row >= 0 && row < rowNum && col + 1 >= 0 && col + 1 < colNum) {
                CheckTileStatus(row, col + 1);
            }
//            cout << "5" << endl;
            if (row + 1 >= 0 && row + 1 < rowNum && col - 1 >= 0 && col - 1 < colNum) {
                CheckTileStatus(row + 1, col - 1);
            }
//            cout << "6" << endl;
            if (row + 1 >= 0 && row + 1 < rowNum && col >= 0 && col < colNum) {
                CheckTileStatus(row + 1, col);
            }
//            cout << "7" << endl;
            if (row + 1 >= 0 && row + 1 < rowNum && col + 1 >= 0 && col + 1 < colNum) {
                CheckTileStatus(row + 1, col + 1);
            }
//            cout << "8" << endl;
        }
    }

    void GameLost(sf::RenderWindow& window) {
        for (int i = 0; i < rowNum; i++) {
            for (int j = 0; j < colNum; j++) {
                if(tArray[i * colNum + j]->isMine)
                    tArray[i * colNum + j]->DrawMine(window);
            }
        }
    }

    bool IsGameWon() {
        bool won = true;
        for (int i = 0; i < rowNum; i++) {
            for (int j = 0; j < colNum; j++) {
                if (!tArray[i * colNum + j]->isMine) {
                    if(tArray[i * colNum + j]->tileStatus == 2) {}
                    else {
                        won = false;
                        return false;
                    }
                }
                if(tArray[i * colNum + j]->isMine) {
                    if(tArray[i * colNum + j]->tileStatus == 1) {}
                    else {
                        won = false;
                        return false;
                    }
                }
            }
        }
        return won;
    }

    int GetRowNum() {
        return rowNum;
    }

    int GetColNum() {
        return colNum;
    }
};

#endif //MAIN_CPP_TILE_H
