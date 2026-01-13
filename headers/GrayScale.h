#pragma once
#include <iostream>
#include <string>

using namespace std;

class Gray_Scale_Image
{
protected:
    int channels;
    int width;
    int height;
    int maxValue;
    unsigned char *pixels;
    bool isLoaded = false;

public:
    Gray_Scale_Image(int ch = 1);
    virtual ~Gray_Scale_Image();
    virtual void read(const string &filename, const string &mode);
    virtual void write(const string &filename, const string &mode) const;
    int getWidth() const;
    int getHeight() const;
    int getMaxValue() const;
    bool getIsLoaded() const;
    
    void invert();
    void resize(int newW, int newH);
    void brighten(int amount);
    void darken(int amount);
    void flip_horizontal();
    void flip_vertical();
    void rotate_clockwise();
    virtual void convert_to_grayscale();
    void auto_contrast();
    void blur();
    void sharpen();
    void merge(Gray_Scale_Image &other, bool horizontal);
    void add_border(int borderSize, int color);
    void crop(int x, int y, int w, int h);
    void threshold(int t);
    void posterize(int levels);
};