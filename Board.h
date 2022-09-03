//
// Created by Cathy Quan on 12/7/21.
//

#ifndef MAIN_CPP_BOARD_H
#define MAIN_CPP_BOARD_H

#include <string>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "Digits.h"
#include "Button.h"
#include "TextureManager.h"
#include "Random.h"
using namespace std;

class Board {
public:
    TileArray tileArray;
    Digits mineCounter;
    Button faceBtn;
    Button debugBtn;
    Button testBoard1Btn;
    Button testBoard2Btn;
    Button testBoard3Btn;
    int numMines;
    bool isDebug;
    bool isReset;
    bool isGameLost;
    bool isGameWon;
    vector<sf::Sprite> flags;
    unsigned int width;
    unsigned int height;
    unsigned int rows;
    unsigned int cols;

    Board(int r = 0 , int c = 0, int n = 0): tileArray(r, c, n), mineCounter(n) {
        tileArray.SetTiles(r, c, n);
        Random();
        tileArray.SetNeighboringTiles(r, c, n);

        numMines = n;
        rows = r;
        cols = c;
        width = c * 32;
        height = r * 32;

        sf::Sprite happyFace(TextureManager::GetTexture("face_happy"));
        sf::Vector2f position1;
        position1.x = width / 2 - 16;
        position1.y = height;
        happyFace.setOrigin(32, 0);
        faceBtn.initialize(position1, happyFace);

        sf::Vector2f position2;
        position2.x = width / 2 + 32 + 64 + 48;
        position2.y = height;
        sf::Sprite debug(TextureManager::GetTexture("debug"));
        debug.setOrigin(0, 0);
        debugBtn.initialize(position2, debug);

        sf::Vector2f position3;
        position3.x = width / 2 + 32 + 64 * 2 + 48;
        position3.y = height;
        sf::Sprite test1(TextureManager::GetTexture("test_1"));
        test1.setOrigin(0, 0);
        testBoard1Btn.initialize(position3, test1);

        sf::Vector2f position4;
        position4.x = width / 2 + 32 + 64 * 3 + 48;
        position4.y = height;
        sf::Sprite test2(TextureManager::GetTexture("test_2"));
        test2.setOrigin(0, 0);
        testBoard2Btn.initialize(position4, test2);

        sf::Vector2f position5;
        position5.x = width / 2 + 32 + 64 * 4 + 48;
        position5.y = height;
        sf::Sprite test3(TextureManager::GetTexture("test_3"));
        test3.setOrigin(0, 0);
        testBoard3Btn.initialize(position5, test3);

        isDebug = false;
        isGameLost = false;
        isGameWon = false;
    }

    void Draw(sf::RenderWindow& window) {
        for (int i = 0; i < tileArray.GetRowNum(); i++) {
            for (int j = 0; j < tileArray.GetColNum(); j++) {
                tileArray.tArray[i * tileArray.GetColNum() + j]->DrawHiddenTile(window);
            }
        }
        tileArray.Draw(window, isDebug, isReset, isGameLost);
        faceBtn.Draw(window);
        debugBtn.Draw(window);
        testBoard1Btn.Draw(window);
        testBoard2Btn.Draw(window);
        testBoard3Btn.Draw(window);
        mineCounter.SetupDigits(tileArray.GetMinesLeft());
        mineCounter.DrawNumMines(window);
        isGameWon = tileArray.IsGameWon();
        if(isGameWon) {
            sf::Sprite winnerFace(TextureManager::GetTexture("face_win"));
            sf::Vector2f position1;
            position1.x = width / 2 - 16;
            position1.y = height;
            winnerFace.setOrigin(32, 0);
            winnerFace.setPosition(position1);
            window.draw(winnerFace);
            isGameWon = false;
        }
        if(isGameLost) {
            sf::Sprite loserFace(TextureManager::GetTexture("face_lose"));
            sf::Vector2f position1;
            position1.x = width / 2 - 16;
            position1.y = height;
            loserFace.setOrigin(32, 0);
            loserFace.setPosition(position1);
            window.draw(loserFace);
            isGameLost = false;
        }
    }

    int LeftClick(sf::Vector2f mousePosition) {
        for(int i = 0; i < tileArray.GetRowNum(); i++) {
            for(int j = 0; j < tileArray.GetColNum(); j++) {
                if((tileArray.tArray[i * tileArray.GetColNum() + j])->GetBounds().contains(mousePosition)) {
                    return 10 + i * tileArray.GetColNum() + j;
                }
            }
        }
        if(faceBtn.GetBounds().contains(mousePosition))
            return 0;
        if(testBoard1Btn.GetBounds().contains(mousePosition))
            return 1;
        if(testBoard2Btn.GetBounds().contains(mousePosition))
            return 2;
        if(testBoard3Btn.GetBounds().contains(mousePosition))
            return 3;
        if(debugBtn.GetBounds().contains(mousePosition))
            return 4;
        return -1;
    }

    int RightClick(sf::Vector2f mousePosition) {
        isReset = false;
        for(int i = 0; i < tileArray.GetRowNum(); i++) {
            for(int j = 0; j < tileArray.GetColNum(); j++) {
                if((tileArray.tArray[i * tileArray.GetColNum() + j])->GetBounds().contains(mousePosition)) {
                    if(tileArray.tArray[i * tileArray.GetColNum() + j]->tileStatus == 1) {
                        tileArray.tArray[i * tileArray.GetColNum() + j]->tileStatus = 0;
                        tileArray.SetMinesLeft(tileArray.GetMinesLeft() + 1);
                    }
                    else if(tileArray.tArray[i * tileArray.GetColNum() + j]->tileStatus == 0) {
                        tileArray.tArray[i * tileArray.GetColNum() + j]->tileStatus = 1;
                        tileArray.SetMinesLeft(tileArray.GetMinesLeft() - 1);
                    }
                }
            }
        }
        return 0;
    }

    void TileClicked(sf::RenderWindow& window, int tileNum) {
        isReset = false;
        tileArray.CheckTileStatus(tileNum / cols, tileNum % cols);
    }

    void Reset(sf::RenderWindow& window) {
        isReset = true;
        tileArray.SetMinesLeft(numMines);
        for(int i = 0; i < tileArray.tArray.size(); i++) {
            tileArray.tArray[i]->tileStatus = 0;
        }
    }

    void Random() {
        vector<int> randVals;
        int num = Random::Int(0, tileArray.GetColNum() * tileArray.GetRowNum() - 1);
        randVals.push_back(num);
        bool found;
        while (randVals.size() < tileArray.GetMinesLeft()) {
            int rand = Random::Int(0, tileArray.GetColNum() * tileArray.GetRowNum() - 1);
            for (int i = 0; i < randVals.size(); i++) {
                if (rand == randVals[i]) {
                    found = true;
                    break;
                }
                else {
                    found = false;
                }
            }
            if (!found)
                randVals.push_back(rand);
        }
        int mineNum = 0;
        for(int i = 0; i < tileArray.GetColNum() * tileArray.GetRowNum(); i++) {
            for (int j = 0; j < randVals.size(); j++) {
                if (i != randVals[j]) {
                    tileArray.tArray[i]->isMine = false;
                }
                else {
                    tileArray.tArray[i]->isMine = true;
                    mineNum++;
                    break;
                }

            }
        }
        for (int i = 0; i < tileArray.GetColNum() * tileArray.GetRowNum(); i++) {
            tileArray.tArray[i]->neighbors.clear();
        }
        tileArray.SetNeighboringTiles(rows, cols, numMines);
    }

    void ReadBoardFile(int num) {
        string fileName = "boards/testboard" + to_string(num) + ".brd";
        ifstream read(fileName);
        if (!read.is_open()) {
//            cout << "error opening file!" << endl;
        }
        string line;
        int row = 0;
        while (getline(read, line)) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '1')
                    tileArray.tArray[row * tileArray.GetColNum() + i]->isMine = 1;
                else
                    tileArray.tArray[row * tileArray.GetColNum() + i]->isMine = 0;
            }
            row++;
        }
        for (int i = 0; i < tileArray.GetColNum() * tileArray.GetRowNum(); i++) {
            tileArray.tArray[i]->neighbors.clear();
        }
        tileArray.SetNeighboringTiles(rows, cols, numMines);
    }

    void Board1() {
        ReadBoardFile(1);
    }

    void Board2() {
        ReadBoardFile(2);
    }

    void Board3() {
        ReadBoardFile(3);
    }

    void Debug(sf::RenderWindow& window) {
        if(!isDebug)
            isDebug = true;
        else
            isDebug = false;
    }
};

#endif //MAIN_CPP_BOARD_H
