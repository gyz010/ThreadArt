//
// Created by Kuba on 24.09.2023.
//

#include "../inc/Bresenham.h"

uint32_t Bresenham::diameter;

std::vector<sf::Vector2i> Bresenham::connectVertices(const sf::Vector2i &v1, const sf::Vector2i &v2) {
    int d, dx, dy, ai, bi, xi, yi;
    int x = v1.x, y = v1.y;
    std::vector<sf::Vector2i> pixels;
    // ustalenie kierunku rysowania
    if (v1.x < v2.x) {
        xi = 1;
        dx = v2.x - v1.x;
    }
    else {
        xi = -1;
        dx = v1.x - v2.x;
    }
    // ustalenie kierunku rysowania
    if (v1.y < v2.y) {
        yi = 1;
        dy = v2.y - v1.y;
    }
    else {
        yi = -1;
        dy = v1.y - v2.y;
    }
    // oś wiodąca OX
    if (dx > dy) {
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;
        // pętla po kolejnych x
        while (x != v2.x) {
            // test współczynnika
            if (d >= 0) {
                x += xi;
                y += yi;
                d += ai;
            }
            else {
                d += bi;
                x += xi;
            }
            if(x < diameter and y < diameter)
                pixels.emplace_back(x, y);
        }
    }
        // oś wiodąca OY
    else {
        ai = ( dx - dy ) * 2;
        bi = dx * 2;
        d = bi - dy;
        // pętla po kolejnych y
        while (y != v2.y) {
            // test współczynnika
            if (d >= 0) {
                x += xi;
                y += yi;
                d += ai;
            }
            else {
                d += bi;
                y += yi;
            }
            if(x < diameter and y < diameter)
                pixels.emplace_back(x, y);
        }
    }
    return pixels;
}

void Bresenham::setDiameter(const uint32_t &diameter) {
    Bresenham::diameter = diameter;
}
