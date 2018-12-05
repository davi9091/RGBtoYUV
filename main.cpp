/*
    Открыть файл, содержащий видеоряд (YUV420) и файл BMP, содержащий
    небольшую картинку (RGB).

    Сделать для картинки преобразование  RGB ->YUV420.
    Предполагается, что BMP файл содержит только данные в формате RGB 24 бит/пиксел без альфа канала, без палитры,
    без компрессии.

    Наложить поверх каждого кадра видеоряда картинку и сохранить результат в выходной файл (YUV420). Размер bmp картинки
    может быть меньше либо равен размеру картинки входного видеоряда/
 */

#include <iostream>
#include "bmp.h"


// This is deprecated, leaving it here just in case
unsigned char* readBMP(char const* filepath) {

    FILE* file = fopen(filepath, "rb");

    if (file == nullptr) {
        throw "File is NULL";
    }

    // Make sure we open something

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file);
    // BMP consists of 54-byte header: 14-byte BITMAPFILEHEADER and 40-byte BITMAPINFO

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    // Take width and height of the image

    int row_padded = (width*3 + 3) & (~3);
    // This is the size of bmp image without padding

    auto* data = new unsigned char[row_padded];

    for(int i = 0; i < height; ++i) {
        fread(data, sizeof(unsigned char), row_padded, file);
        for(int j = 0; j < width*3; j += 3) {
            std::swap(data[j], data[j+2]);
            // Convert weird (B, G, R) format to (R, G, B)

        }
    }

    fclose(file);

    return data;

}


int main() {
    char const* filepath = "/Users/davi9091/LAND.BMP";
    // This image is 1024x768
    unsigned char* bmpdata;

    int yuv_width = 352;
    int yuv_heigth = 288;
    int yuv_frames = 150;

    imageBMP bmp(filepath);

    bmpdata = bmp.getData();
    int bmpwidth = bmp.getWidth();

    std::cout << bmpdata << '\n';

    return 0;
}