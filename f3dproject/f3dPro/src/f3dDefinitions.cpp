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

#include "include/f3d.h"

using namespace imageProcessing;

// Method Definitions of class f3d

// Constructor

f3d::f3d() : pixmap(){
    // Nothing to do
}

// Destructor

f3d::~f3d(){
    // Nothing to do
}

unsigned int f3d::makeint( unsigned char a[] ){
    unsigned int s = 0, t = 1;
    for(int i = 3; i >= 0; i--){
        s += a[i]*t;
        t = t*256;
    }
    return s;
}

int f3d::size( int dtype ){
    switch(dtype){
        case f3dUChar:
            return sizeof(unsigned char);
        case f3dChar:
            return sizeof(char);
        case f3dUInt16:
            return sizeof(unsigned short int);
        case f3dInt16:
            return sizeof(short int);
        case f3dUInt32:
            return sizeof(unsigned int);
        case f3dInt32:
            return sizeof(int);
        case f3dFloat:
            return sizeof(float);
        default:
            return 0;
    }
}

void f3d::GetF3dComment( char comment[], int k ){
    //TODO

    char array[ 200 ], *com, c = comment[ k ];
    int i = 0;
    PNMCOMMENTS *temp, *comm = f3dcomment;

    while( c != '\0' ){
        array[ i++ ] = c;
        c = comment[ ++k ];
    }

    array[ i ] = '\0';
    com = ( char* ) calloc( strlen( array ) + 1, sizeof( char ));
    strcpy( com, array );
    temp = ( PNMCOMMENTS* ) malloc( sizeof( PNMCOMMENTS ));
    temp->next = NULL;
    temp->Comment = com;

    if( comm == NULL ){
        f3dinfo.f3dcomment = temp;
        return ;
    }

    while( comm->next != NULL )
        comm = comm->next;
    comm->next = temp;
}

void f3d::ReadF3dInfo(){
    //TODO

    ///Reading The PNM Information Header

    readpnminfo( inputFile );
    PNMCOMMENTS *com = Comments;

    while( com != NULL ){
        int i = 1;
        char c = com->Comment[ i++ ];
        char array[ 20 ];

        /**Read The f3d Information Stored As PNM Comments**/

        if( c == '!' ){
            int j = 0;
            c = com->Comment[ i++ ];

            /**Forming The f3d tag**/

            while( isalnum(c) ){
                array[ j++ ] = c;
                c = com->Comment[ i++ ];
            }
            array[ j ] = '\0';
            while( !isalnum(c) )
                c = com->Comment[ i++ ];

            /**f3d Vertion**/
            if( !strcmp(array, "f3d") ){
                j = 0;
                while( isalnum(c) || c == '.' ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                f3dinfo.version = atof( array );
            }

            /**Defining The Byte Order Of The Computer The File Was Written On**/
            else if( !strcmp(array,"endian") ){
                c = com->Comment[ i+2 ];
                if( c == 'L' )
                    f3dinfo.endian = f3dLittleEndian;
                else
                    f3dinfo.endian = f3dBigEndian;
            }

            /**Defining Volume Dimensions**/
            else if( !strcmp(array,"vdim") ){
                for( int index = 1; index <= 3; index++ ){
                    j = 0;
                    while( isdigit(c) ){
                        array[ j++ ] = c;
                        c = com->Comment[ i++ ];
                    }
                    array[ j ] = '\0';
                    if( index == 1 )
                        f3dinfo.vdim.nx = atoi( array );
                    else if( index == 2 )
                        f3dinfo.vdim.ny = atoi( array );
                    else
                        f3dinfo.vdim.nz = atoi( array );
                    while( !isalnum(c) )
                        c = com->Comment[ i++ ];
                }
            }

            /**Defining The Grid Type**/
            else if( !strcmp(array,"vtype") ){
                j = 0;
                while( isalnum(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                if( !strcmp(array, "f3dCubic") )
                    f3dinfo.vtype = f3dCubic;
                else if( !strcmp(array, "f3dRegular") )
                    f3dinfo.vtype = f3dRegular;
                else if( !strcmp(array, "f3dRectZ") )
                    f3dinfo.vtype = f3dRectZ;
                else if( !strcmp(array, "f3dRectXYZ") )
                    f3dinfo.vtype = f3dRectXYZ;
            }

            /**Defining Scaler and Vector (Color) Data**/
            else if( !strcmp(array,"ctype") ){
                j = 0;
                while( isalnum(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                if( !strcmp(array, "f3dMono") )
                    f3dinfo.ctype = f3dMono;
                else if( !strcmp(array, "f3dComplex") )
                    f3dinfo.ctype = f3dComplex;
                else if( !strcmp(array, "f3dColor") )
                    f3dinfo.ctype = f3dColor;
            }

            /**Defining The Numerical Type Of A Voxel**/

            else if( !strcmp(array,"dtype") ){
                j = 0;
                while( isalnum(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                if( !strcmp(array, "f3dUChar") )
                    f3dinfo.dtype = f3dUChar;
                else if( !strcmp(array, "f3dChar") )
                    f3dinfo.dtype = f3dChar;
                else if( !strcmp(array, "f3dUInt16") )
                    f3dinfo.dtype = f3dUInt16;
                else if( !strcmp(array, "f3dInt16") )
                    f3dinfo.dtype = f3dInt16;
                else if( !strcmp(array, "f3dUInt32") )
                    f3dinfo.dtype = f3dUInt32;
                else if( !strcmp(array, "f3dInt32") )
                    f3dinfo.dtype = f3dInt32;
                else if( !strcmp(array, "f3dFloat") )
                    f3dinfo.dtype = f3dFloat;
            }

            /**Physical Units Of The Grid Dimensions**/
            else if( !strcmp(array,"units") ){
                j = 0;
                while( isalnum(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                if( !strcmp(array, "f3dUum") )
                    f3dinfo.units = f3dUum;
                else if( !strcmp(array, "f3dUmm") )
                    f3dinfo.units = f3dUmm;
                else if( !strcmp(array, "f3dUm") )
                    f3dinfo.units = f3dUm;
            }

            /**Absolute/Default Maximun and Minimun Values**/
            else if( !strcmp(array,"absMax") ){
                j = 0;
                while( isdigit(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                f3dinfo.absMax = atoi(array);
            }
            else if( !strcmp(array,"absMin") ){
                j = 0;
                while( isdigit(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                f3dinfo.absMin = atoi(array);
            }
            else if( !strcmp(array,"defaultMax") ){
                j = 0;
                while( isdigit(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                f3dinfo.defaultMax = atoi(array);
            }
            else if( !strcmp(array,"defaultMin") ){
                j = 0;
                while( isdigit(c) ){
                    array[ j++ ] = c;
                    c = com->Comment[ i++ ];
                }
                array[ j ] = '\0';
                f3dinfo.defaultMin = atoi(array);
            }

            /**Comments**/
            else if( !strcmp(array,"comment") ){
                getf3dcomment( com->Comment, i - 1 );
            }

            /**Finding Voxel Size In Different Directions**/
            else{
                if( vtype == f3dCubic || vtype == f3dRectZ || vtype == f3dRegular ){
                    if( !strcmp( array, "px" ) ){
                        j = 0;
                        while( isdigit(c)||c == '.' ){
                            array[ j++ ] = c;
                            c = com->Comment[ i++ ];
                        }
                        array[ j ] = '\0';
                        f3dinfo.px = atof( array );
                    }
                    if( vtype == f3dRectZ || vtype == f3dRegular ){
                            if( !strcmp( array, "py" ) ){
                            j = 0;
                            while( isdigit(c) || c == '.' ){
                                array[ j++ ] = c;
                                c = com->Comment[ i++ ];
                            }
                            array[ j ] = '\0';
                            f3dinfo.py = atof( array );
                        }
                        if( vtype == f3dRegular ){
                            if( !strcmp( array, "pz" ) ){
                                j = 0;
                                while( isdigit(c) || c == '.' ){
                                    array[ j++ ] = c;
                                    c = com->Comment[ i++ ];
                                }
                                array[ j ] = '\0';
                                f3dinfo.pz = atof( array );
                            }
                        }
                        else if( !strcmp( array, "rz" ) ){
                            j = 0;
                            while( isdigit(c) || c == '.' ){
                                array[ j++ ] = c;
                                c = com->Comment[ i++ ];
                            }
                            array[ j ] = '\0';
                            rz = atof( array );
                        }
                    }
                }
                else{
                    if( !strcmp( array, "rx" ) ){
                        j = 0;
                        while( isdigit(c) || c == '.' ){
                            array[ j++ ] = c;
                            c = com->Comment[ i++ ];
                        }
                        array[ j ] = '\0';
                        f3dinfo.rx = atof( array );
                    }
                    else if( !strcmp( array, "ry" ) ){
                        j = 0;
                        while( isdigit(c) || c == '.' ){
                            array[ j++ ] = c;
                            c = com->Comment[ i++ ];
                        }
                        array[ j ] = '\0';
                        f3dinfo.ry = atof( array );
                    }
                    else if( !strcmp( array, "rz" ) ){
                        j = 0;
                        while( isdigit(c) || c == '.' ){
                            array[ j++ ] = c;
                            c = com->Comment[ i++ ];
                        }
                        array[ j ] = '\0';
                        f3dinfo.rz = atof( array );
                    }
                }
            }
        }
        com = com->next;
    }
    f3dinfo.VoxelDataOffset = f3dinfo.vdim.nx * f3dinfo.vdim.ny + ImageDataOffset;
}

void f3d::ShowF3dInfo( void ){
    //TODO
    printf( "\n\tF3DINFOHEADER\n\n" );
    printf( "\t\tVoxelDataOffset\t:\t%d\n", VoxelDataOffset );
    printf( "\t\tversion\t\t:\t%0.2f\n", version );
    printf( "\t\tendian\t\t:\t%s\n", Message1[ endian ] );
    printf( "\t\tvdim\tnx\t:\t%d\n", vdim.nx );
    printf( "\t\t\tny\t:\t%d\n", vdim.ny );
    printf( "\t\t\tnz\t:\t%d\n", vdim.nz );
    printf( "\t\tvtype\t\t:\t%s\n", Message2[ vtype ] );
    printf( "\t\tctype\t\t:\t%s\n", Message3[ ctype ] );
    printf( "\t\tdtype\t\t:\t%s\n", Message4[ dtype ] );
    printf( "\t\tunits\t\t:\t%s\n", Message5[ units ] );
    printf( "\t\tabsMax\t\t:\t%d\n", absMax );
    printf( "\t\tabsMin\t\t:\t%d\n", absMin );
    printf( "\t\tdefaultMax\t:\t%d\n", defaultMax );
    printf( "\t\tdefaultMin\t:\t%d\n", defaultMin );
    printf( "\t\tpx\t\t:\t%f\n", px );
    printf( "\t\tpy\t\t:\t%f\n", py );
    printf( "\t\tpz\t\t:\t%f\n", pz );
    printf( "\t\trx\t\t:\t%f\n", rx );
    printf( "\t\try\t\t:\t%f\n", ry );
    printf( "\t\trz\t\t:\t%f\n", rz );

    PNMCOMMENTS *comm = f3dinfo.f3dcomment;

    printf( "\nComments :\n\n" );

    while( comm != NULL ){
        printf( "%s\n", comm->Comment );
            comm = comm->next;
    }
}

void f3d::GetF3dVoxel(){
    //TODO

//    int offset = ImageDataOffset, i, j;

//    fseek( inputFile, offset, 0 );

//    /**Finding The File Size**/
//    while ((fread (&rec, 1, 1, source)) > 0) {
//        offset++;
//    }

    //cout << "FileSize : " << offset << "Bytes\n";
//
//    /**Copy Header Part**/
//    fseek(source, 0, 0);
//    for(i = 0; i < ImageDataOffset; i++){
//        fread(&rec, 1, 1, source);
//        //fwrite(&rec, 1, 1, dest);
//    }

    ///Copy Icon Image Data Part

    getpnmpixel();
    SavePnmAsFile();
//    int k = 0;
//    for(i = 0; i < vdim.nx; i++){
//        for(j = 0; j < vdim.ny; j++){
//            fread(&rec, 1, 1, source);
//            //fseek(dest, offset-k, 0); //for reversing the 2-D preview
//            //fwrite(&rec, 1, 1, dest);
//            k++;
//        }
//    }

    ///Copy Voxel Part

//    offset = f3dinfo.VoxelDataOffset;
//    fseek(dest, offset, 0);

    int zLimit = f3dinfo.vdim.nz;
    int yLimit = f3dinfo.vdim.ny;
    int xLimit = f3dinfo.vdim.nx;
    unsigned char a[4];
    unsigned long sourceLen;
    unsigned char *buf;
    unsigned long destLen = f3dinfo.vdim.nx * f3dinfo.vdim.ny * size( dtype );
    unsigned char *obuf = new unsigned char[ destLen ];

    /// For each slice, do the within-loop part

    for( register int k = 0; k < zLimit; k++ ){

        ///Read The 32 bit Integer Part

        fread( a, 1, 4, inputFile );
        //fwrite(a, 1, 4, dest);
        sourceLen = makeint(a);

        ///Read The Following Compressed Slice Part

        buf = new unsigned char[ sourceLen ];
        fread( buf, 1, sourceLen, inputFile );
        //fwrite(buf, 1, val, dest);

        ///Uncompress The Compressed Slice Part Using zlib

        int ret = uncompress( obuf, &destLen, buf, sourceLen );

        ///Error handling

        switch( ret ){
            case Z_OK:
                //fwrite(obuf, 1, destLen, dest);
                break;
            case Z_MEM_ERROR:
                perror("Not enough memory\n");
                exit( EXIT_FAILURE );
            case Z_BUF_ERROR:
                perror("Not enough memory in output buffer\n");
                exit( EXIT_FAILURE );
            case Z_DATA_ERROR:
                perror("Input data corrupted\n");
                exit( EXIT_FAILURE );
        }

        ///Read The Uncompressed Voxels According To Data Type

        ///*(buf + z*(hdr.ny*hdr.nx) + y*hdr.nx + x) => formula for accessing a voxel(x,y,z)

        for( register int j = 0; j < yLimit; j++ ){
            for( register int i = 0; i < xLimit; i++ ){
                {
//                //printf("Voxel (%3d,%3d,%3d)\t", i, j, slicecount);
//                loadValue( obuf, i, j, slicecount );
//                switch(dtype){
//                    case f3dUChar:
//                        fwrite(((unsigned char*)obuf + j * vdim.nx + i), 1, size(f3dUChar), dest);
//                        //printf("%u\n", *((unsigned char*)obuf + i * f3dinfo.vdim.nx + j));
//                        break;
//                    case f3dChar:
//                        fwrite(((char*)obuf + i * vdim.nx + j), 1, size(f3dChar), dest);
//                        //printf("%d\n", *((char*)obuf + i * f3dinfo.vdim.nx + j));
//                        break;
//                    case f3dUInt16:
//                        fwrite(((unsigned short int*)obuf + i * vdim.nx + j), 1, size(f3dUInt16), dest);
//                        //printf("%u\n", *((unsigned short int*)obuf + i * f3dinfo.vdim.nx + j));
//                        break;
//                    case f3dInt16:
//                        fwrite(((short int*)obuf + i * vdim.nx + j), 1, size(f3dInt16), dest);
//                        //printf("%d\n", *((short int*)obuf + i * f3dinfo.vdim.nx + j));
//                        break;
//                    case f3dUInt32:
//                        fwrite(((unsigned int*)obuf + i * vdim.nx + j), 1, size(f3dUInt32), dest);
//                        //printf("%u\n", *((unsigned int*)obuf + i * f3dinfo.vdim.nx + j));
//                        break;
//                    case f3dInt32:
//                        fwrite(((int*)obuf + i * vdim.nx + j), 1, size(f3dInt32), dest);
//                        //printf("%d\n", *((int*)obuf + i * f3dinfo.vdim.nx + j));
//                        break;
//                    case f3dFloat:
//                        fwrite(((float*)obuf + i * vdim.nx + j), 1, size(f3dFloat), dest);
//                        //printf("%f\n", *((float*)obuf + i * f3dinfo.vdim.nx + j));
//                        break;
//                }
                }
                //
                ( image* )f3dData->loadValue( voxValue, i, j, k );
            }
        }
        delete buf;
    }
    delete obuf;
}

//int f3d::Size( int ){
//    //TODO
//}

void f3d::LoadF3dVoxel( char* source ){
    //TODO
    fileLoc = source;
    inputFile = fopen( fileLoc, "rb" );

    // Error handling
    if ( inputFile == NULL ){
        cout << "cannot open the file " << fileLoc << endl;
        exit( EXIT_FAILURE );
    }

    ReadF3dInfo();
    ShowF3dInfo();

    // Define appropriate data type for image part
    switch( f3dinfo.dtype ){
        case f3dUChar:
            f3dUCharData = ( f3dUChar*  ) new image<f3dUChar>();
            f3dUCharData->allocImage( vdim.nx, vdim.ny, vdim.nz );
            break;
        case f3dChar:
            f3dCharData = ( f3dChar*   ) new image<f3dChar>();
            f3dUCharData->allocImage( vdim.nx, vdim.ny, vdim.nz );
            break;
        case f3dUInt16:
            f3dUInt16Data = ( f3dUInt16* ) new image<f3dUInt16>();
            f3dUCharData->allocImage( vdim.nx, vdim.ny, vdim.nz );
            break;
        case f3dInt16:
            f3dInt16Data = ( f3dInt16*  ) new image<f3dInt16>();
            f3dUCharData->allocImage( vdim.nx, vdim.ny, vdim.nz );
            break;
        case f3dUInt32:
            f3dUInt32Data = ( f3dUInt32* ) new image<f3dUInt32>();
            f3dUCharData->allocImage( vdim.nx, vdim.ny, vdim.nz );
            break;
        case f3dInt32:
            f3dInt32Data = ( f3dInt32*  ) new image<f3dInt32>();
            f3dUCharData->allocImage( vdim.nx, vdim.ny, vdim.nz );
            break;
        case f3dFloat:
            f3dFloatData = ( f3dFloat*  ) new image<f3dFloat>():
            f3dUCharData->allocImage( vdim.nx, vdim.ny, vdim.nz );
            break;
    }

    // For holding the icon image data part
    //TODO
    GetF3dVoxel();
}

void f3d::SaveF3dAsFile(){
    //TODO
}
