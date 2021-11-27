// ./a.out ./fast_rescaled.ppm ./vanilla_rescaled.ppm 

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

unsigned char *readPPMimage(const char *filename, int *sx, int *sy)
{
 // Reads an image from a .ppm file. A .ppm file is a very simple image representation
 // format with a text header followed by the binary RGB data at 24bits per pixel.
 // The header  has the following form:
 //
 // P6
 // # Optionally, one or more comment lines preceded by '#'
 // 340 200
 // 255
 //
 // The first line 'P6' is the .ppm format identifier, this is followed by one or more
 // lines with comments, typically used to inidicate which program generated the
 // .ppm file.
 // After the comments, a line with two integer values specifies the image resolution
 // as number of pixels in x and number of pixels in y.
 // The final line of the header stores the maximum value for pixels in the image,
 // usually 255.
 // After this last header line, binary data stores the RGB values for each pixel
 // in row-major order. Each pixel requires 3 bytes ordered R, G, and B.
 //
 // NOTE: Windows file handling is rather crotchetty. You may have to change the
 //       way this file is accessed if the images are being corrupted on read
 //       on Windows.
 //
 // readPPMdata converts the image colour information to floating point. This is so that
 // the texture mapping function doesn't have to do the conversion every time
 // it is asked to return the colour at a specific location.
 //
 // On error, the function returns NULL
 //

 FILE *f;
 unsigned char *im;
 char line[1024];
 int sizx,sizy;

 f=fopen(filename,"rb+");
 if (f==NULL)
 {
  fprintf(stderr,"Unable to open file %s for reading, please check name and path\n",filename);
  return(NULL);
 }
 fgets(&line[0],1000,f);
 if (strcmp(&line[0],"P6\n")!=0)
 {
  fprintf(stderr,"Wrong file format, not a .ppm file or header end-of-line characters missing\n");
  fclose(f);
  return(NULL);
 }

 // Skip over comments
 fgets(&line[0],511,f);
 while (line[0]=='#')
 {
  fgets(&line[0],511,f);
 }
 sscanf(&line[0],"%d %d\n",&sizx,&sizy);           // Read file size
 *(sx)=sizx;
 *(sy)=sizy;

 fgets(&line[0],9,f);  	                // Read the remaining header line
 im=(unsigned char *)calloc(sizx*sizy*3,sizeof(unsigned char));
 if (im==NULL)
 {
  fprintf(stderr,"Out of memory allocating space for image\n");
  fclose(f);
  return(NULL);
 }

 fread(im,sizx*sizy*3*sizeof(unsigned char),1,f);
 fclose(f);
 return(im);
}

int main(int argc, char *argv[]){
    // argv[1] - vanillaName
    // argv[2] - fastName
    // are image names
    unsigned char * vanilla;
    unsigned char * fast;


    int sx,sy;

    vanilla=readPPMimage(argv[1], &sx, &sy);
    fast=readPPMimage(argv[2], &sx, &sy);

    for(int i=0; i<sx*sy; i++){
        if( fabs( vanilla[i] - fast[i]) >1.2){
            printf("(i, vanilla, fast) (%d, %d, %d)", i, vanilla[i], fast[i]);
        }
    }

    return 0;
}