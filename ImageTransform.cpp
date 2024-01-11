//
// Created by Asus on 12.11.2023.
//

#include <iostream>
#include "ImageTransform.h"



void ImageTransform::loadImage(const std::string &path, std::vector<std::vector<uint8_t>> &originImage) {
    sf::Image img;
    img.loadFromFile(path);
    uint32_t imageSize = std::min(img.getSize().x, img.getSize().y);
    uint32_t oversize = std::max(img.getSize().x, img.getSize().y) - imageSize;
    originImage.resize(imageSize);
    for(auto &e : originImage) {
        e.resize(imageSize);
    }
    auto pixelPtr = img.getPixelsPtr();
    int n;
    for(int i=0; i<imageSize; i++) {
        for(int j=0; j<imageSize; j++) {
            if(img.getSize().x > img.getSize().y)
                n = (i * (imageSize + oversize) + j) * 4;
            else
                n = (i*(imageSize) + j)*4;
            ///NTSC Grayscale formula
            originImage[j][i] = static_cast<uint8_t>
                                (static_cast<float>(pixelPtr[n]) * 0.299 +
                                static_cast<float>(pixelPtr[n+1] * 0.587 +
                                static_cast<float>(pixelPtr[n+2] * 0.114)));
        }
    }
}
