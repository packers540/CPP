#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#pragma pack(push,1)

typedef struct
{
    unsigned short type;            /* 2 bytes */
    unsigned int filesize1;         /* 4 bytes */
    unsigned short reserved1;       /* 2 bytes */
    unsigned short reserved2;       /* 2 bytes */
    unsigned int offset;            /* 4 bytes */
}BITMAPFILEHEADER1;               /*14 bytes TOTAL */

typedef struct
{
    unsigned int filesize2;         /* 4 bytes */
    int width;		                /* 4 bytes */
    int height;                     /* 4 bytes */
    unsigned short planes;          /* 2 bytes */
    unsigned short bitsPerPixel;    /* 2 bytes */
    unsigned int compression;       /* 4 bytes */
    unsigned int imageSize;         /* 4 bytes */
    int xPelsPerMeter;              /* 4 bytes */
    int yPelsPerMeter;              /* 4 bytes */
    unsigned int clrUsed;           /* 4 bytes */
    unsigned int clrImportant;      /* 4 bytes */
}BITMAPINFOHEADER1;

typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved;
}RGBQUAD1;

class Bitmap
{

  public:
       Bitmap()
       {
           bmpheader.reserved1 = 0;
           bmpheader.reserved2 = 0;
           bmpinfo.planes = 1;
       }
       ~Bitmap(){}

     //functions to return all image data arrays
     unsigned char* getOriginal(){return original;}
     unsigned char* getOverlay(){return overlay;}
     unsigned char* getHistogram(){return histogram;}
     unsigned char* getEditImageBrightness(){return editImageBrightness;}
     unsigned char* getEditImageContrast(){return editImageContrast;}

     //functions to get height and width of an image
     int getHeight(){return bmpinfo.height;}
     int getWidth(){return bmpinfo.width;}
     int getOverlayHeight(){return overlayInfo.height;}
     int getOverlayWidth(){return overlayInfo.width;}


    void loadOriginalBitmap(char*,int);
    void loadOverlayBitmap(char*,int);
    void loadHistogramImage(char*,int);
    void saveBitmap(char*,unsigned char*,int);
    void saveHistBitmap(char*,unsigned char*,int);
    void checkImageData(unsigned char*); //for testing purposes to see if image pointer is outputting the correct data pixel values
    unsigned char* overLayImages(unsigned char*,unsigned char*);
    unsigned char* histEqualization(unsigned char*);
    void Bitmap::loadEditImage(char*, int);
    void adjustBrightness(int);
    void adjustContrast(int);
    void reset();




  private: //object names of the other structs
        BITMAPFILEHEADER1 bmpheader;
        BITMAPINFOHEADER1 bmpinfo;

        BITMAPFILEHEADER1 overlayHeader;
        BITMAPINFOHEADER1 overlayInfo;

        BITMAPFILEHEADER1 histHeader;
        BITMAPINFOHEADER1 histInfo;

        RGBQUAD1 palette[256];

        //array to store original image data
        unsigned char* original;
        //array to store overlay image data
        unsigned char* overlay;
        //array to store image data that is going to be equalized
        unsigned char* histogram;
        //array to store image data edited by brightness slider
        unsigned char* editImageContrast;
        //array to store image data edited by the contrast slider
        unsigned char* editImageBrightness;

        //variables to keep track of previous slider setting when switching between sliders
        //this makes sure the slider value does not stack with the previous value
        //ie if you set you slider to 2x then to 3x, without these variables it would effect the image 6x
        //instead of 3x
        int previousBrightnessValue = 10;
        int previousContrastValue = 950;
        int tempBrightnessSliderValue = 10;
        int tempContrastSliderValue = 950;
};

#pragma pack(pop)

#endif // BITMAP_H_INCLUDED
