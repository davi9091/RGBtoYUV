//
// Created by Arkady Rubtsov on 04/12/2018.
//

#ifndef RGBTOYUV_BMP_H
#define RGBTOYUV_BMP_H

#include <sys/proc_info.h>
#include <cstdio>

class imageBMP {
private:

    // We store chars instead of int because they weigh less
    // Assuming BMP is 24-bit colour

    unsigned char bm_header[54]; // 14-byte BITMAPFILEHEADER and 40-byte BITMAPINFO

    int bm_width;
    int bm_height;
    // Width and height in pixels

    int bm_row_padded;
    // The size, including row-padding fix

    unsigned char* bm_data;
    // Raw data inside of bmp, stored as recurring B, G and R values (from 0 to 255)

    unsigned char* bm_R_data;
    unsigned char* bm_G_data;
    unsigned char* bm_B_data;

public:

    imageBMP(char const* path);
    ~imageBMP();

    int getWidth();
    int getHeight();

    unsigned char* getData();
    unsigned char* getRData();
    unsigned char* getGData();
    unsigned char* getBData();

};


#endif //RGBTOYUV_BMP_H
