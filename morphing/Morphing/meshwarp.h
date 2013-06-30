/* ====================================================================== 
 * meshwarp.h -  Mesh warping header file. 
 * Copyright (C) 1993 by George Wolberg 
 * 
 * Written by: George Wolberg, 1993 
 * ====================================================================== 
 */

#include <stdio.h>
#include <stdlib.h>

#define BW  0 
#define MESH  1 
#define MAX(A,B) ((A) > (B) ? (A) : (B)) 
#define MIN(A,B) ((A) < (B) ? (A) : (B))

typedef unsigned char uchar;

typedef struct {  /* image data structure  */ 
 int width;  /* image width  (# cols) */ 
 int height;  /* image height (# rows) */ 
 void *ch[2];  /* pointers to channels  */ 
} imageS, *imageP;

/* extern declarations for functions in meshwarp.c */ 
extern void meshWarp(); 
extern void resample();

/* extern declarations for functions in util.c */ 
extern imageP readImage(); 
extern int saveImage(); 
extern imageP allocImage(); 
extern void freeImage(); 
 