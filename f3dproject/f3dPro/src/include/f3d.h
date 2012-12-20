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

#ifndef F3D_H_INCLUDED
#define F3D_H_INCLUDED

// Include Directives

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <typeinfo>
#include "mathtool.h"
#include "pixmap.h"
#include "zlib.h"

using namespace std;

namespace imageProcessing{

    //Enumerators Used

    /**
    Description:
        //TODO
    **/

    enum endian {
        f3dLittleEndian,
        f3dBigEndian
    };
    enum vtype  {
        f3dCubic,
        f3dRegular,
        f3dRectZ,
        f3dRectXYZ
    };
    enum ctype  {
        f3dMono,
        f3dComplex,
        f3dColor
    };
    enum dtype  {
        f3dUChar,
        f3dChar,
        f3dUInt16,
        f3dInt16,
        f3dUInt32,
        f3dInt32,
        f3dFloat
    };
    enum units  {
        f3dUum,
        f3dUmm,
        f3dUm
    };

    //Typedefs
    typedef unsigned char f3dUChar;
    typedef char f3dChar;
    typedef unsigned short f3dUInt16;
    typedef short f3dInt16;
    typedef unsigned long f3dUInt32;
    typedef long f3dInt32;
    typedef char f3dFloat;


    //Arrays For Header Display

    /**
    Description:
        //TODO
    **/

    char Message1[][20] = {
        "f3dLittleEndian",
        "f3dBigEndian"
    };
    char Message2[][20] = {
        "f3dCubic",
        "f3dRegular",
        "f3dRectZ",
        "f3dRectXYZ"
    };
    char Message3[][20] = {
        "f3dMono",
        "f3dComplex",
        "f3dColor"
    };
    char Message4[][20] = {
        "f3dUChar",
        "f3dChar",
        "f3dUInt16",
        "f3dInt16",
        "f3dUInt32",
        "f3dInt32",
        "f3dFloat"
    };
    char Message5[][20] = {
        "f3dUum",
        "f3dUmm",
        "f3dUm"
    };

    //Structure For Holding Header

    /**
    Description:
        //TODO
    **/

    typedef struct dim{
        int         nx, ny, nz;
    }dim;

    typedef struct tagF3DHEADER{
        float       version;
        int         endian;
        dim         vdim;
        int         vtype;
        int         ctype;
        int         dtype;
        int         units;
        float       px, py, pz, rx, ry, rz;
        int         absMax, absMin, defaultMax, defaultMin;
        int         VoxelDataOffset;
        PNMCOMMENTS *f3dcomment;
    }F3DHEADER;

    // Class f3d

    /**
    Description:
        //TODO
    **/

    class f3d::public pixmap{
        //TODO
        private:
            F3DHEADER       f3dinfo;            // Holds the header part

        public:
            f3d();
            ~f3d();
            void            GetF3dComment( char comment[], int k );
            void            ReadF3dInfo( FILE* );
            void            ShowF3dInfo( void );
            void            GetF3dVoxel( FILE*, FILE* );
            void            LoadF3dVoxel( char* );
            void            SaveF3dAsFile();
            unsigned int    makeint( unsigned char a[] );
            int             size( int );
    }
}

#endif // F3D_H_INCLUDED
