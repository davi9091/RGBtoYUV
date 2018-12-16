//
// Created by Arkady Rubtsov on 04/12/2018.
//

#include <iostream>
#include "bmp.h"

imageBMP::imageBMP(char const* path) {

    FILE* file = fopen(path, "rb");

    if (file == nullptr) {
        throw "BMP file is NULL";
    }

    fread(bm_header, sizeof(unsigned char), 54, file);

    bm_width = *(int*)&bm_header[18];
    bm_height = *(int*)&bm_header[22];

    // 54 first bytes is the header, which is 14-byte BITMAPFILEHEADER
    // and 40-byte BITMAPINFO.
    // I read it as one piece for convenience.
    // BITMAPINFO contains:
    // 0E 00 biSize - 4 bytes of DWORD, useless for us, since we have to consider padding
    // 12 04 biWidth - 4 bytes
    // 16 08 biHeight - 4 bytes
    // Pretty much all we have to know.

    bm_row_padded = (bm_width*3 + 3) & (~3);

    auto* bm_data = new unsigned char[bm_row_padded];

    for (int i = 0; i < bm_height; ++i) {
        fread(bm_data, sizeof(char), bm_row_padded, file);

        for(int j = 0; j < bm_row_padded; j += 3) {
            bm_R_data.push_back(bm_data[j+2]);
            bm_G_data.push_back(bm_data[j+1]);
            bm_B_data.push_back(bm_data[j]);
        }
    }

    fclose(file);
}

imageBMP::~imageBMP() = default;

std::vector <unsigned char> imageBMP::getRData() {
    return bm_R_data;
}

std::vector <unsigned char> imageBMP::getGData() {
    return bm_G_data;
}

std::vector <unsigned char> imageBMP::getBData() {
    return bm_B_data;
}

int imageBMP::getWidth() {
    return bm_width;
}

int imageBMP::getHeight() {
    return bm_height;
}

