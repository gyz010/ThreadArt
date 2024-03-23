//
// Created by gyz on 24.11.23.
//

#include "../inc/LineTest.h"

size_t LineTest::j_iter ;
size_t LineTest::i_iter ;
size_t LineTest::imageSize ;
std::vector<std::vector<uint8_t>> LineTest::lineOnCanvas;


void LineTest::nextLine(const std::vector<sf::Vector2i> &vertices) {
    ///Iterating through every line possible
    j_iter++;
//    if(j_iter>=vertices.size()) {
//        j_iter=0;
//        i_iter++;
//    }
//    i_iter = i_iter%vertices.size();
    i_iter++;
    i_iter = i_iter % vertices.size();
    j_iter = j_iter%vertices.size();
    std::vector<sf::Vector2i> line = Bresenham::connectVertices(vertices[i_iter], vertices[j_iter]);
    lineOnCanvas.clear();
    lineOnCanvas.resize(imageSize);
    for(size_t i=0; i<imageSize; ++i) {
        lineOnCanvas[i].resize(imageSize);
    }
    for(size_t i=0; i<line.size(); ++i) {
        lineOnCanvas[line[i].x][line[i].y] = 255;
    }
}

void LineTest::zeroIterators() {
    i_iter = 0;
    j_iter = 200;
}
