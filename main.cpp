#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Board.h"
using namespace std;

int main()
{
    int rows = 0;
    int cols = 0;
    int numMines = 0;

    ifstream read("boards/config.cfg");
    if(read.is_open()) {
        string line;
        getline(read, line);
        cols = stoi(line);
        getline(read, line);
        rows = stoi(line);
        getline(read, line);
        numMines = stoi(line);
    }
    else {
        cout << "problems opening file" << endl;
    }

    unsigned int width = cols * 32;
    unsigned int height = rows * 32 + 88;
    unsigned int tileCount = rows * cols;

//    cout << "width: " << width << ", height: " << height << endl;

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    Board newGame(rows, cols, numMines);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // drawing the board
            window.clear(sf::Color(255, 255, 255, 255));

            newGame.Draw(window);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                    newGame.RightClick(mousePosition);
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

                    int option = newGame.LeftClick(mousePosition);
                    if (option >= 10) {
                        newGame.TileClicked(window, option - 10);
                    }
                    else {
                        switch (option) {
                            case 0:
                                newGame.Reset(window);
                                newGame.Random();
                                break;
                            case 1:
                                newGame.Reset(window);
                                newGame.Board1();
                                break;
                            case 2:
                                newGame.Reset(window);
                                newGame.Board2();
                                break;
                            case 3:
                                newGame.Reset(window);
                                newGame.Board3();
                                break;
                            case 4:
                                newGame.Debug(window);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                continue;
            }
            // display the board
            window.display();
        }
    }


#if 0
    unsigned int width = cols * 32;
    unsigned int height = rows * 32 + 88;
    unsigned int tileCount = rows * cols;

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    Game newGame = Game(window);
    Board testBoard1 = Board(rows, cols, numMines);
    vector<vector<string>> board1 = testBoard1.ReadBoardFile(2, newGame.tiles, window);

    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << board1[i][j];
        }
        cout << endl;
    }

    sf::Sprite grid(TextureManager::GetTexture("tile_hidden"));

    sf::Sprite happyFace(TextureManager::GetTexture("face_happy"));
    happyFace.setOrigin(32, 0);
    happyFace.setPosition(width / 2, 32 * rows);

    sf::Sprite debug(TextureManager::GetTexture("debug"));
    debug.setOrigin(0, 0);
    debug.setPosition(width / 2 + 32 + 64, 32 * rows);

    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    test1.setOrigin(0, 0);
    test1.setPosition(width / 2 + 32 + 64 * 2, 32 * rows);

    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    test2.setOrigin(0, 0);
    test2.setPosition(width / 2 + 32 + 64 * 3, 32 * rows);

    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    test3.setOrigin(0, 0);
    test3.setPosition(width / 2 + 32 + 64 * 4, 32 * rows);

    sf::Sprite flag(TextureManager::GetTexture("flag"));
    flag.setOrigin(0, 0);

    vector<sf::Sprite> flags;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                auto pointer = sf::Mouse::getPosition(window);
                cout << "x-position: " << pointer.x << ", y-position: " << pointer.y << endl;
                int tileX = pointer.x - pointer.x % 32;
                int tileY = pointer.y - pointer.y % 32;
                if (event.mouseButton.button == sf::Mouse::Right) {
                    flag.setPosition(tileX, tileY);
                    flags.push_back(flag);
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                    cout << "hello" << endl;
                    cout << "rows: " << rows << ", cols: " << cols << endl;
                    for(int i = 0; i < rows; i++) {
                        for(int j = 0; j < cols; j++) {
                            sf::FloatRect fRect = newGame.tiles[i][j].GetBounds();
                            cout << "left: " << fRect.left << ", top: " << fRect.top << ", width: " << fRect.width << ", height: " << fRect.height << endl;
//                            tiles[0][0].Draw(window);
//                            if(tiles[i][j].GetBounds().contains(mousePosition)) {
//                                tiles[i][j].Draw(window);
//                            }
                        }
                    }
                }
            }
        }

        // drawing the board
        window.clear(sf::Color(255, 255, 255, 255));
        for(int i = 0; i < width; i += 32) {
            for(int j = 0; j < height - 32 * 3; j += 32) {
                grid.setPosition(i, j);
                window.draw(grid);
            }
        }
        for(unsigned int i = 0; i < flags.size(); i++) {
            window.draw(flags[i]);
        }
        window.draw(happyFace);
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);

        sf::Sprite hundred(TextureManager::GetTexture("digits"));
        hundred.setTextureRect(sf::Rect<int>(0, 0, 21, 32));
        hundred.setPosition(0, 512);
        sf::Sprite tens(TextureManager::GetTexture("digits"));
        tens.setTextureRect(sf::Rect<int>(21 * 5, 0, 21, 32));
        tens.setPosition(21, 512);
        sf::Sprite ones(TextureManager::GetTexture("digits"));
        ones.setTextureRect(sf::Rect<int>(0, 0, 21, 32));
        ones.setPosition(42, 512);

        window.draw(hundred);
        window.draw(tens);
        window.draw(ones);

        // display the board
        window.display();
    }

    TextureManager::Clear();
#endif
    return 0;
}