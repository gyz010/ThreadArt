//
// Created by Asus on 12.11.2023.
//

#ifndef THREADART_IMAGETRANSFORM_H
#define THREADART_IMAGETRANSFORM_H

#include <SFML/Graphics.hpp>

class ImageTransform {
public:
    static void loadImage(const std::string &path, std::vector<std::vector<uint8_t>> &threadImage);
};


#endif //THREADART_IMAGETRANSFORM_H
