//
// Created by Arkady Rubtsov on 04/12/2018.
//

#include <iostream>
#include "bmp.h"

imageBMP::imageBMP(char const* path) {

    FILE* file = fopen(path, "rb");

    if (file != nullptr) {
        std::cout << "file is not null!" << std::endl;
    }

    fread(bm_header, sizeof(unsigned char), 54, file);

    bm_width = *(int*)&bm_header[18];
    bm_height = *(int*)&bm_header[22];

    // BITMAPINFO contains:
    // 0E 00 biSize - 4 bytes of DWORD, useless for us, since we have to consider padding
    // 12 04 biWidth - 4 bytes
    // 16 08 biHeight - 4 bytes
    // Pretty much all we have to know

    bm_row_padded = (bm_width*3 + 3) & (~3);

    auto* bm_data = new unsigned char[bm_row_padded];

    auto* bm_R_data = new unsigned char[bm_row_padded / 3];
    auto* bm_G_data = new unsigned char[bm_row_padded / 3];
    auto* bm_B_data = new unsigned char[bm_row_padded / 3];

    for (int i = 0; i < bm_height; i++) {
        fread(bm_data, sizeof(unsigned char), bm_row_padded, file);
        for(int j = 0; j < bm_width*3; j += 3) {
            bm_B_data[j] = bm_data[j];
            bm_G_data[j+1] = bm_data[j+1];
            bm_R_data[j+2] = bm_data[j+2];
        }
    }



    fclose(file);
}

imageBMP::~imageBMP() = default;

unsigned char* imageBMP::getData() {
    return bm_data;
}

unsigned char* imageBMP::getRData() {
    return bm_R_data;
}

unsigned char* imageBMP::getGData() {
    return bm_G_data;
}

unsigned char* imageBMP::getBData() {
    return bm_B_data;
}

int imageBMP::getWidth() {
    return bm_width;
}

int imageBMP::getHeight() {
    return bm_height;
}

