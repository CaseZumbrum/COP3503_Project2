//
// Created by casez on 3/6/2024.
//

#include <fstream>
#include "image.h"
using namespace std;
class image_reader {

public:
    image_reader();
    image read(string file);
    void write(string file, image i);
    image Multiply(image& one, image& two);
    image Screen(image& one, image& two);
    image Subtract(image& one, image& two);
    image Add(image& one, image& two);
    image Overlay(image& one, image& two);
    image onlygreen(image& one);
    image onlyred(image& one);
    image onlyblue(image& one);
    image addred(image& one, int pixel);
    image addgreen(image& one, int pixel);
    image addblue(image& one, int pixel);
    image scalered(image& one, int scale);
    image scalegreen(image& one, int scale);
    image scaleblue(image& one, int scale);
    image combine(image& one, image& two, image& three);
    image flip(image& one);
};


