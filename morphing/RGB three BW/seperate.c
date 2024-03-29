/********************************************************************/  
/*Seperate SGI color image to BW image files                          */ 
/*File name: seperate.c                                              */ 
/*Author:    Yurong Sun                                               */ 
/*Description:                                                        */ 
/*Read color SGI format image file                                    */ 
/*Create three grayscale BW format images relative to r, g, b channels*/ 
/********************************************************************/ 

#include "stdio.h" 
#include <math.h>  

putbyte(outf,val) 
FILE *outf; 
unsigned char val; 
{ 
    unsigned char buf[1]; 
  
    buf[0] = val; 
    fwrite(buf,1,1,outf); 
} 
  
putshort(outf,val) 
FILE *outf; 
unsigned short val; 
{ 
    unsigned char buf[2]; 
  
    buf[0] = (val>>8); 
    buf[1] = (val>>0); 
    fwrite(buf,2,1,outf); 
} 
  
static int putlong(outf,val) 
FILE *outf; 
unsigned long val; 
{ 
    unsigned char buf[4]; 
  
    buf[0] = (val>>24); 
    buf[1] = (val>>16); 
    buf[2] = (val>>8); 
    buf[3] = (val>>0); 
    return fwrite(buf,4,1,outf); 
}


unsigned short getshort(FILE *inf) 
{ 
 unsigned char buf[2]; 
 fread(buf, 2, 1, inf); 
 return (buf[0]<<8) + (buf[1]<<0); 
}

static long getlong(FILE *inf) 
{ 
 unsigned char buf[4]; 
 fread(buf, 4, 1, inf); 
 return (buf[0]<<24) + (buf[1]<<16)+ (buf[2]<<8) + (buf[3]<<0); 
}

#define IXSIZE  (800) 
#define IYSIZE  (800) 
#define IZSIZE  (3)

main(argc, argv) 
int   argc; 
char **argv; 
{ 
    FILE *of, *inf;
    char iname[80]; 
 unsigned char inbuf[IXSIZE][IYSIZE][IZSIZE]; 
    int i, x, y,z; 
 unsigned short magic, dimension, ixsi, iysi, izsi, ixsi1, iysi1; 
 static long colormap, pixmin, pixmax; 
 char storage, bpc; 
  
 /* make sure the user invokes this program properly */ 
 if(argc != 5) { 
  fprintf(stderr, "Usage: seperate in.rgb outr.bw outg.bw outb.bw\n"); 
  return 1; 
 }

 /* Read the input RGB file*/ 
 if ((inf=fopen(argv[1], "r"))==NULL) 
 { 
  fprintf(stderr, "readImage: Can't open file %s\n", argv[1]); 
  return 1; 
 } 
 else 
 { 
  magic = getshort(inf); /* 2 bytes short magic */ 
  storage = fgetc(inf); /* 1 byte char storage */ 
  bpc = fgetc(inf);  /* 1 byte char bpc */ 
  dimension = getshort(inf);/* 2 bytes short dimension */

  ixsi = getshort(inf);  /* 2 bytes xsize */ 
  iysi = getshort(inf);  /* 2 bytes ysize */ 
  izsi = getshort(inf);  /* 2 bytes zsize */

  pixmin = getlong(inf); /* 4 bytes pixel minimum */ 
  pixmax = getlong(inf); /* 4 bytes pixel maximum */

  for (i = 0; i < 84; i++) 
   fgetc(inf);  /* 4 bytes char dummy and 80 bytes char imagename */

  colormap = getlong(inf);

  for (i = 0; i < 404; i++) 
   fgetc(inf);  /* 404 byters char dummy */

  for (z=0; z < izsi; z++) 
   for (y=0; y < iysi; y++) 
    for (x=0; x < ixsi; x++) 
     fread(&inbuf[x][y][z], 1, 1, inf); 
 } 
 fclose(inf);

/*Begin to write output files */ 
 ixsi1=0; 
 iysi1=0; 
 /* output the red channel BW file */ 
    of = fopen(argv[2],"w"); 
    if(!of) { 
        fprintf(stderr,"sgiimage: can't open output file\n"); 
        return 1; 
    } 
 putshort(of, ixsi1); 
 putshort(of, ixsi); 
 putshort(of, iysi1); 
 putshort(of, iysi);

 for (y=0; y < iysi; y++) 
  for (x=0; x < ixsi; x++) 
   fwrite(&inbuf[x][y][0], 1, 1, of);

 fclose(of);

 /* output the green channel BW file */ 
    of = fopen(argv[3],"w"); 
    if(!of) { 
        fprintf(stderr,"sgiimage: can't open output file\n"); 
        return 1; 
    } 
 putshort(of, ixsi1); 
 putshort(of, ixsi); 
 putshort(of, iysi1); 
 putshort(of, iysi);

 for (y=0; y < iysi; y++) 
  for (x=0; x < ixsi; x++) 
   fwrite(&inbuf[x][y][1], 1, 1, of);

 fclose(of);

 /* output the blue channel BW file */ 
    of = fopen(argv[4],"w"); 
    if(!of) { 
        fprintf(stderr,"sgiimage: can't open output file\n"); 
        return 1; 
    } 
 putshort(of, ixsi1); 
 putshort(of, ixsi); 
 putshort(of, iysi1); 
 putshort(of, iysi);

 for (y=0; y < iysi; y++) 
  for (x=0; x < ixsi; x++) 
   fwrite(&inbuf[x][y][2], 1, 1, of);

 fclose(of); 
}