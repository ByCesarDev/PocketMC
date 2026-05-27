#include "PngLoader.h"

#include <png.h>
#include <cstring>

struct MemoryReader {
    const unsigned char* data;
    size_t size;
    size_t pos;
};

static void pngMemoryRead(png_structp pngPtr, png_bytep outBytes, png_size_t byteCountToRead) {
#ifndef STANDALONE_SERVER
    MemoryReader* reader = (MemoryReader*)png_get_io_ptr(pngPtr);
    if (!reader)
        return;

    if (reader->pos + byteCountToRead > reader->size) {
        png_error(pngPtr, "Read past end of buffer");
        return;
    }

    memcpy(outBytes, reader->data + reader->pos, byteCountToRead);
    reader->pos += byteCountToRead;
#endif
}

TextureData loadPngFromMemory(const unsigned char* data, size_t size) {
    TextureData out;
#ifndef STANDALONE_SERVER
    if (!data || size == 0) return out;

    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr) return out;

    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) {
        png_destroy_read_struct(&pngPtr, NULL, NULL);
        return out;
    }

    png_bytep* rowPtrs = NULL;
    unsigned char* pixels = NULL;

    if (setjmp(png_jmpbuf(pngPtr))) {
        if (rowPtrs) {
            delete[] rowPtrs;
            rowPtrs = NULL;
        }
        if (pixels) {
            delete[] pixels;
            pixels = NULL;
        }
        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
        return TextureData();
    }

    MemoryReader reader;
    reader.data = data;
    reader.size = size;
    reader.pos = 0;

    png_set_read_fn(pngPtr, &reader, pngMemoryRead);
    png_read_info(pngPtr, infoPtr);

    png_uint_32 width = 0;
    png_uint_32 height = 0;
    int bitDepth = 0;
    int colorType = 0;
    int interlaceType = 0;
    int compressionType = 0;
    int filterType = 0;
    png_get_IHDR(pngPtr, infoPtr, &width, &height, &bitDepth, &colorType,
                 &interlaceType, &compressionType, &filterType);

    // Convert any color type to 8-bit RGBA
    if (colorType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(pngPtr);
    if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
        png_set_expand_gray_1_2_4_to_8(pngPtr);

    bool hasAlpha = (colorType == PNG_COLOR_TYPE_GRAY_ALPHA || colorType == PNG_COLOR_TYPE_RGBA);
    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(pngPtr);
    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
        hasAlpha = true;
    if (bitDepth == 16)
        png_set_strip_16(pngPtr);

    // Ensure we always have RGBA (4 bytes per pixel)
    if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(pngPtr);
    if (!hasAlpha)
        png_set_filler(pngPtr, 0xFF, PNG_FILLER_AFTER);

    // Handle interlaced PNGs properly
    png_set_interlace_handling(pngPtr);

    png_read_update_info(pngPtr, infoPtr);

    png_size_t rowBytes = png_get_rowbytes(pngPtr, infoPtr);
    if (rowBytes == 0 || width == 0 || height == 0)
        png_error(pngPtr, "internal row size calculation error");

    pixels = new unsigned char[rowBytes * height];
    rowPtrs = new png_bytep[height];
    for (png_uint_32 i = 0; i < height; ++i) {
        rowPtrs[i] = (png_bytep)(pixels + i * rowBytes);
    }

    png_read_image(pngPtr, rowPtrs);
    png_read_end(pngPtr, NULL);

    delete[] rowPtrs;
    rowPtrs = NULL;

    png_destroy_read_struct(&pngPtr, &infoPtr, NULL);

    // Guarantee 4-bytes-per-pixel output for the rendering pipeline.
    const size_t expectedRowBytes = (size_t)width * 4;
    if (rowBytes != expectedRowBytes) {
        unsigned char* repacked = new unsigned char[expectedRowBytes * height];
        for (png_uint_32 y = 0; y < height; ++y) {
            unsigned char* dst = repacked + y * expectedRowBytes;
            unsigned char* src = pixels + y * rowBytes;
            if (rowBytes == (size_t)width * 3) {
                for (png_uint_32 x = 0; x < width; ++x) {
                    dst[x * 4 + 0] = src[x * 3 + 0];
                    dst[x * 4 + 1] = src[x * 3 + 1];
                    dst[x * 4 + 2] = src[x * 3 + 2];
                    dst[x * 4 + 3] = 0xFF;
                }
            } else {
                size_t copy = rowBytes < expectedRowBytes ? rowBytes : expectedRowBytes;
                memcpy(dst, src, copy);
                if (copy < expectedRowBytes) {
                    memset(dst + copy, 0xFF, expectedRowBytes - copy);
                }
            }
        }
        delete[] pixels;
        pixels = repacked;
        rowBytes = expectedRowBytes;
    }

    out.w = (int)width;
    out.h = (int)height;
    out.data = pixels;
    out.memoryHandledExternally = false;
    out.transparent = true;
    out.format = TEXF_UNCOMPRESSED_8888;
#endif

    return out;
}
