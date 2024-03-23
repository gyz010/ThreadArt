//
// Created by gyz on 24.11.23.
//

#ifndef THREADART_LINETEST_H
#define THREADART_LINETEST_H
#include "Bresenham.h"
#include "SFML/Graphics.hpp"

class LineTest {
    static size_t j_iter;
    static size_t i_iter;
    static size_t imageSize;
public:
    static std::vector<std::vector<uint8_t>> lineOnCanvas;
    static void nextLine(const std::vector<sf::Vector2i> &vertices);
    static void setImageSize(const size_t &imgSize){imageSize = imgSize;};
    static void zeroIterators();

};


#endif //THREADART_LINETEST_H
