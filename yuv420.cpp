//
// Created by Arkady Rubtsov on 05/12/2018.
//

#include <iostream>
#include <cmath>
#include "yuv420.h"

YUVI420::YUVI420(char const *path, int width, int height, int frames) {

    FILE *file = fopen(path, "r+b");

    if (file == nullptr) {
        throw "YUV file is not NULL";
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

    yuv_Y_data = new unsigned char[yuv_Y_frame_size * yuv_frames];
    yuv_U_data = new unsigned char[yuv_U_frame_size * yuv_frames];
    yuv_V_data = new unsigned char[yuv_V_frame_size * yuv_frames];

    for (int i = 0; i < yuv_frames; ++i) {
        fread((*this).yuv_Y_data, sizeof(unsigned char), yuv_Y_frame_size, file);
    }

    for (int i = 0; i < yuv_frames; ++i) {
        fread(yuv_U_data, sizeof(unsigned char), yuv_U_frame_size, file);
    }

    for (int i = 0; i < yuv_frames; ++i) {
        fread(yuv_V_data, sizeof(unsigned char), yuv_V_frame_size, file);
    }


    // reading each property data could be threaded.

    fclose(file);
}

YUVI420::~YUVI420() = default;

unsigned char *YUVI420::getYData() {
    return yuv_Y_data;
}

unsigned char *YUVI420::getUData() {
    return yuv_U_data;
}

unsigned char *YUVI420::getVData() {
    return yuv_V_data;
}

void YUVI420::convertRGB(unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int rgb_width, int rgb_height) {

    const double Kr = 0.2126;
    const double Kb = 0.0722;
    int temp;
    int offset = 0;


    for (int i = 0; i < yuv_frames; ++i) {
        int yuv_pos = 0;
        int rgb_pos = 0;

        for (int j = 0; j < rgb_height; ++j) {
            for (int k = 0; k < rgb_width; ++k) {
                rgb_pos++;
                yuv_pos = j*yuv_frames + rgb_pos + offset;
//                yuv_pos++;

                temp = (int) std::lround(Kr * (int)R_data[rgb_pos] + (1 - Kr - Kb) * (int)G_data[rgb_pos] + Kb * (int)B_data[rgb_pos]);
                yuv_Y_data[yuv_pos] = (unsigned char) temp;

                //this should work
            }
            offset = offset + (yuv_width - rgb_width);
        }
        offset = offset + ((yuv_height - rgb_height) * yuv_width) + yuv_U_frame_size + yuv_V_frame_size;
    }
}

void YUVI420::writeToFile(char const *path) {
    FILE* file = fopen(path, "w+b");

    int y_pos = 0;
    int u_pos = 0;
    int v_pos = 0;

    for( int i = 0; i < yuv_frames; ++i) {

        for (int f = 0; f < yuv_Y_frame_size; ++f) {
            fprintf(file, "%c", yuv_Y_data[y_pos]);
            ++y_pos;
        }

        for (int f = 0; f < yuv_U_frame_size; ++f) {
            fprintf(file, "%c", yuv_U_data[u_pos]);
            ++u_pos;
        }

        for (int f = 0; f < yuv_V_frame_size; ++f) {
            fprintf(file, "%c", yuv_V_data[v_pos]);
            ++v_pos;
        }
    }

    fclose(file);
}