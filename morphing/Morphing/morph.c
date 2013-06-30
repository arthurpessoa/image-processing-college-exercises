/* ====================================================================== 
 * morph.c -  Generate a metamorphosis sequence. 
 * Copyright (C) 1993 by George Wolberg 
 * 
 * Written by: George Wolberg, 1993 
 * ====================================================================== 
 */

#include "meshwarp.h"
#include <string.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * main: 
 * 
 * Main function to collect user parameters and pass them to morph(). 
 */ 
main(argc, argv) 
int   argc; 
char **argv; 
{ 
 int nframes; 
 char name[10]; 
 imageP I1, I2; 
 imageP M1, M2;

 /* make sure the user invokes this program properly */ 
 if(argc != 7) { 
  fprintf(stderr, "Usage: morph src.bw dst.bw src.XY dst.XY frames name\n"); 
  exit(1); 
 }

 /* read input image and meshes */ 
 I1 = readImage(argv[1], BW);  /* source image */ 
 I2 = readImage(argv[2], BW);  /* target image */ 
 M1 = readImage(argv[3], MESH);  /* source mesh */ 
 M2 = readImage(argv[4], MESH);  /* target mesh */ 
 nframes = atoi(argv[5]);  /* # frames */ 
 strcpy(name,   argv[6]);  /* out basename */

 morph(I1, I2, M1, M2, nframes, name); 
} 
  
 

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * morph: 
 * 
 * Generate a morph sequence of frames between images I1 and I2. 
 * Correspondence points among I1 and I2 are given in meshes M1 and M2. 
 * nframes frames are generated (including I1 and I2). 
 * The output is stored in files "basename_xxx.bw" where xxx are sequential 
 * 3-digit frame numbers. 
 */ 
morph(I1, I2, M1, M2, nframes, basename) 
imageP I1, I2; 
imageP M1, M2; 
int nframes; 
char *basename; 
{ 
 int  i, j, totalI, totalM; 
 double  w1, w2; 
 char  name[20]; 
 uchar *p1, *p2, *p3; 
 float *x1, *y1, *x2, *y2, *x3, *y3; 
 imageP I3, Iw1, Iw2, M3;

 /* allocate space for tmp images and mesh */ 
 M3  = allocImage(M1->width, M1->height, MESH); 
 I3  = allocImage(I1->width, I1->height, BW); 
 Iw1 = allocImage(I1->width, I1->height, BW); 
 Iw2 = allocImage(I1->width, I1->height, BW);

 /* eval total number of points in mesh (totalM) and image (totalI) */ 
 totalM = M1->width * M1->height; 
 totalI = I1->width * I1->height;

 /* copy first frame to basename_000.bw */ 
 sprintf(name, "%s_000.bw", basename); 
 saveImage(I1, name, BW); 
 printf("Finished Frame 0\n");

 for(i=1; i<nframes-1; i++) { 
  /* M3 <- linearly interpolate between M1 and M2 */ 
  w2 = (double) i / (nframes-1); 
  w1 = 1. - w2; 
  
  /* linearly interpolate M3 grid */ 
  x1 = (float *) M1->ch[0]; y1 = (float *) M1->ch[1]; 
  x2 = (float *) M2->ch[0]; y2 = (float *) M2->ch[1]; 
  x3 = (float *) M3->ch[0]; y3 = (float *) M3->ch[1]; 
  for(j=0; j<totalM; j++) { 
   x3[j] = x1[j]*w1 + x2[j]*w2; 
   y3[j] = y1[j]*w1 + y2[j]*w2; 
  }

  /* warp I1 and I2 according to grid M3 */ 
  meshWarp(I1, M1, M3, Iw1); 
  meshWarp(I2, M2, M3, Iw2);

  /* cross-dissolve warped images Iw1 and Iw2 */ 
  p1 = (uchar *) Iw1->ch[0]; 
  p2 = (uchar *) Iw2->ch[0]; 
  p3 = (uchar *) I3->ch[0]; 
  for(j=0; j<totalI; j++) p3[j] = p1[j]*w1 + p2[j]*w2;

  /* save frame into file */ 
  sprintf(name, "%s_%03d.bw", basename, i); 
  saveImage(I3, name, BW); 
  printf("Finished Frame %d\n", i); 
 }

 /* copy last frame to basename_xxx.bw */ 
 sprintf(name, "%s_%03d.bw", basename, i); 
 saveImage(I2, name, BW); 
 printf("Finished Frame %d\n", i);

} 
 