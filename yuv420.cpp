//
// Created by Arkady Rubtsov on 05/12/2018.
//

#include <iostream>
#include "yuv420.h"

YUVI420::YUVI420(char const *path, int width, int height, int frames) {

    FILE* file = fopen(path, "rb");

    yuv_width = width;
    yuv_height = height;
    yuv_frames = frames;

    yuv_frame_size = (yuv_width * yuv_height) * 3 / 2;
    // For this to work we assume that height and width values are even numbers

    yuv_frames = frames;

    auto* yuv_data = new unsigned char[yuv_frame_size * yuv_frames];

    for ( int i = 0; i < yuv_frames; ++i) {
        fread(yuv_data, sizeof(unsigned char), yuv_frame_size, file);
    }

    fclose(file);
}

// TODO: make destructor and functions