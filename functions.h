#ifndef PROGRAMMENWURF_FUNCTIONS_H
#define PROGRAMMENWURF_FUNCTIONS_H

//Settings
#define MYFILENAME "testimage.ppm" // Your Filename
#define X_PIXEL 2000 //Width of the Image
#define Y_PIXEL 2000 //Height of the Image
#define BACKGROUND 255 //Backgroundcolor
#define LINECOLOR 0 //Linecolor

#include <stdio.h>
#include <stdlib.h>

extern int cor[X_PIXEL][Y_PIXEL];

void create_ppm();
void setbackground();
void findcenter(int middle[]);
void drawline(int A[], int B[]);

#endif //PROGRAMMENWURF_FUNCTIONS_H
