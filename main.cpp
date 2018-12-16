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
#include "yuv420.h"


int main() {
    char const* bmppath = "/Users/davi9091/TRU256.BMP";

    char const* yuvpath = "/Users/davi9091/BUS.YUV";

    int yuv_width = 352;
    int yuv_height = 288;
    int yuv_frames = 150;

    imageBMP bmp(bmppath);
    YUVI420 yuv(yuvpath, yuv_width, yuv_height, yuv_frames);

    yuv.addRGB(bmp.getRData(), bmp.getGData(), bmp.getBData(), bmp.getWidth(), bmp.getHeight());

    yuv.writeToFile("/Users/davi9091/fuckup.YUV");

    return 0;
}