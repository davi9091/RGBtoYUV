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

unsigned char* readBMP(char* filename) {

    FILE* file = fopen(filename, "rb");

    if (file == std::nullptr_t)
        throw "File is NULL";
    // Make sure we open something

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file);
    // BMP consists of 54-byte header: 14-byte BITMAPFILEHEADER and 40-byte BITMAPINFO

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    // Take width and height of the image

    int row_padded = (width*3 + 3) & (~3);
    auto* data = new unsigned char[row_padded];

    for(int i = 0; i < height; ++i) {
        fread(int j = 0; j < width*3; j += 3) {
            swap(data[j], data[j+2]);
            // Convert weird (B, G, R) format to (R, G, B)
        }
    }

    fclose(file);

    return data;

}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}