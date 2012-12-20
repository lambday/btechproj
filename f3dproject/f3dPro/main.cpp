/**
 *  DOCUMENTATION:
 *      This file is part of the f3d project under
 *      Kalyani Govt. Engineering College. f3d is a
 *      new file format, stands for format 3 dimension
 *      to store and display 3D volumetric data. In
 *      this project we try to develope a viewer for
 *      the f3d images, called f3dview. Currently
 *      this works only under microsoft windows. But
 *      soon a Linux version will be prepared. The
 *      approach uses OpenGL graphics library towards
 *      achieving the primary goal.
 *
 *      @authr Soumyajit De, 3rd year, B.Tech CSE.
 *      under the guidance of Mr. Kousik Dasgupta,
 *      Lecturer, Kalyani Govt. Engineering College.
**/

// Include Directives

#include <iostream>
#include "src/include/imageProcessing.h"

using namespace std;
using namespace imageProcessing;

// The Main function

/**
Description:
    The Main function creates an instance of a
    template object called 'image' and then
    allocates a 256 x 256 memory in it and stores
    it to the image using one of the provided
    method, called 'loadValue'. And then we call
    another method from image called 'draw' to
    draw this image, creating a GLUT window.
**/


int main( int argc, char **argv )
{
    //image<unsigned char> myImg(argc, argv);
    pixmap *myImg = new pixmap();
//    char input[50];
//    cout << "Enter file location and name" << endl;
//    cin >> input;

    myImg->loadPnmPixel( argv[0] );

    cout << "Loaded successfully" << endl;

    myImg->SavePnmAsFile();
    delete myImg;

    cout << "Successful" << endl;

    return 0;
}
