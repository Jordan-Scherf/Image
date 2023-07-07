


#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>


struct pixel{
    unsigned short red;
    unsigned short green;
    unsigned short blue;
};
void read(pixel image[][1024], int width, int height, std::ifstream& infile);
void print(pixel image[][1024], int width, int height, std::ofstream& infile);
void negate(pixel image[][1024], int width, int height, int color_depth);
void ReverseCol(pixel image[][1024], int width, int height);
void ReverseRow(pixel image[][1024], int width, int height);

int main(int argc, const char *argv[]){

    if(argc == 3 && strcmp(argv[1], argv[2]) != 0){
        std::ifstream infile;  // input File
        std::ofstream outfile;  // Output File

        // attempt to open files
        infile.open(argv[1]);
        outfile.open(argv[2]);

        if(infile && outfile && infile.get() == 'P' && infile.get() == '3'){
            pixel image[1024][1024] = { 0, 0 ,0 };
            pixel temp;
            int width = 0;
            int height = 0;
            int color_depth = 0;

            infile.ignore(256,' ');
            infile >> width >> height >> color_depth;

            if(width > 1024 || height > 1024 || color_depth > 255){
                std::cout << "This is Incorrect Format";
            }else{
                std::cout << argv[1] << " Has " << width << " X " << height <<
                      " with " << color_depth <<" intenstity levels./n";


            read(image, width, height, infile);

            negate(image, width, height, color_depth);

            ReverseCol(image, width, height);

            ReverseRow(image, width, height);

            print(image, width, height, outfile);

            }
        }
    }else{
      std::cout<<"Incorrect File or Wrong Format";
    }


    return 0;
}

void read(pixel image[][1024], int width, int height , std::ifstream& infile){

    for(int i = 0; i < width; i++){
        for(int x = 0; x < height; x++){
            infile >> image[i][x].red;
            infile >> image[i][x].green;
            infile >> image[i][x].blue;
        }
    }
}


void negate(pixel image[][1024], int width, int height, int color_depth){

    for (int i = 0; i < width; i++){
        for(int x = 0; x < height; x++){
            image[i][x].red = color_depth - image[i][x].red;
            image[i][x].green = color_depth - image[i][x].green;
            image[i][x].blue = color_depth - image[i][x].blue;
        }
    }
}



void ReverseRow(pixel image[][1024], int width, int height){
    pixel temp;
    for(int col = 0;col < width; col++){
            for(int row = 0; row < height/2; row++) {
                temp = image[row][col];
                image[row][col] = image[height - row - 1][col];
                image[height - row - 1][col] = temp;
            }
    }
}


void ReverseCol(pixel image[][1024], int width, int height){
    pixel temp;
    for(int i = 0; i <= height; i++) {
        for(int j = 0; j<= width/2; j++) {
            temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = temp;
        }
    }
}


void print(pixel image[][1024], int width, int height, std::ofstream& outfile){
    for(int i = 0; i < width; i++){
        for(int x = 0; x < height; x++){
            outfile << image[i][x].red << " ";
            outfile << image[i][x].green << " ";
            outfile << image[i][x].blue << " ";
        }
    }
}