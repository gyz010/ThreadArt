//
// Created by Kuba on 24.09.2023.
//

#ifndef THREADART_CANVAS_H
#define THREADART_CANVAS_H

#include <vector>
#include <cstdint>
#include <cmath>
#include "SFML/Graphics.hpp"
#include <fstream>
#include <list>
#include "Bresenham.h"
#include <queue>
#include "ImageTransform.h"
class Canvas {
    const uint8_t darkness;
    uint32_t diameter;
    uint8_t linesPerScoring;
    size_t currentVerticeIndex;
    std::vector<std::vector<uint8_t>> threadImage;
    std::vector<std::vector<uint8_t>> originImage;
    std::vector<sf::Vector2i> vertices;
    sf::Vector2i currentVertice;
    sf::Vector2i previousVertice;
    std::vector<uint32_t> threadOrder;
    std::vector<std::queue<size_t>> bestLines;
    sf::Vector2i bestFitLine();
    void bestNLines(const size_t &verticeIndex);
    int calculateScore(const std::vector<sf::Vector2i> &pixels);

public:
    explicit Canvas(const uint32_t &numberOfVertices, const uint8_t &darkness);

    bool drawBestLine();
    bool drawLine();
    void draw(sf::RenderWindow &window);
    void drawImage(sf::RenderWindow &window, const std::vector<std::vector<uint8_t>> &image);
    uint32_t getDiameter() const {return diameter;}
};


#endif //THREADART_CANVAS_H
