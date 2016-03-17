#include "bitmap.h"
#include <fstream>

void Bitmap::loadOriginalBitmap(char* filename, int MAX)
{
    FILE* in = fopen(filename, "rb");

    if(NULL == in)
    {
        cout<<"Could not open file!"<<endl;
        exit(1);
    }

    fread(&bmpheader, sizeof(BITMAPFILEHEADER1), 1, in); //read in the values for BITMAPFILEHEADER
    fread(&bmpinfo, sizeof(BITMAPINFOHEADER1), 1, in); //read in the value for BITMAPINFOHEADER
    fread(&palette, sizeof(RGBQUAD1), MAX, in);  //read in the color table for the bitmap

    int picture = bmpinfo.height*bmpinfo.width;
    original = new unsigned char[picture];

    fseek(in, bmpheader.offset, SEEK_SET);
    fread(original, sizeof(unsigned char), picture, in);
    fclose(in);

}

void Bitmap::loadOverlayBitmap(char* filename, int MAX)
{
    FILE* in = fopen(filename, "rb");

    if(NULL == in)
    {
        cout<<"Could not open file!"<<endl;
        exit(1);
    }

    fread(&overlayHeader, sizeof(BITMAPFILEHEADER1), 1, in); //read in the values for BITMAPFILEHEADER
    fread(&overlayInfo, sizeof(BITMAPINFOHEADER1), 1, in); //read in the value for BITMAPINFOHEADER
    fread(&palette, sizeof(RGBQUAD1), MAX, in);  //read in the color table for the bitmap

    int picture = overlayInfo.height*overlayInfo.width;
    overlay = new unsigned char[picture];

    fseek(in, overlayHeader.offset, SEEK_SET);
    fread(overlay, sizeof(unsigned char), picture, in);
    fclose(in);

}

void Bitmap::checkImageData(unsigned char* image)
{
    int height = getHeight();
    int width = getWidth();
    int frameSize = height*width;

 for(int i = 0; i < frameSize; ++i)
   cout<<(int)image[i]<<" ";
}

unsigned char* Bitmap::overLayImages(unsigned char* image, unsigned char* overlay) //first slot is for the image, and the second slot is for the overlay text
{
    int height = getHeight();
    int width = getWidth();
    int frameSize = height*width;

    for(int i = 0; i < frameSize; ++i)
    {
         if(overlay[i] == 0) //if the overlay pixel is black, change it to white
           overlay[i] = 255;
         else
           overlay[i] = image[i]; //if the overlay pixel is not black, change it to the images pixel
    }

    return overlay;
}

void Bitmap::saveBitmap(char* filename, unsigned char* overlayImage, int MAX)
{
    FILE* out;

    int height = getHeight();
    int width = getWidth();
    int pixels = height*width;

    out = fopen(filename, "wb");

    if(NULL == out)
    {
        cout<<"Could not create file!"<<endl;
        exit(1);
    }

    fwrite((char*)&(bmpheader), sizeof(BITMAPFILEHEADER1), 1, out); //write the header file to .bmp file
    fwrite((char*)&(bmpinfo), sizeof(BITMAPINFOHEADER1), 1, out);  //write the header info file to .bmp file


    for(int i = 0; i < MAX; ++i)
    {
        palette[i].blue = (unsigned char)i;
        palette[i].green = (unsigned char)i;
        palette[i].red = (unsigned char)i;
        palette[i].reserved = 0;
    }

    for(int i = 0; i < MAX; ++i)
    {
        fwrite((char*)&(palette[i].blue), 1, 1, out);
        fwrite((char*)&(palette[i].green), 1, 1, out);
        fwrite((char*)&(palette[i].red), 1, 1, out);
        fwrite((char*)&(palette[i].reserved), 1, 1, out);
    }

    for(int i = 0; i < pixels; ++i)
    {
        fwrite((char*)&(overlayImage[i]), 1, 1, out);
    }

    fclose(out);
}
void Bitmap::loadHistogramImage(char* filename, int MAX)
{
    FILE* in = fopen(filename, "rb");

    if(NULL == in)
    {
        cout<<"Could not open file!"<<endl;
        exit(1);
    }

    fread(&histHeader, sizeof(BITMAPFILEHEADER1), 1, in); //read in the values for BITMAPFILEHEADER
    fread(&histInfo, sizeof(BITMAPINFOHEADER1), 1, in); //read in the value for BITMAPINFOHEADER
    fread(&palette, sizeof(RGBQUAD1), MAX, in);  //read in the color table for the bitmap

    int picture = histInfo.height*histInfo.width;
    histogram = new unsigned char[picture];

    fseek(in, histHeader.offset, SEEK_SET);
    fread(histogram, sizeof(unsigned char), picture, in);
    fclose(in);

}

void Bitmap::loadEditImage(char* filename, int MAX)
{
    FILE* in = fopen(filename, "rb");

    if(NULL == in)
    {
        cout<<"Could not open file!"<<endl;
        exit(1);
    }

    fread(&histHeader, sizeof(BITMAPFILEHEADER1), 1, in); //read in the values for BITMAPFILEHEADER
    fread(&histInfo, sizeof(BITMAPINFOHEADER1), 1, in); //read in the value for BITMAPINFOHEADER
    fread(&palette, sizeof(RGBQUAD1), MAX, in);  //read in the color table for the bitmap

    int picture = histInfo.height*histInfo.width;
    histogram = new unsigned char[picture];
    editImageContrast = new unsigned char[picture];
    editImageBrightness = new unsigned char[picture];


    fseek(in, histHeader.offset, SEEK_SET);
    fread(histogram, sizeof(unsigned char), picture, in);
    fclose(in);

    //fill editing arrays with loaded image data
    for (int i = 0; i < picture; i++)
    {
        editImageBrightness[i] = histogram[i];
        editImageContrast[i] = histogram[i];
    }
}

unsigned char* Bitmap::histEqualization(unsigned char* image)
{
    int* histogram = new int[256];
    int* lookuptable = new int[256];

     //initialize historgram with all zeros
     for (int i = 0; i < 256; i++)
        histogram[i] = 0;

    //initialize lookup table with all zeros
     for (int i = 0; i < 256; i++)
        lookuptable[i] = 0;

    //build histrogram from image data
    for (int i = 0; i < (histInfo.height*histInfo.width); i++)
        histogram[image[i]] = histogram[image[i]] + 1;

    //build lookup tabled from histogram data
    for (int i = 1; i < 256; i++)
        lookuptable[i] = lookuptable[i - 1] + histogram[i];

    //rebuiuld image data with equalized values
     for (int i = 0; i < (histInfo.height*histInfo.width); i++)
     {
        int temp = (lookuptable[image[i]] *255) / (histInfo.height*histInfo.width);
        if (temp > 255)
            image [i] = 255;
        else
            image[i] = temp;
     }

    return image;
}

void Bitmap::saveHistBitmap(char* filename, unsigned char* image, int MAX)
{
    FILE* out;

    out = fopen(filename, "wb");

    if(NULL == out)
    {
        cout<<"Could not create file!"<<endl;
        exit(1);
    }

    fwrite((char*)&(histHeader), sizeof(BITMAPFILEHEADER1), 1, out); //write the header file to .bmp file
    fwrite((char*)&(histInfo), sizeof(BITMAPINFOHEADER1), 1, out);  //write the header info file to .bmp file


    for(int i = 0; i < MAX; ++i)
    {
        palette[i].blue = (unsigned char)i;
        palette[i].green = (unsigned char)i;
        palette[i].red = (unsigned char)i;
        palette[i].reserved = 0;
    }

    for(int i = 0; i < MAX; ++i)
    {
        fwrite((char*)&(palette[i].blue), 1, 1, out);
        fwrite((char*)&(palette[i].green), 1, 1, out);
        fwrite((char*)&(palette[i].red), 1, 1, out);
        fwrite((char*)&(palette[i].reserved), 1, 1, out);
    }

    for(int i = 0; i < (histInfo.width*histInfo.height); ++i)
    {
        fwrite((char*)&(image[i]), 1, 1, out);
    }

    fclose(out);
}

void Bitmap::adjustBrightness(int value)
{
    //log where the contrast slider was when brightness editing began
    //so contrast stays the same when returning to editing the contrast
    previousContrastValue = tempContrastSliderValue;

    int temp;
    int* histogram = new int[256];



    //scale image data by a factor determined by slider not letting values exceed 255 or go below 0
    //Also divide out old brightness slider value so slider values do not multiplicatively stack
    for (int i = 0; i < (histInfo.height * histInfo.width); i++)
    {
        temp = (editImageContrast[i] * (value/10.0)) / (previousBrightnessValue/10.0);
        if (temp > 255)
            editImageBrightness[i] = 255;
        else if (temp < 1)
            editImageBrightness[i] = 0;
        else
            editImageBrightness[i] = temp;
    }
    ofstream myfile("brightness.csv");
    for (int i = 0; i < 256; i++)
       histogram[i] = 0;

    for (int i =0; (i < histInfo.width * histInfo.height); i++)
        histogram[editImageBrightness[i]] = histogram[editImageBrightness[i]] + 1;

    for (int z = 0; z < 256; z++)
        myfile<<histogram[z]<<","<<endl;



    //log slider value when leaving brightness editing slider
    tempBrightnessSliderValue = value;
}

void Bitmap::adjustContrast(int value)
{
    //log where the brightness slider was when contrast editing began
    //so brightness stays the same when returning to editing the brightness
    previousBrightnessValue = tempBrightnessSliderValue;


    int* histogram = new int[256];
    int* lookuptable = new int[256];
    int* histogram1 = new int[256];


     //initialize historgram with all zeros
     for (int i = 0; i < 256; i++)
        histogram[i] = 0;

    //initialize lookup table with all zeros
     for (int i = 0; i < 256; i++)
        lookuptable[i] = 0;

    //build histrogram from brightness adjusted image data
    for (int i = 0; i < (histInfo.height*histInfo.width); i++)
        histogram[editImageBrightness[i]] = histogram[editImageBrightness[i]] + 1;

    //build lookup tabled from histogram data and skew data based on slider value and divide out old slider value so it does not stack
    for (int i = 1; i < 256; i++)
        lookuptable[i] = ((lookuptable[i - 1] + histogram[i]) * (value/950.0)) / (previousContrastValue/950.0);

    //rebuiuld image data with equalized values, not allowing values to exceed 255 or go below 0
     for (int i = 0; i < (histInfo.height*histInfo.width); i++)
     {
        int temp = (lookuptable[editImageBrightness[i]] *255) / (histInfo.height*histInfo.width);
        if (temp > 255)
            editImageContrast [i] = 255;
        else if (temp < 1)
            editImageContrast[i] = 0;
        else
            editImageContrast[i] = temp;
     }

     ofstream myfile("contrast.csv");
     for (int i = 0; i < 256; i++)
        histogram1[i] = 0;

     for (int i =0; (i < histInfo.width * histInfo.height); i++)
         histogram1[editImageContrast[i]] = histogram1[editImageContrast[i]] + 1;

     for (int z = 0; z < 256; z++)
         myfile<<histogram1[z]<<","<<endl;

    //log constrast slider value to return to
    tempContrastSliderValue = value;
}


//function to reset the sliders and all changes made to an image
void Bitmap::reset()
{
    previousBrightnessValue = 10;
    previousContrastValue = 950;
    //refil editing arrays with original image data
    for (int i = 0; i < (histInfo.width * histInfo.height); i++)
    {
        editImageBrightness[i] = histogram[i];
        editImageContrast[i] = histogram[i];
    }
}
