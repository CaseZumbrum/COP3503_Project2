//
// Created by casez on 3/6/2024.
//

#ifndef PROJECT2_IMAGE_H
#define PROJECT2_IMAGE_H


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
        };
    struct Color{
        int blue;
        int green;
        int red;
    };
    Header header;
    Color* arr;
};


#endif //PROJECT2_IMAGE_H
