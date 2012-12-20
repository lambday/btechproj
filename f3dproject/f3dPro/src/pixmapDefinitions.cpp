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

/// DOCUMENTATION NOT COMPLETE

// Include Directives

#include "include/pixmap.h"

using namespace imageProcessing;

// Method Definitions of class pixmap

// Constructor

pixmap::pixmap():image<unsigned char>(){

    loaded = false;
}

pixmap::~pixmap(){

    fclose( inputFile );
    cout << "file closed" << endl;

}


/// Some utility methods
// The following method changes the loaded status

void pixmap::changeLoaded(){

	loaded = !loaded;

}

// The following method returns the loaded status

bool pixmap::isLoaded(){

	return loaded;

}

void pixmap::loadFormatSignature( char* s ){

	strcpy( FormatSignature, s );

}

char* pixmap::getFormatSignature(){

	return FormatSignature;

}

bool pixmap::isFormat( char f ){

	return ( FormatSignature[1] == f );

}

void pixmap::loadImageWidth( int w ){

	ImageWidth = w;

}

int pixmap::getImageWidth(){

	return ImageWidth;

}

void pixmap::loadImageHeight( int h ){

	ImageHeight = h;

}

int pixmap::getImageHeight(){

	return ImageHeight;

}

void pixmap::loadMaxValue( int m ){

	MaxValue = m;

}

int pixmap::getMaxValue(){

	return MaxValue;

}

void pixmap::loadImageDataOffset( int d ){

	ImageDataOffset = d;

}

int pixmap::getImageDataOffset(){

	return ImageDataOffset;

}

void pixmap::loadFileSize( long s ){

	FileSize = s;

}

long pixmap::getFileSize(){

	return FileSize;

}

void pixmap::loadImageSize( long i ){

	ImageSize = i;

}

long pixmap::getImageSize(){

	return ImageSize;

}

void pixmap::loadBitDepth( int d ){

	BitDepth = d;

}

int pixmap::getBitDepth(){

	return BitDepth;

}

// Usage methods

/** getcomment method:
    ------------------
    Description:
        Gets the comment and stores in a linked list, returns
        the changed offset value.
**/

int pixmap::getcomment( int offset, char rec ){

    char array[ 200 ], *com;
    int i = 0;
    PNMCOMMENTS *temp, *comm = Comments;

    while( rec != '\n' ){
        array[ i++ ] = rec;
        fread( &rec, 1, 1, inputFile );
        offset++;
    }

    array[ i ] = '\0';

    com = ( char* ) calloc( strlen( array ) + 1, sizeof( char ));
    strcpy( com, array );

    temp = ( PNMCOMMENTS* ) malloc( sizeof( PNMCOMMENTS ));
    temp->next = NULL;
    temp->Comment = com;

    if(comm == NULL){
        Comments = temp;
        return offset;
    }

    while(comm->next != NULL)
        comm = comm->next;
    comm->next = temp;

    return offset;

}

/** readpnminfo method:
    -------------------
    Description:
        Reads the header and stores information into header.
**/

void pixmap::readpnminfo(){

    // if already loaded, cannot read any more data
	if( isLoaded())
		return;

    char rec, array[ 10 ];
    enum state{ isheader, ispixel };
    state status = isheader;

    int c = 1, i = 0, offset = 0;

    Comments = NULL;

	char signature[ 3 ];

    fseek( inputFile, 0, 0 );

    while( status == isheader ){

        switch( c ){
            case 1:
                i = 0;
                fread( &rec, 1, 1, inputFile );
                offset++;
                if( rec == '#' ){
                    offset = getcomment( offset, rec );
                    break;
                }
                while( rec != '\n' ){
                    signature[ i++ ] = rec;
                    fread( &rec, 1, 1, inputFile );
                    offset++;
                }
                c = 2;
                signature[ i ] = '\0';
                loadFormatSignature( signature );
                break;
            case 2:
                i = 0;
                fread( &rec, 1, 1, inputFile );
                offset++;
                if(rec == '#'){
                    offset = getcomment( offset, rec);
                    break;
                }
                while( rec != ' ' ){
                    array[ i++ ] = rec;
                    fread( &rec, 1, 1, inputFile );
                    offset++;
                }
                array[ i ] = '\0';
                loadImageWidth( atoi( array ));
                c = 3;
                break;
            case 3:
                i = 0;
                fread( &rec, 1, 1, inputFile );
                offset++;
                if( rec == '#' ){
                    offset = getcomment( offset, rec);
                    break;
                }
                while ( rec != '\n' ){
                    array[ i++ ] = rec;
                    fread( &rec, 1, 1, inputFile );
                    offset++;
                }
                array[ i ] = '\0';
                loadImageHeight( atoi( array ));
                c = 4;
                break;
            case 4:
                if( isFormat( '1' ) || isFormat( '4' )){
                    loadMaxValue( 1 );
                    status = ispixel;
                    break;
                }
                i = 0;
                fread( &rec, 1, 1, inputFile );
                offset++;
                if( rec == '#' ){
                    offset = getcomment( offset, rec);
                    break;
                }
                while( rec != '\n' ){
                    array[ i++ ] = rec;
                    fread( &rec, 1, 1, inputFile );
                    offset++;
                }
                array[ i ] = '\0';
                loadMaxValue( atoi( array ));
                status = ispixel;
                break;
        }
    }

    loadImageDataOffset( offset );
    long int size = getImageWidth() * getImageHeight();

    if( isFormat( '4' ))
        loadImageSize( size/8 );
    else if( isFormat( '5' ))
        loadImageSize( size );
    else if( isFormat( '6' ))
        loadImageSize( size * 3 );

    loadFileSize( getImageSize() + getImageDataOffset());

    if( isFormat( '3' ) || isFormat( '6' ))
        loadBitDepth( 24 );
    else if( isFormat( '2' ) || isFormat( '5' ))
        loadBitDepth( 8 );
    else
        loadBitDepth( 1 );

    changeLoaded();

}

/** getpnmpixel method:
    -------------------
    Description:
        Stores the pixmap image in an image.
**/

void pixmap::getpnmpixel(){

    unsigned char rec;
    //readpnminfo();

    cout << "offset " << getImageDataOffset() << endl;

    fseek( inputFile, getImageDataOffset(), 0);

	int h = getImageHeight();
	int w = getImageWidth();

	int bit = getBitDepth() / 8;
	cout << "bit depth " << bit << endl;

	allocImage( w, h, bit );

//    /// TEST PURPOSE
//	for( int j = 0; j < h; j++ ){
//        for( int i = 0; i < w; i++ ){
//            for( int k = 0; k < bit; k++ ){
//                loadValue( 'A', i, j, k );
//            }
//        }
//	}
//
//	///UPTO HERE

    for( int j = 0; j < h; j++ ){
        for( int i = 0; i < w; i++ ){
            //printf("\nPixel(%d,%d)", i+1, j+1);

            for( int k = 0; k < bit; k++ ){

                // Read until it gets the first value
//                do{
//                    fread( &rec, 1, 1, inputFile );
//                }while( !isalnum( rec ) );

                fread( &rec, 1, 1, inputFile );

//                if( !isFormat( '3' )){
//
//                    // The pixel value is formed by more than one character
//
//                    char array[ 10 ];
//                    int c = 0;
//                    do{
//                        array[ c ] = rec;
//                        ++c;
//                        fread( &rec, 1, 1, inputFile );
//                    }while( isdigit( rec ) );
//                    array[ c ] = '\0';
//                    //cout << "Print Array " << array << endl;
//                    rec = ( unsigned char ) atoi( array );
//                    //printf("\t%3d", rec);
//                    //loadValue( rec, i, j, k);
//                }
                //printf("\t%3d", rec);
                loadValue( rec, i, j, k );
            }
        }
        //printf("\n");
    }
    printf( "Pixels written to the matrix\n" );

    printf( "Do you want to see the pixels? [y]/[n]\t" );
    char choice;
    cin >> choice;

    if( choice == 'y' || choice == 'Y' ){
		for( int j = 0; j < h; ++j ){
			for( int i = 0; i < w; ++i ){
				printf( "%3d ", ( int ) getValue( i, j, 0 ));
				if( bit > 1 ){
					cout << getValue( i, j, 1 ) << " ";
					cout << getValue( i, j, 2 ) << " ";
				}
			}
			cout << endl;
		}
    }

}

/** showpnminfo method:
    -------------------
    Description:
        Displays the information header.
**/

void pixmap::showpnminfo(){

    printf( "\n\tPNMINFOHEADER\n\n" );
	printf( "\t\tFormatSignature\t:\t%s\n", getFormatSignature());
    printf( "\t\tImageWidth\t:\t%d\n", getImageWidth());
    printf( "\t\tImageHeight\t:\t%d\n", getImageHeight());
    printf( "\t\tMaxValue\t:\t%d\n", getMaxValue());
    printf( "\t\tImageDataOffset\t:\t%d\n", getImageDataOffset());
    printf( "\t\tFileSize\t:\t%ld\n", getFileSize());
    printf( "\t\tImageSize\t:\t%ld\n", getImageSize());
    printf( "\t\tBitDepth\t:\t%d\n", getBitDepth());

    if( isFormat( '4' ) || isFormat( '5' ) || isFormat( '6' ))
        printf( "\t\tEncoding\t:\tRawBits\n" );
    else
        printf( "\t\tEncoding\t:\tASCII\n" );

    PNMCOMMENTS *com = Comments;

    if( com != NULL ){
        printf( "\nComments :\n\n" );
        while( com != NULL ){
            printf( "%s\n", com->Comment );
            com = com->next;
        }
    }

}

/** loadPnmPixel method:
    --------------------
    Description:
        Reads the file specified by the char pointer
        specified as argument, and the loads the image
        by calling getpnmpixel. This is the method user
        should call for loading a complete pixmap image
        and then start working.
**/

void pixmap::loadPnmPixel( char *loc ){

    fileLoc = loc;
    inputFile = fopen( fileLoc, "rb" );

    if ( inputFile != NULL ){
        readpnminfo();
        getpnmpixel();
    }else{
        cout << "Cannot open input file " << fileLoc << endl;
        exit( EXIT_FAILURE );
    }

}

/** SavePnmPixel method:
    --------------------
    Description:
        Takes the output filename as argument and writes
        the raw image data in binary format to that out-
        -put file, and closes handles to that file.
**/

void pixmap::SavePnmAsFile(){
    //
    char * destLoc = "_iconImage.tmp";
    FILE * outputFile = fopen( destLoc, "wb" );
    FILE * headerFile = fopen( "_info2D.tmp" , "w" );

    if ( outputFile == NULL && headerFile == NULL ){
        cout << "Cannot open output file " << destLoc << endl;
        exit( EXIT_FAILURE );
    }else{

        int bit = BitDepth / 8;

        if ( bit == 0 ){
            // Make modification if P1/P2
            cout << "Changing the format to P5." << endl;
            bit += 1;
        }

        cout << "Saving as RAW format." << endl;

        // Form the header for display

        fprintf( headerFile, "%d\n", ImageWidth );
        fprintf( headerFile, "%d\n", ImageHeight );
        fprintf( headerFile, "%d\n", bit );

        fclose( headerFile );

        // Form the Data part

        for ( int j = 0; j < ImageWidth; ++j ){
            for( int i = 0; i < ImageHeight; ++i ){
                for( int k = 0; k < bit; ++k ){
                    unsigned char rec = getValue( i, j, k );
                    fwrite( &rec, 1, 1, outputFile );
                }
            }
        }

        // close the handle on output file
        fclose( outputFile );

        cout << "File saved as " << destLoc << "." << endl;
    }
}
