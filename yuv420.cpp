//
// Created by Arkady Rubtsov on 05/12/2018.
//

#include <iostream>
#include "yuv420.h"

YUVI420::YUVI420(char const *path, int width, int height, int frames) {

    FILE *file = fopen(path, "r+b");

    if (file != nullptr) {
        std::cout << "YUV file is not NULL" << '\n';
    }

    yuv_width = width;
    yuv_height = height;
    yuv_frames = frames;

//    yuv_frame_size = (yuv_width * yuv_height) * 3 / 2;

    yuv_Y_frame_size = (yuv_width * yuv_height);
    yuv_U_frame_size = (yuv_width * yuv_height) / 4;
    yuv_V_frame_size = yuv_U_frame_size; // Why calculate when you can NOT calculate?

    // For this to work we assume that height and width values are even numbers (and they SHOULD be)

    yuv_frames = frames;

    auto *yuv_Y_data = new unsigned char[yuv_Y_frame_size * yuv_frames];
    auto *yuv_U_data = new unsigned char[yuv_U_frame_size * yuv_frames];
    auto *yuv_V_data = new unsigned char[yuv_V_frame_size * yuv_frames];

    for (int i = 0; i < yuv_frames; ++i) {
        fread(yuv_Y_data, sizeof(unsigned char), yuv_Y_frame_size, file);
    }

    for (int i = 0; i < yuv_frames; ++i) {
        fread(yuv_U_data, sizeof(unsigned char), yuv_U_frame_size, file);
    }

    for (int i = 0; i < yuv_frames; ++i) {
        fread(yuv_V_data, sizeof(unsigned char), yuv_V_frame_size, file);
    }

    std::cout << yuv_Y_data << std::endl;
    // reading each property data could be threaded.

    fclose(file);
}

YUVI420::~YUVI420() = default;

unsigned char *YUVI420::getYData() {
    std::cout << yuv_Y_data << std::endl;
    return yuv_Y_data;
}

unsigned char *YUVI420::getUData() {
    return yuv_U_data;
}

unsigned char *YUVI420::getVData() {
    return yuv_V_data;
}