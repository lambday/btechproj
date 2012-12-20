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

#ifndef IMAGEDEFINITIONS_H_INCLUDED
#define IMAGEDEFINITIONS_H_INCLUDED

// Include Directives

#include <cstdio>

using namespace imageProcessing;

/**
Description:
    The following are method definitions for the class
    image. As the class is a template class, so its
    better we define the methods within a separate
    header file than individual source file, else its
    hard to compile.
**/

// Constructor

/**
Description:
    The constructor takes no parameters, and initializes
    the size of the image be 0 x 0 x 0, default.
**/

template <typename dataType>
image <dataType>::image(){

    size_x = size_y = size_z = 0;

}

// allocImage Method

/**
Description:
    Allocates memory to matrix as per size specified, in
    X x Y x Z fashion. Specifying only two parameters
	defaults to create a 2D image.
**/

template <typename dataType>
void image <dataType>::allocImage(
                        int imageSize_x = 0,
                        int imageSize_y = 0,
                        int imageSize_z = 1
                        ){

	// Initializing the sizes

	size_x = imageSize_x;
	size_y = imageSize_y;
	size_z = imageSize_z;

	// Just a bit error handling in case the method
	// is called with no arguments at all.

	if ( size_x == 0 || size_y == 0){
		cout << "No memory allocated." << endl;
		size_x = size_y = size_z = 0;
	}
	else{

		// Here goes the real Memory Allocation Part

		/**
        Description:
            In this, we take a triple pointer, matrix.
            By allocating like this, the 'k' or size_z will
            specify the #slice, the 'j' or size_y will specify
            the #row, and the 'i' or size_x will specify the
            #element selected. Note this different than normal
            loop variables where 'i' is generally used for
            refering the row and 'j' for column.
        **/

		try{
	            matrix = new dataType**[size_z];
	            for(register int j = 0; j < size_z; ++j){
	                matrix[j] = new dataType*[size_y];
	                for(register int i = 0; i < size_y; ++i){
	                    matrix[j][i] = new dataType[size_x];
	                }
	            }

	            // Successfully allocated memory.

	            cout << "Memory allocated for " << size_x << " X " << size_y << " X "       \
	            << size_z << " sized image." << endl;

		}catch( exception e ){

			// Got exception while allocating memory.

			cout << "Memory allocation failed" << endl;
		}
	}
}

// Destructor

/**
Description:
    The destructor discards the memory allocated for
    the image.
**/

template <typename dataType>
image <dataType>::~image(){

	delete matrix;
	cout << "Memory Discarded successfully" << endl;

}

// Image type : 3D or 2D?

/**
Description:
    The following method returns true if its 3d else false (even if its not allocated)
**/

template <typename dataType>
bool image <dataType>::is3d(){

	bool allocated = isAllocated();

	if ( allocated )
		return ( size_z != 1 );
	else
		return allocated;

}

// Is the memory allocated?

/**
Description:
    The following method returns true if memory is allocated else false.
**/

template <typename dataType>
bool image <dataType>::isAllocated(){

	return (( size_x || size_y || size_z ));

}

// Size query methods

/**
Description:
    The following methods returns dimensions of the image
**/

template <typename dataType>
int image <dataType>::getDimension_x(){

	return size_x;

}

template <typename dataType>
int image <dataType>::getDimension_y(){

	return size_y;

}

template <typename dataType>
int image <dataType>::getDimension_z(){

	return size_z;

}

// getValue Method

/**
Description:
    Returns the voxel value located at position (i, j, k).
    Default value of k is taken as 1 for generality for 2d images.
**/

template <typename dataType>
dataType image <dataType>::getValue(
                            int i,
                            int j,
                            int k = 0
                            ){

	return matrix[k][j][i];

}

// getValue Method

/**
Description:
    Stores the value to the matrix at position (i, j, k).
**/

template <typename dataType>
void image <dataType>::loadValue(
                        dataType val,
                        int i,
                        int j,
                        int k = 0
                        ){

    //cout << (int)val << " loaded at (" << k << "," << j << "," << i << ")" << endl;
	matrix[k][j][i] = val;
	// The value of the 'k'th slice of total 'size_z' slices and 'j'th row
	// of total 'size_y' rows (i.e. image height is size_y) and 'i'th element
	// of total 'size_x' elements per row (i.e. image width is size_x) is 'val'

}

#endif // IMAGEDEFINITIONS_H_INCLUDED
