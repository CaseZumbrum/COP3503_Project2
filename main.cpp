#include <iostream>
#include "image.h"
#include "image_reader.h"
#include <cstring>
#include <fstream>

bool check_exist(string file){
    ifstream f(file);
    return f.good();
}

bool check_tga(string file){
    return file.size() <= 4 || file.substr(file.size() - 4) == ".tga";
}

bool check_number(string s){
    if(s == "-"){
        return false;
    }
    if(s.at(0) != '-' && !isdigit(s.at(0))){
        return false;
    }
    for(int i = 1; i < s.size(); i++){
        if(!isdigit(s.at(i))){
            return false;
        }
    }
    return true;
}


using namespace std;
int main(int argc, char* argv[]) {
    image_reader printer;


    int count = 1;
    if(argc == 1 || strcmp(argv[1], "--help") == 0){
        cout << "Project 2: Image Processing, Spring 2024\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }
    string outfile = argv[1];
    count++;
    if(!check_tga(outfile)){
        cout << "Invalid file name." << endl;
        return 0;
    }
    if(argc == 2){
        cout << "Invalid file name." << endl;
        return 0;
    }
    string trackingfile = argv[2];
    count++;
    if(!check_tga(trackingfile)){
        cout << "Invalid file name." << endl;
        return 0;
    }
    else if(!check_exist(trackingfile)){
        cout << "File does not exist." << endl;
        return 0;
    }

    image tracking = printer.read(trackingfile);

    if (argc == 3) {
        cout << "Invalid method name." << endl;
        return 0;
    }
    cout << tracking.arr.at(301).at(301).green << endl;
    while(count < argc) {
        string cmd = argv[count];
        count++;
        if (cmd == "multiply") {

            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string base = argv[count];
            count++;
            if (!check_tga(base)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            } else if (!check_exist(base)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            image two = printer.read(base);
            tracking = printer.Multiply(tracking, two);


        }
        else if (cmd == "subtract") {

            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string base = argv[count];
            count++;
            if (!check_tga(base)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            } else if (!check_exist(base)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            image two = printer.read(base);
            tracking = printer.Subtract(tracking, two);


        }
        else if (cmd == "overlay") {

            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string base = argv[count];
            count++;
            if (!check_tga(base)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            } else if (!check_exist(base)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            image two = printer.read(base);
            tracking = printer.Overlay(tracking, two);


        }
        else if (cmd == "screen") {

            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string base = argv[count];
            count++;
            if (!check_tga(base)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            } else if (!check_exist(base)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            image two = printer.read(base);
            tracking = printer.Screen(two, tracking);


        }

        else if(cmd == "combine"){
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }

            string base1 = argv[count];
            count++;
            if (!check_tga(base1)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            } else if (!check_exist(base1)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            image two = printer.read(base1);
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }

            string base2 = argv[count];
            count++;
            if (!check_tga(base2)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            } else if (!check_exist(base2)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            image three = printer.read(base2);
            tracking = printer.combine(three,two,tracking);
        }
        else if(cmd == "flip"){
            tracking = printer.flip(tracking);
        }
        else if(cmd == "onlyred"){
            tracking = printer.onlyred(tracking);
        }
        else if(cmd == "onlygreen"){
            tracking = printer.onlygreen(tracking);
        }
        else if(cmd == "onlyblue"){
            tracking = printer.onlyblue(tracking);
        }
        else if(cmd == "addred"){
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string s = argv[count];
            if(!check_number(s)){
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            int add = stoi(s);
            count++;
            tracking = printer.addred(tracking, add);
        }
        else if(cmd == "addblue"){
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string s = argv[count];
            if(!check_number(s)){
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            int add = stoi(s);
            count++;
            tracking = printer.addblue(tracking, add);
        }
        else if(cmd == "addgreen"){
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string s = argv[count];
            if(!check_number(s)){
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            int add = stoi(s);
            count++;
            tracking = printer.addgreen(tracking, add);

        }
        else if(cmd == "scalered"){
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string s = argv[count];
            if(!check_number(s)){
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            int scale = stoi(s);
            count++;
            tracking = printer.scalered(tracking, scale);
        }
        else if(cmd == "scalegreen"){
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string s = argv[count];
            if(!check_number(s)){
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            int scale = stoi(s);
            count++;
            tracking = printer.scalegreen(tracking, scale);
        }
        else if(cmd == "scaleblue"){
            if (count == argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            string s = argv[count];
            if(!check_number(s)){
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
            int scale = stoi(s);
            count++;
            tracking = printer.scaleblue(tracking, scale);
        }
        else {
            cout << "Invalid method name." << endl;
            return 0;
        }
    }

    cout << tracking.arr.at(301).at(301).green << endl;
    printer.write(outfile, tracking);
    cout << count << endl << argc << endl;
    return 0;
}
