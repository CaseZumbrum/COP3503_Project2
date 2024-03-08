//
// Created by casez on 3/6/2024.
//

#include "image_reader.h"
#include "image.h"
#include <vector>
#include <iostream>
using namespace std;
image_reader::image_reader() {

}
image image_reader::read(string file){
    ifstream read(file, ios_base::binary);
    image i;
    short* x = new short;
    float* xfloat = new float;
    char* arr = new char;

    read.read(arr,1);
    i.header.idLength = *arr;
    read.read(arr,1);
    i.header.colorMapType = *arr;
    read.read(arr,1);
    i.header.dataTypeCode = *arr;
    read.read(reinterpret_cast<char*>(x),2);
    i.header.colorMapOrigin = *x;
    read.read(reinterpret_cast<char*>(x),2);
    i.header.colorMapLength = *x;
    read.read(arr,1);
    i.header.colorMapDepth = *arr;
    read.read(reinterpret_cast<char*>(x),2);
    i.header.xOrigin = *x;
    read.read(reinterpret_cast<char*>(x),2);
    i.header.yOrigin = *x;
    read.read(reinterpret_cast<char*>(x),2);
    i.header.width = *x;
    read.read(reinterpret_cast<char*>(x),2);
    i.header.height = *x;
    read.read(arr,1);
    i.header.bitsPerPixel = *arr;
    read.read(arr,1);
    i.header.imageDescriptor = *arr;

    unsigned char* pixel = new unsigned char;
    for(int j = 0; j < i.header.width; j++){
        i.arr.push_back({});
        for(int k = 0; k < i.header.height; k++){
            image::Color c;

            read.read((char*)pixel,1);
            c.blue = static_cast<unsigned int>(*pixel);


            read.read((char*)pixel,1);
            c.green = static_cast<unsigned int>(*pixel);
            read.read((char*)pixel,1);
            c.red = static_cast<unsigned int>(*pixel);
            i.arr.at(j).push_back(c);

        }
    }
    delete xfloat;
    delete arr;
    delete x;
    delete pixel;
    return i;

}

void image_reader::write(string file, image i){
    ofstream write(file, ios_base::binary);



    write.write((char*)&i.header.idLength,1);

    write.write((char*)&i.header.colorMapType,1);

    write.write((char*)&i.header.dataTypeCode,1);

    write.write((char*)&i.header.colorMapOrigin,2);

    write.write((char*)&i.header.colorMapLength,2);

    write.write((char*)&i.header.colorMapDepth,1);

    write.write((char*)&i.header.xOrigin,2);

    write.write((char*)&i.header.yOrigin,2);

    write.write((char*)&i.header.width,2);

    write.write((char*)&i.header.height,2);

    write.write((char*)&i.header.bitsPerPixel,1);

    write.write((char*)&i.header.imageDescriptor,1);

    for(int j = 0; j < i.header.width; j++){
        for(int k = 0; k < i.header.height; k++){

            write.write(reinterpret_cast<char*>(&i.arr.at(j).at(k).blue),1);

            write.write(reinterpret_cast<char*>(&i.arr.at(j).at(k).green),1);

            write.write(reinterpret_cast<char*>(&i.arr.at(j).at(k).red),1);

        }
    }


}


image image_reader::Multiply(image& one, image& two) {
    image out;
    out.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        out.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            out.arr.at(i).push_back(c);
            float oneblue = (float)one.arr.at(i).at(j).blue/255;
            float twoblue = (float)two.arr.at(i).at(j).blue/255;
            //cout << oneblue << endl <<twoblue << endl;
            out.arr.at(i).at(j).blue = (int)(255.0f*(oneblue * twoblue) + 0.5f);
            float onegreen = (float)one.arr.at(i).at(j).green/255.0f;
            float twogreen = (float)two.arr.at(i).at(j).green/255.0f;
            out.arr.at(i).at(j).green = (int)(255.0f*(onegreen * twogreen) + 0.5f);
            float onered = (float)one.arr.at(i).at(j).red/255.0f;
            float twored = (float)two.arr.at(i).at(j).red/255.0f;
            out.arr.at(i).at(j).red = (int)(255.0f*(onered * twored) + 0.5f);
        }
    }
    return out;
}

image image_reader::Screen(image& one, image& two) {
    image out;
    out.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        out.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            out.arr.at(i).push_back(c);
            out.arr.at(i).at(j).blue = (int)(255.0f*(1 - ((1-one.arr.at(i).at(j).blue/255.0f) * (1-two.arr.at(i).at(j).blue/255.0f))) + 0.5f);
            out.arr.at(i).at(j).green = (int)(255.0f*(1 - ((1-one.arr.at(i).at(j).green/255.0f) * (1-two.arr.at(i).at(j).green/255.0f))) + 0.5f);
            out.arr.at(i).at(j).red = (int)(255.0f*(1 - ((1-one.arr.at(i).at(j).red/255.0f) * (1-two.arr.at(i).at(j).red/255.0f))) + 0.5f);
        }
    }
    return out;
}


image image_reader::Subtract(image& one, image& two) {
    image out;
    out.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        out.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            out.arr.at(i).push_back(c);
            out.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue - two.arr.at(i).at(j).blue;
            if(out.arr.at(i).at(j).blue < 0){
                out.arr.at(i).at(j).blue = 0;
            }

            out.arr.at(i).at(j).green = one.arr.at(i).at(j).green - two.arr.at(i).at(j).green;
            if(out.arr.at(i).at(j).green < 0){
                out.arr.at(i).at(j).green = 0;
            }

            out.arr.at(i).at(j).red = one.arr.at(i).at(j).red - two.arr.at(i).at(j).red;
            if(out.arr.at(i).at(j).red < 0){
                out.arr.at(i).at(j).red = 0;
            }
        }
    }
    return out;
}

image image_reader::Add(image& one, image& two) {
    image out;
    out.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        out.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            out.arr.at(i).push_back(c);
            out.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue + two.arr.at(i).at(j).blue;
            if(out.arr.at(i).at(j).blue > 255){
                out.arr.at(i).at(j).blue = 255;
            }

            out.arr.at(i).at(j).green = one.arr.at(i).at(j).green + two.arr.at(i).at(j).green;
            if(out.arr.at(i).at(j).green > 255){
                out.arr.at(i).at(j).green = 255;
            }

            out.arr.at(i).at(j).red = one.arr.at(i).at(j).red + two.arr.at(i).at(j).red;
            if(out.arr.at(i).at(j).red > 255){
                out.arr.at(i).at(j).red = 255;
            }
        }
    }
    return out;
}



image image_reader::Overlay(image& one, image& two) {
    image out;
    out.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        out.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            out.arr.at(i).push_back(c);

            if(two.arr.at(i).at(j).blue/255.0f <= 0.5f){
                out.arr.at(i).at(j).blue = (int)(255.0f*(2*(one.arr.at(i).at(j).blue/255.0f) * (two.arr.at(i).at(j).blue/255.0f)) + 0.5f);
                out.arr.at(i).at(j).green = (int)(255.0f*(2*(one.arr.at(i).at(j).green/255.0f) * (two.arr.at(i).at(j).green/255.0f)) + 0.5f);
                out.arr.at(i).at(j).red = (int)(255.0f*(2*(one.arr.at(i).at(j).red/255.0f) * (two.arr.at(i).at(j).red/255.0f)) + 0.5f);
            }
            else {
                out.arr.at(i).at(j).blue = (int) (255.0f * (1 - (2 * (1 - one.arr.at(i).at(j).blue / 255.0f) * (1 - two.arr.at(i).at(j).blue / 255.0f))) + 0.5f);
                out.arr.at(i).at(j).green = (int) (255.0f * (1 - (2 * (1 - one.arr.at(i).at(j).green / 255.0f) * (1 - two.arr.at(i).at(j).green / 255.0f))) + 0.5f);
                out.arr.at(i).at(j).red = (int) (255.0f * (1 - (2 * (1 - one.arr.at(i).at(j).red / 255.0f) * (1 - two.arr.at(i).at(j).red / 255.0f))) + 0.5f);
            }
        }
    }
    return out;
}

image image_reader::onlygreen(image &one) {
    image e;
    e.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        e.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            e.arr.at(i).push_back(c);
            e.arr.at(i).at(j).blue = one.arr.at(i).at(j).green;
            e.arr.at(i).at(j).green = one.arr.at(i).at(j).green;
            e.arr.at(i).at(j).red = one.arr.at(i).at(j).green;
        }
    }
    return e;
}
image image_reader::onlyred(image &one) {
    image e;
    e.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        e.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            e.arr.at(i).push_back(c);
            e.arr.at(i).at(j).blue = one.arr.at(i).at(j).red;
            e.arr.at(i).at(j).green = one.arr.at(i).at(j).red;
            e.arr.at(i).at(j).red = one.arr.at(i).at(j).red;
        }
    }
    return e;
}
image image_reader::onlyblue(image &one) {
    image e;
    e.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        e.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            e.arr.at(i).push_back(c);
            e.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue;
            e.arr.at(i).at(j).green = one.arr.at(i).at(j).blue;
            e.arr.at(i).at(j).red = one.arr.at(i).at(j).blue;
        }
    }
    return e;
}

image image_reader::addred(image &one, int pixel) {
    image two;
    two.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        two.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            two.arr.at(i).push_back(c);
            two.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue;
            two.arr.at(i).at(j).green = one.arr.at(i).at(j).green;
            two.arr.at(i).at(j).red = one.arr.at(i).at(j).red + pixel;

            if(two.arr.at(i).at(j).red < 0){
                two.arr.at(i).at(j).red = 0;
            }
            else if(two.arr.at(i).at(j).red > 255){
                two.arr.at(i).at(j).red = 255;
            }
        }
    }
    return two;
}

image image_reader::addgreen(image &one, int pixel) {
    image two;
    two.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        two.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            two.arr.at(i).push_back(c);
            two.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue;
            two.arr.at(i).at(j).green = one.arr.at(i).at(j).green + pixel;
            two.arr.at(i).at(j).red = one.arr.at(i).at(j).red;

            if(two.arr.at(i).at(j).green < 0){
                two.arr.at(i).at(j).green = 0;
            }
            else if(two.arr.at(i).at(j).green > 255){
                two.arr.at(i).at(j).green = 255;
            }
        }
    }
    return two;
}


image image_reader::addblue(image &one, int pixel) {
    image two;
    two.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        two.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            two.arr.at(i).push_back(c);
            two.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue + pixel;
            two.arr.at(i).at(j).green = one.arr.at(i).at(j).green;
            two.arr.at(i).at(j).red = one.arr.at(i).at(j).red;

            if(two.arr.at(i).at(j).blue < 0){
                two.arr.at(i).at(j).blue = 0;
            }
            else if(two.arr.at(i).at(j).blue > 255){
                two.arr.at(i).at(j).blue = 255;
            }
        }
    }
    return two;
}


image image_reader::scalered(image &one, int scale) {
    image two;
    two.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        two.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            two.arr.at(i).push_back(c);
            two.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue;
            two.arr.at(i).at(j).red = (int)(255.0f*((one.arr.at(i).at(j).red/255.0f) * scale ) + 0.5f);
            two.arr.at(i).at(j).green = one.arr.at(i).at(j).green;

            if(two.arr.at(i).at(j).red > 255){
                two.arr.at(i).at(j).red = 255;
            }
        }
    }
    return two;
}

image image_reader::scalegreen(image &one, int scale) {
    image two;
    two.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        two.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            two.arr.at(i).push_back(c);
            two.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue;
            two.arr.at(i).at(j).green = (int)(255.0f*((one.arr.at(i).at(j).green/255.0f) * scale ) + 0.5f);
            two.arr.at(i).at(j).red = one.arr.at(i).at(j).red;

            if(two.arr.at(i).at(j).green > 255){
                two.arr.at(i).at(j).green = 255;
            }
        }
    }
    return two;
}

image image_reader::scaleblue(image &one, int scale) {
    image two;
    two.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        two.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            two.arr.at(i).push_back(c);
            two.arr.at(i).at(j).red = one.arr.at(i).at(j).red;
            two.arr.at(i).at(j).blue = (int)(255.0f*((one.arr.at(i).at(j).blue/255.0f) * scale ) + 0.5f);
            two.arr.at(i).at(j).green = one.arr.at(i).at(j).green;

            if(two.arr.at(i).at(j).blue > 255){
                two.arr.at(i).at(j).blue = 255;
            }
        }
    }
    return two;
}

image image_reader::combine(image &one, image &two, image &three) {
    image combination;
    combination.header = one.header;
    for(int i = 0; i < one.header.width; i++){
        combination.arr.push_back({});
        for(int j = 0; j < one.header.height; j++){
            image::Color c;
            combination.arr.at(i).push_back(c);
            combination.arr.at(i).at(j).blue = one.arr.at(i).at(j).blue;
            combination.arr.at(i).at(j).green = two.arr.at(i).at(j).green;
            combination.arr.at(i).at(j).red = three.arr.at(i).at(j).red;
        }
    }
    return combination;
}

image image_reader::flip(image &one) {
    image flipped;
    flipped.header = one.header;
    for(int i = one.header.width-1; i >=0 ; i--){
        flipped.arr.push_back({});
        for(int j = one.header.height-1; j >=0; j--){
            image::Color c;
            flipped.arr.at((one.header.width-1)-i).push_back(c);
            flipped.arr.at((one.header.width-1)-i).at((one.header.height-1)-j).blue = one.arr.at(i).at(j).blue;
            flipped.arr.at((one.header.width-1)-i).at((one.header.height-1)-j).green = one.arr.at(i).at(j).green;
            flipped.arr.at((one.header.width-1)-i).at((one.header.height-1)-j).red = one.arr.at(i).at(j).red;
        }
    }
    return flipped;

}