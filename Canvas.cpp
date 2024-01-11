//
// Created by Kuba on 24.09.2023.
//

#include "Canvas.h"
#include <unistd.h>

Canvas::Canvas(const uint32_t &numberOfVertices, const uint8_t &darkness):
    darkness(darkness) {
    linesPerScoring = 25;

    ImageTransform::loadImage("../sobala.png", originImage);
    this->diameter = originImage.size();
    Bresenham::setDiameter(diameter);

    threadImage.resize(diameter);
    for(int i=0; i<diameter; i++) {
        threadImage[i].resize(diameter, 255);
    }
    const float radius = static_cast<float>(diameter)/2;
    const double deltaAngle = 2*M_PI/numberOfVertices;
    for(int i=0; i<numberOfVertices; i++) {
        vertices.emplace_back(static_cast<int>(radius+radius*cos(i*deltaAngle)), static_cast<int>(radius+radius*sin(i*deltaAngle)));
    }
    currentVerticeIndex = 0;
    currentVertice = previousVertice = vertices[0];
    bestLines.resize(vertices.size());

}

sf::Vector2i Canvas::bestFitLine() {
    int score;
    int bestScore=-1;
    int bestVerticeIndex=-1;
    std::vector<sf::Vector2i> pixels;
    for(int i=0; i<vertices.size(); i++) {
        if(vertices[i] == previousVertice or vertices[i] == currentVertice) {
            continue;
        }
        pixels = Bresenham::connectVertices(currentVertice, vertices[i]);
        score = calculateScore(pixels);
        if(score > bestScore) {
            bestScore = score;
            bestVerticeIndex = i;
        }
    }
    threadOrder.emplace_back(bestVerticeIndex);
    if(bestVerticeIndex == -1) {
        return {-1, -1};
    }
    return vertices[bestVerticeIndex];
}

int Canvas::calculateScore(const std::vector<sf::Vector2i> &pixels){
    long int difference=0;
    for(auto &pixel : pixels) {
        if(originImage[pixel.x][pixel.y]-threadImage[pixel.x][pixel.y] + darkness < 0) {
            difference+=static_cast<int>(pow(originImage[pixel.x][pixel.y]-threadImage[pixel.x][pixel.y] + darkness, 2));
        }
    }
    return difference;
}

bool Canvas::drawBestLine() {
    sf::Vector2i nextVertice = bestFitLine();
    if(nextVertice.x == -1 and nextVertice.y ==-1) {
        return false;
    }
    auto pixels = Bresenham::connectVertices(currentVertice, nextVertice);
    for(auto &pixel : pixels) {
        if(threadImage[pixel.x][pixel.y] - darkness > 0) {
            threadImage[pixel.x][pixel.y] -= darkness;
        }
        else {
            threadImage[pixel.x][pixel.y]=0;
        }
    }
    previousVertice = currentVertice;
    currentVertice = nextVertice;
    return true;

}

void Canvas::draw(sf::RenderWindow &window) {
    drawBestLine();
    sf::RectangleShape pixel;
    pixel.setSize({1, 1});
    sf::Color color = {255, 255, 255};
    for(int i=0; i<diameter; i++) {
        for(int j=0; j<diameter; j++) {
            color.a = threadImage[i][j];
            pixel.setPosition(i, j);
            pixel.setFillColor(color);
            window.draw(pixel);
        }
    }
}




