//
// Created by Kuba on 24.09.2023.
//

#ifndef THREADART_BRESENHAM_H
#define THREADART_BRESENHAM_H

#include <iostream>
#include <vector>
#include <cstdint>
#include "SFML/System.hpp"

class Bresenham {
    static uint32_t diameter;
public:
    static std::vector<sf::Vector2i> connectVertices(const sf::Vector2i &v1, const sf::Vector2i &v2);
    static void setDiameter(const uint32_t &diameter);
};


#endif //THREADART_BRESENHAM_H
