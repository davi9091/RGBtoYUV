//
// Created by Arkady Rubtsov on 05/12/2018.
//

#include <iostream>
#include <cmath>
#include "yuv420.h"

YUVI420::YUVI420(char const *path, int width, int height, int frames) {

    FILE *file = fopen(path, "r+b");

    if (file == nullptr) {
        throw "YUV file is NULL";
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
    auto* temp_Y_data = new unsigned char[yuv_Y_frame_size];
    yuv_U_data = new unsigned char[yuv_U_frame_size * yuv_frames];
    auto* temp_U_data = new unsigned char[yuv_U_frame_size];
    yuv_V_data = new unsigned char[yuv_V_frame_size * yuv_frames];
    auto* temp_V_data = new unsigned char[yuv_V_frame_size];

    for (int i = 0; i < yuv_frames; ++i) {
        fread(temp_Y_data, sizeof(unsigned char), yuv_Y_frame_size, file);
        memcpy(yuv_Y_data+(i*yuv_Y_frame_size), temp_Y_data, yuv_Y_frame_size);
        fread(temp_U_data, sizeof(unsigned char), yuv_U_frame_size, file);
        memcpy(yuv_U_data+(i*yuv_U_frame_size), temp_U_data, yuv_U_frame_size);
        fread(temp_V_data, sizeof(unsigned char), yuv_V_frame_size, file);
        memcpy(yuv_V_data+(i*yuv_V_frame_size), temp_V_data, yuv_V_frame_size);
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

void YUVI420::addRGB(unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int rgb_width, int rgb_height) {

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

                temp = (int) std::lround(0.299 * (int)R_data[rgb_pos] + 0.587 * (int)G_data[rgb_pos] + 0.114 * (int)B_data[rgb_pos]);
                yuv_Y_data[yuv_pos] = (unsigned char) temp;
            }

            offset = offset + (yuv_width - rgb_width);
        }

        offset = offset + ((yuv_height - rgb_height) * yuv_width);
    }

    offset = 0;

    for (int i = 0; i < yuv_frames; ++i) {
        int yuv_pos = 0;
        int rgb_pos = 0;

        for (int j = 0; j < rgb_height; j += 2) {
            for (int k = 0; k < rgb_width; k += 2) {
                rgb_pos = rgb_pos + 2;
                yuv_pos = j*yuv_frames + rgb_pos + offset;

                int tempR = (int)std::lround(((int)R_data[rgb_pos] + (int)R_data[rgb_pos+1] + (int)R_data[rgb_pos + rgb_width] + (int)R_data[rgb_pos + rgb_width + 1]) / 4);
                int tempG = (int)std::lround(((int)G_data[rgb_pos] + (int)G_data[rgb_pos+1] + (int)G_data[rgb_pos + rgb_width] + (int)G_data[rgb_pos + rgb_width + 1]) / 4);
                int tempB = (int)std::lround(((int)B_data[rgb_pos] + (int)B_data[rgb_pos+1] + (int)B_data[rgb_pos + rgb_width] + (int)B_data[rgb_pos + rgb_width + 1]) / 4);

                temp = (int) std::lround(-0.147 * tempR - 0.289 * tempG + 0.436 * tempB);
                yuv_U_data[yuv_pos] = (unsigned char) temp;
                temp = (int) std::lround(0.615 * tempR - 0.515 * tempG - 0.100 * tempB);
                yuv_V_data[yuv_pos + yuv_U_frame_size] = (unsigned char) temp;
            }

            rgb_pos = rgb_pos + rgb_width;
            offset = offset + (yuv_width - rgb_width)/2;
        }

        offset = offset + ((yuv_height - rgb_height) * yuv_width)/4;
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