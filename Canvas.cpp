//
// Created by Kuba on 24.09.2023.
//

#include "Canvas.h"
#include <unistd.h>
#include <chrono>
#include <random>

Canvas::Canvas(const uint32_t &numberOfVertices, const uint8_t &darkness):
    darkness(darkness) {

    ImageTransform::loadImage("../wawr.png", originImage);
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
    currentVertice = previousVertice = vertices[0];
    bestLines.resize(vertices.size());

    scoringDistribution.resize(400);

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
    if(bestVerticeIndex == -1 or bestScore < 10) {
        return {-1, -1};
    }
    return vertices[bestVerticeIndex];
}

bool Canvas::isIncreasing(const size_t &index, const uint32_t &range) {
    int startingScore = calculateScore(vertices[index]);
    for(uint32_t i=1; i<=range; i++) {
        if(index+i >= vertices.size()) {
            break;
        }
        if(calculateScore(vertices[index+i]) > static_cast<int>(startingScore*1.05)) {
            return true;
        }
    }
    return false;
}

/* Uses fact that the scores of lines are in approximation locally sorted
   Doesn't give best result but good enough and fassst WIP*/
sf::Vector2i Canvas::fastFitLine(const uint32_t &range) {
    std::random_device rand;
    size_t left = rand()%(vertices.size()/2);
    size_t right = vertices.size() - 1;
    std::vector<sf::Vector2i> pixels;
    auto start = std::chrono::high_resolution_clock::now();
    while(left < right) {
        size_t mid = left + ((right - left) / 2);
        for(uint32_t i=0; i<=range; i++) {
            if (!isIncreasing(mid, range)) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time: " << duration.count()/1000.f << "ms" << std::endl;
    threadOrder.emplace_back(left);
    return vertices[left];
}

int Canvas::calculateScore(const std::vector<sf::Vector2i> &pixels){
    long int difference=0;
    for(auto &pixel : pixels) {
        if(originImage[pixel.x][pixel.y]-threadImage[pixel.x][pixel.y] + darkness < 0) {
            difference+=static_cast<int>((originImage[pixel.x][pixel.y]-threadImage[pixel.x][pixel.y] + darkness, 2));
        }
    }
    //Statistics
    if(distributionIndex<scoringDistribution.size()) {
        scoringDistribution[distributionIndex].emplace_back(difference);
    }
    return difference;
}



int Canvas::calculateScore(const sf::Vector2i &vertex){
    std::vector<sf::Vector2i> pixels = Bresenham::connectVertices(currentVertice, vertex);
    long int difference=0;
    for(auto &pixel : pixels) {
        if(originImage[pixel.x][pixel.y]-threadImage[pixel.x][pixel.y] + darkness < 0) {
            difference+=static_cast<int>((originImage[pixel.x][pixel.y]-threadImage[pixel.x][pixel.y] + darkness) *
                    (originImage[pixel.x][pixel.y]-threadImage[pixel.x][pixel.y] + darkness));
        }
    }
    return difference;
}

bool Canvas::drawBestLine() {
//    sf::Vector2i nextVertice = bestFitLine();
    sf::Vector2i nextVertice = fastFitLine(2);

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

    //Statistics
    distributionIndex++;

    return true;

}


void Canvas::draw(sf::RenderWindow &window) {
    for(int i=0; i<100; i++) {
        drawBestLine();
    }
    writeStatsToFile();
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

void Canvas::writeStatsToFile() {
    if(distributionIndex!=10) {
        return;
    }
    std::fstream stats("../stats.txt", std::ios::out);
    for(size_t i=0; i<scoringDistribution.size(); i++) {
        for(size_t j=0; j<scoringDistribution[i].size(); j++) {
            stats << scoringDistribution[i][j] << " ";
        }
        stats << std::endl;
    }
    stats.close();
}




