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

#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

// Include Directives

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "image.h"

using namespace std;

// Class 'pixmap' is part of the namespace imageProcessing

namespace imageProcessing{

// Class pixmap

/**
Description:
    The 'pixmap' class inherits the 'image' class
    as usigned char format publicly. It holds the
    header for the pixmap image in protected format.
        Various methods include some utility
    protected method for internal use, and some public
    methods for usage of this class, and let the
    user to query some image and header specific
    information.
**/

    class pixmap:public image<unsigned char>{

        // Data Members - Header Specific Information

    protected:
        char    FormatSignature[3];
        int     ImageWidth;
        int     ImageHeight;
        int     MaxValue;
        int     ImageDataOffset;
        long    FileSize;
        long    ImageSize;
        int     BitDepth;
        bool    loaded;    // loaded = true if image is loaded, else false

        // Structure Declaration

        typedef struct tagPNMCOMMENTS{
            char    *Comment;
            struct  tagPNMCOMMENTS *next;
        }PNMCOMMENTS;
        PNMCOMMENTS *Comments;

        // File specific information

        char    *fileLoc;
		FILE    *inputFile;

        // Some internal methods

        void    changeLoaded();
        void    loadFormatSignature( char* );
        bool    isFormat( char );
        void    loadImageWidth( int );
        void    loadImageHeight( int );
        void    loadMaxValue( int );
        void    loadImageDataOffset( int );
        void    loadFileSize( long );
        void    loadImageSize( long );
        void    loadBitDepth( int );


    	// Publicly Usable Method members

	public:
        // Constructor

        pixmap();

        // Destructor

        ~pixmap();

        // Some utility methods

        bool    isLoaded();
        char*   getFormatSignature();
        int     getImageWidth();
        int     getImageHeight();
        int     getMaxValue();
        int     getImageDataOffset();
        long    getFileSize();
        long    getImageSize();
        int     getBitDepth();

        // Usage methods

	/**
        	Description:
	            Reads the header and stores information into header.
        **/

        void    readpnminfo();

	/**
        	Description:
	            Displays the information header.
        **/

        void    showpnminfo();

	/**
		Description:
        	    Gets the comment and stores in a linked list, returns
	            the changed offset value.
        **/

        int     getcomment( int, char );

	/**
		Description:
        	    Stores the pixmap image in an image.
        **/

        void    getpnmpixel();

	/**
		Description:
	            Reads the file specified by the char pointer
	            specified as argument, and the loads the image
	            by calling getpnmpixel. This is the method user
	            should call for loading a complete pixmap image
	            and then start working.
        **/

        void    loadPnmPixel( char* );

	/**
		Description:
	            Takes the output filename as argument and writes
        	    the raw image data in binary format to that out-
	            -put file, and closes handles to that file.
        **/

        void    SavePnmAsFile();
    };
}

#endif // PIXMAP_H_INCLUDED
