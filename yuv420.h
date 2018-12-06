//
// Created by Arkady Rubtsov on 05/12/2018.
//

#ifndef RGBTOYUV_YUV420_H
#define RGBTOYUV_YUV420_H

class YUVI420 {
private:
    int yuv_width;
    int yuv_height;

//    int yuv_frame_size;

    int yuv_Y_frame_size;
    int yuv_U_frame_size;
    int yuv_V_frame_size;

    int yuv_frames;


    // apparently YUVI420 (same as YV12) doesn't store any data
    // for width, height or size of image inside.

    unsigned char* yuv_Y_data;
    unsigned char* yuv_U_data;
    unsigned char* yuv_V_data;


public:

    YUVI420(char const* path, int width, int height, int frames);
    ~YUVI420();

    int getWidth();
    int getHeigth();

    unsigned char* getYData();
    unsigned char* getUData();
    unsigned char* getVData();



};

#endif //RGBTOYUV_YUV420_H
