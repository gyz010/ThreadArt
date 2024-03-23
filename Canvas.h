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
    std::vector<std::vector<uint8_t>> threadImage;
    std::vector<std::vector<uint8_t>> originImage;
    std::vector<sf::Vector2i> vertices;
    sf::Vector2i currentVertice;
    sf::Vector2i previousVertice;
    std::vector<uint32_t> threadOrder;
    std::vector<std::queue<size_t>> bestLines;

    bool isIncreasing(const size_t &index, const uint32_t &range);
    sf::Vector2i bestFitLine();
    sf::Vector2i fastFitLine(const uint32_t &range);
    int calculateScore(const std::vector<sf::Vector2i> &pixels);
    int calculateScore(const sf::Vector2i &vertex);

    void writeStatsToFile();

public:
    explicit Canvas(const uint32_t &numberOfVertices, const uint8_t &darkness);

    bool drawBestLine();
    void draw(sf::RenderWindow &window);
    uint32_t getDiameter() const {return diameter;}

    //Statistics
    std::vector<std::vector<int32_t>> scoringDistribution;
    size_t distributionIndex;
};


#endif //THREADART_CANVAS_H
