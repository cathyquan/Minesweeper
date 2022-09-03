//
// Created by Cathy Quan on 12/6/21.
//

#ifndef MAIN_CPP_RANDOM_H
#define MAIN_CPP_RANDOM_H
#include <random>

class Random {
    static std::mt19937 random;
public:
    static int Int(int min, int max);
    static float Float(float min, float max);
};

#endif //MAIN_CPP_RANDOM_H
