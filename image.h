//
// Created by casez on 3/6/2024.
//


#pragma once
#include <vector>
using namespace std;

class image {
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
        Header& operator=(const Header& other){
            this->idLength = other.idLength;
            this->colorMapType= other.colorMapType;
            this->dataTypeCode= other.dataTypeCode;
            this->colorMapOrigin= other.colorMapOrigin;
            this->colorMapLength= other.colorMapLength;
            this->colorMapDepth= other.colorMapDepth;
            this->xOrigin= other.xOrigin;
            this->yOrigin= other.yOrigin;
            this->width= other.width;
            this->height= other.height;
            this->bitsPerPixel= other.bitsPerPixel;
            this->imageDescriptor= other.imageDescriptor;
            return *this;
        }
        };
public:
    struct Color{
        int blue;
        int green;
        int red;
    };

    Header header;
    vector<vector<Color>> arr;
    image();
    ~image();
};



