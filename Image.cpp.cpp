/// @file Image.cpp
/// @author Jordan Scherf <5005736913@student.csn.edu>
/// @date 05/05/2021
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief This lab demonstates [The Use of Files and Structs]. Takes in an image (.ppm)
/// and outputs the image inverted, fliped, and floped.
/// @note Time Taken to Develop Program is about 7 hours
/// between days 05/01 and 05/05  with Assitance of
/// [TA William and TA Miguel]


#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

// Below is the struct for a pixel with RGB
struct pixel {
    unsigned short red;  // Red pixel color
    unsigned short green;  // Green pixel color
    unsigned short blue;  // Blue pixel color
};
void read(pixel image[][1024], int width, int height, std::ifstream& infile);

void print(pixel image[][1024], int width, int height, int color_depth,
           std::ofstream& infile);

void negate(pixel image[][1024], int width, int height, int color_depth);

void flop(pixel image[][1024], int width, int height);

void flip(pixel image[][1024], int width, int height);

int main(int argc, const char *argv[]) {
    int width = 0;  // Width of the Array 
    int height = 0;  // Height of the Array
    int color_depth = 0;  // Color Depth of the Array
    pixel image[1024][1024];  // Creates a image array with the pixel
    if (argc == 3 && strcmp(argv[1], argv[2]) != 0) {
        std::ifstream infile;  // input File
        std::ofstream outfile;  // Output File

        // attempt to open files
        infile.open(argv[1]);
        outfile.open(argv[2]);

        // Below Checks to make sure the file is compatible
        if (infile && outfile && infile.get() == 'P' && infile.get() == '3') {
            infile.ignore(256, '\n');
            
            // if the file has a comment ignore it
            if (infile.peek() == '#') {
                infile.ignore(256, '\n');
            }

            // Take in the width, height, and color depth
            infile >> width >> height >> color_depth;

            // If everything is in order begin the process
            if (width > 1024 || height > 1024 || color_depth > 255) {
                std::cout << "This is Incorrect Format";
            } else {
                std::cout << argv[1] << " Has " << width << " X " << height <<
                          " with " << color_depth << " intenstity levels." << '\n';


                read(image, width, height, infile);

                negate(image, width, height, color_depth);

                flop(image, width, height);

                flip(image, width, height);

                print(image, width, height, color_depth,  outfile);

            }
        }
    } else {
        std::cout << "Incorrect File or Wrong Format";
    }


    return 0;
}

/// ---------------------------------------------------------------
/// Function Name: read
///
/// Reads in the pixels into the Array
///
/// @param Image the Array for the image.
/// @param Width the width of the array.
/// @param height the height of the array.
/// @param infile the file that is giving input
///
/// @returns Void (no Return)
/// ---------------------------------------------------------------
void read(pixel image[][1024], int width, int height, std::ifstream& infile) {

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            infile >> image[row][col].red;
            infile >> image[row][col].green;
            infile >> image[row][col].blue;
        }
    }
}

/// ---------------------------------------------------------------
/// Function Name: negate
///
/// Negates (Reverses) The pixels within the array
///
/// @param Image the Array for the image.
/// @param Width the width of the array.
/// @param height the height of the array.
/// @param color_depth how much color to negate from the pixels
///
/// @returns Void (no Return)
/// ---------------------------------------------------------------

void negate(pixel image[][1024], int width, int height, int color_depth) {

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            image[row][col].red = color_depth - image[row][col].red;
            image[row][col].green = color_depth - image[row][col].green;
            image[row][col].blue = color_depth - image[row][col].blue;
        }
    }
}


/// ---------------------------------------------------------------
/// Function Name: flip
///
/// Flips the contents of the array affecting the image
///
/// @param Image the Array for the image.
/// @param Width the width of the array.
/// @param height the height of the array.
///
/// @returns Void (no Return)
/// ---------------------------------------------------------------

void flip(pixel image[][1024], int width, int height) {

    pixel temp;  // Temporary placement for the image array

    for (int row = 0; row < height / 2; row++) {
        for (int col = 0; col < width; col++) {
            temp = image[row][col];
            image[row][col] = image[height - row - 1][col];
            image[height - row - 1][col] = temp;
        }
    }
}

/// ---------------------------------------------------------------
/// Function Name: flop
///
/// Flops the contents of the array affecting the image
///
/// @param Image the Array for the image.
/// @param Width the width of the array.
/// @param height the height of the array.
///
/// @returns Void (no Return)
/// ---------------------------------------------------------------

void flop(pixel image[][1024], int width, int height) {
    pixel temp;  // Temporary placement for the image array

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width / 2; col++) {
            temp = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - col - 1] = temp;
        }
    }
}

/// ---------------------------------------------------------------
/// Function Name: print
///
/// Prints the contents of the array (pixels) onto another file
///
/// @param Image the Array for the image.
/// @param Width the width of the array.
/// @param height the height of the array.
/// @param outfile the file we are giving the array contents to
///
/// @returns Void (no Return)
/// ---------------------------------------------------------------

void print(pixel image[][1024], int width, int height, int color_depth,
           std::ofstream& outfile) {
    outfile << "P3" << '\n';
    outfile << width << " " << height << '\n';
    outfile << color_depth << '\n';

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            outfile << image[row][col].red << " ";
            outfile << image[row][col].green << " ";
            outfile << image[row][col].blue << " ";
        }
    }
}
