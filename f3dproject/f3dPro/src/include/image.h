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

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

// Include Directives

#include <iostream>

using namespace std;

// Class 'image' is part of the namespace imageProcessing

namespace imageProcessing{

// Class image

/**
Description:
    The image class is a template class, which holds the
    image data, as 'dataType' type 3D pointer 'matrix',
    the size of the image in integers.
        Various methods include one constructor, and
    methods for allocating memory (allocImage), one
    destructor, and several query specific methods for
    basic information about the image stored. We provide
    no direct method to load any image from a file, rather
    a method called 'loadValue' is provided here to store
    values to the image matrix directly at desired position.
**/

	template <typename dataType>
	class image{

	protected:
		// Holds the actual matrix
		dataType    ***matrix;

		// Holds the size of the image
		int     size_x,
			size_y,
                	size_z;

	public:
		// Initializes the sizes to zero (Default).
		image();

		// Allocates memory to matrix as per size specified, in
		// X x Y x Z fashion. Specifying only two parameters
		// defaults to create a 2D image.
		void    allocImage( int, int, int );

		// Deallocates the memory
		~image();

		// Returns true if the image is 3d else false
		bool    is3d();
		// Returns true if the memory is allocated else false
		bool    isAllocated();

		// Returns the dimension details of the image
		int     getDimension_x();
		int     getDimension_y();
		int     getDimension_z();

		// TODO
		// we need to write a method that will use run-time-type-information
		// and will provide a way to know the datatype of the image at rumtime

		// Returns the image size in bytes
		int     getDataSize();

		// Returns the value of the voxel at position (i, j, k) // parameters
		dataType getValue(int, int, int);

		// Loads the value of the voxel at position (i, j, k) // parameters
		void    loadValue(dataType, int, int, int);

	};

}

#include "imageDefinition.h"

#endif // IMAGE_H_INCLUDED
