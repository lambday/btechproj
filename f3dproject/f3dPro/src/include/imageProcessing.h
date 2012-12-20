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

#ifndef IMAGE_PROCESSING_H_INCLUDED
#define IMAGE_PROCESSING_H_INCLUDED

// Include Directives
#include "image.h"
#include "pixmap.h"
#include "f3d.h"

// Namespace imageProcessing

/**
Description:
    The namespace imageProcessing is the common
    wrapper for the all classes and methods for
    the entire project. Currently is has members
    as:
    # image class:
        The image class is a template class, which
    holds the image data, as 'dataType' type 3D
    pointer 'matrix', the size of the image in
    integers, argument counter & argument vector
    for creating glut windowing facility to draw
    the image. (Detailed info in the 'image.h' file.)
**/


namespace imageProcessing{
	template <typename dataType> class image;
	class pixmap;
	class f3d;
}

#endif // IMAGE_PROCESSING_H_INCLUDED
