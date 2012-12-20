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

//#include <windows.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glut.h>
//#include <gl/glext.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

// Global Variable Declaration
GLubyte *img;
int height;
int width;
int bit;

/* Called to draw scene */
void RenderScene( void )
{
    // Clear the window with current clearing color
    glClear( GL_COLOR_BUFFER_BIT );
    // Set color to white
    glColor3f( 1.0f, 1.0f, 1.0f );
    // Set raster position for this "square"
    glRasterPos2f( -1.0f, -1.0f );

    /* Draw the pixmap */
    //GL_LUMINANCE for grayscale images & GL_RGB or GL_BGR for colored images
    glDrawPixels( width, height, bit == 1 ? GL_LUMINANCE : \
    GL_RGB, GL_UNSIGNED_BYTE, img);

    // Do the buffer swap
    glutSwapBuffers();
    glFlush();
}

/* Set up the rendering state */
void SetupRC( void )
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/* Main program entry point */
int main( int argc, char* argv[] )
{
//    STARTUPINFO si;
//    PROCESS_INFORMATION pi;
//
//    ZeroMemory( &si, sizeof(si) );
//    si.cb = sizeof(si);
//    ZeroMemory( &pi, sizeof(pi) );
//
//    if ( ! CreateProcess(
//                NULL,
//                "f3dPro.exe",
//                NULL,
//                NULL,
//                FALSE,
//                0,
//                NULL,
//                NULL,
//                &si,
//                &pi))
//        {
//            fprintf( stderr, "Create Process failed.\n" );
//            return -1;
//        }
//
//    WaitForSingleObject( pi.hProcess, INFINITE );
//    printf( "Child Complete.\n" );
//
//    CloseHandle( pi.hProcess );
//    CloseHandle( pi.hThread );

    FILE *fp, *fh;
    fp = fopen( "_iconImage.tmp", "rb" );
    fh = fopen( "_info2D.tmp", "r" );
    if( fp == NULL && fh == NULL ){
        cout << "Cannot read _iconImage.tmp" << endl;
        exit(-1);
    }

    fscanf( fh, "%d\n", &width );
    fscanf( fh, "%d\n", &height );
    fscanf( fh, "%d\n", &bit );

    fclose( fh );

    cout << "Read Header Successfully" << endl;

//    cout << "width = " << width << endl;
//    cout << "height = " << height << endl;
//    cout << "bit = " << bit << endl;

    /* the bitmap image to be displayed */
    img = ( GLubyte* ) calloc( sizeof(GLubyte), width * height * bit );

    if( img == NULL ){
        cout << "Couldn't allocate memory" << endl;
        exit(-2);
    }

    // reading the image data part
    int i = width * height * bit - 1;
    GLubyte rec;
    while( fread (&rec, 1, 1, fp) ) {
        *(img + i) = rec;
        //cout << i << ":" << *(img + i) << endl;
        i--;
    }

    cout << "Image data read successfully" << endl;

    fclose( fp );

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( width, height );
    glutInitWindowPosition( 400, 150 );
    glutCreateWindow( "PNM View" );
    glutDisplayFunc( RenderScene );
    SetupRC();
    glutMainLoop();

    return 0;
}
