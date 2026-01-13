#pragma once

// PGM means Portable Gray Map image (Black and White Image)
// PPM means Portable Pixel Map Image (Coloured Image)

struct Image
{
    int width;
    int height;
    int maxValue;
    unsigned char *pixels; // Holds PPM (RGB*3) OR PGM (1 channel only)
};
