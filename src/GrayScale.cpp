#include "GrayScale.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
#include "global.h"

using namespace std;
Gray_Scale_Image::Gray_Scale_Image(int ch) : channels(ch), width(0), height(0), maxValue(255), pixels(nullptr), isLoaded(false) {}
Gray_Scale_Image::~Gray_Scale_Image()
{
    delete[] pixels;
    pixels = nullptr;
}

void Gray_Scale_Image::read(const string &filename, const string &mode)
{
    ifstream file(filename, mode == "binary" ? ios::binary : ios::in);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string magic;
    file >> magic;
    if (magic != (mode == "text" ? "P2" : "P5"))
    {
        cout << "Invalid PGM format!" << endl;
        return;
    }
    skip_comments(file);
    file >> width >> height;
    skip_comments(file);
    file >> maxValue;
    skip_comments(file);
    delete[] pixels;
    pixels = new unsigned char[width * height * channels];
    if (mode == "text")
    {
        for (int i = 0; i < width * height * channels; ++i)
        {
            int val;
            file >> val;
            pixels[i] = static_cast<unsigned char>(val);
        }
    }
    else
    {
        file.read(reinterpret_cast<char *>(pixels), width * height * channels);
        cout<<"File Read Successfully"<<endl;
    }
    file.close();
}
void Gray_Scale_Image::write(const string &filename, const string &mode) const
{
    ofstream file(filename, mode == "binary" ? ios::binary : ios::out);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string magic = (mode == "text" ? "P2" : "P5");
    file << magic << endl;
    file << width << " " << height << endl;
    file << maxValue << endl;
    int size = width * height * channels;
    if (mode == "text")
    {
        for (int i = 0; i < size; ++i)
        {
            file << static_cast<int>(pixels[i]) << " ";
        }
    }
    else
    {
        file.write(reinterpret_cast<const char *>(pixels), size);
    }
    file.close();
} 

int Gray_Scale_Image::getWidth() const
{
    return width;
}
int Gray_Scale_Image::getHeight() const
{
    return height;
}
int Gray_Scale_Image::getMaxValue() const
{
    return maxValue;
}

bool Gray_Scale_Image::getIsLoaded() const
{
    return isLoaded;
}

void Gray_Scale_Image::invert()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int size = width * height * channels;
    for (int i = 0; i < size; i++)
        pixels[i] = maxValue - pixels[i];
        
    isLoaded = true;
}
void Gray_Scale_Image::brighten(int amount)
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int size = width * height * channels;
    for (int i = 0; i < size; i++)
        pixels[i] = min(maxValue, (int)pixels[i] + amount);
    
    isLoaded = true;
}
void Gray_Scale_Image::darken(int amount)
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int size = width * height * channels;
    for (int i = 0; i < size; i++)
        pixels[i] = max(0, (int)pixels[i] - amount);
    isLoaded = true;
}
void Gray_Scale_Image::flip_horizontal()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int left = (y * width + x) * channels + c;
                int right = (y * width + (width - 1 - x)) * channels + c;
                swap(pixels[left], pixels[right]);
            }
        }
    }
    isLoaded = true;
}
void Gray_Scale_Image::flip_vertical()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height / 2; y++)
        {
            for (int c = 0; c < channels; c++)
            {
                int top = (y * width + x) * channels + c;
                int bottom = ((height - 1 - y) * width + x) * channels + c;
                swap(pixels[top], pixels[bottom]);
            }
        }
    }
    isLoaded = true;
}
void Gray_Scale_Image::rotate_clockwise()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int newW = height;
    int newH = width;
    unsigned char *newPixels = new unsigned char[newW * newH * channels];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int oldIndex = (y * width + x) * channels + c;
                int newIndex = (x * newW + (newW - 1 - y)) * channels + c;
                newPixels[newIndex] = pixels[oldIndex];
            }
        }
    }
    delete[] pixels;
    pixels = newPixels;
    width = newW;
    height = newH;
    isLoaded = true;
}
void Gray_Scale_Image::convert_to_grayscale()
{
    cout << "Already grayscale!" << endl;
    isLoaded = false;
    return;
}
void Gray_Scale_Image::auto_contrast()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int size = width * height * channels;
    int minVal = 255, maxVal = 0;
    for (int i = 0; i < size; i++)
    {
        minVal = min(minVal, (int)pixels[i]);
        maxVal = max(maxVal, (int)pixels[i]);
    }
    float scale = 255.0f / (maxVal - minVal + 1);
    for (int i = 0; i < size; i++)
    {
        pixels[i] = (pixels[i] - minVal) * scale;
    }
    isLoaded = true;
}
void Gray_Scale_Image::blur()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int W = width;
    int H = height;
    int size = W * H * channels;
    unsigned char *out = new unsigned char[size];
    int karr[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int y = 1; y < H - 1; y++)
    {
        for (int x = 1; x < W - 1; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int sum = 0, k = 0;
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        int idx = ((y + dy) * W + (x + dx)) * channels + c;
                        sum += pixels[idx] * karr[k++];
                    }
                }
                out[(y * W + x) * channels + c] = sum / 9;
            }
        }
    }
    delete[] pixels;
    pixels = out;
    isLoaded = true;
}
void Gray_Scale_Image::sharpen()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int W = width;
    int H = height;
    unsigned char *out = new unsigned char[W * H * channels];
    int karr[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    for (int y = 1; y < H - 1; y++)
    {
        for (int x = 1; x < W - 1; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int sum = 0, k = 0;
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        int idx = ((y + dy) * W + (x + dx)) * channels + c;
                        sum += pixels[idx] * karr[k++];
                    }
                }
                sum = max(0, min(255, sum));
                out[(y * W + x) * channels + c] = sum;
            }
        }
    }
    isLoaded = true;
    delete[] pixels;
    pixels = out;
}
void Gray_Scale_Image::merge(Gray_Scale_Image &other, bool horizontal)
{
    if ((pixels == nullptr) || (other.pixels == nullptr))
    {
        cout << "No Operations can be performed , First Read Image!";
        isLoaded = false;
        return;
    }
    int newW = horizontal ? width + other.width : max(width, other.width);
    int newH = horizontal ? max(height, other.height) : height + other.height;
    unsigned char *newPixels = new unsigned char[newW * newH * channels];
    for (int i = 0; i < newW * newH * channels; i++)
    {
        newPixels[i] = 0;
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int newIndex = (y * newW + x) * channels + c;
                int oldIndex = (y * width + x) * channels + c;
                newPixels[newIndex] = pixels[oldIndex];
            }
        }
    }
    for (int y = 0; y < other.height; y++)
    {
        for (int x = 0; x < other.width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int nx = horizontal ? width + x : x;
                int ny = horizontal ? y : height + y;
                int newIndex = (ny * newW + nx) * channels + c;
                int oldIndex = (y * other.width + x) * channels + c;
                newPixels[newIndex] = other.pixels[oldIndex];
            }
        }
    }
    delete[] pixels;
    pixels = newPixels;
    width = newW;
    height = newH;
    isLoaded = true;
}
void Gray_Scale_Image::add_border(int borderSize, int color)
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    int newW = width + borderSize * 2;
    int newH = height + borderSize * 2;
    unsigned char *newPixels = new unsigned char[newW * newH * channels];
    for (int i = 0; i < newW * newH * channels; i++)
        newPixels[i] = color;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            for (int c = 0; c < channels; c++)
            {
                int newIndex = ((y + borderSize) * newW + (x + borderSize)) * channels + c;
                int oldIndex = (y * width + x) * channels + c;
                newPixels[newIndex] = pixels[oldIndex];
            }
    delete[] pixels;
    pixels = newPixels;
    width = newW;
    height = newH;
    isLoaded = true;
}
void Gray_Scale_Image::crop(int x, int y, int w, int h)
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= width || y >= height)
    {
        cout << "\033[31mError: Crop coordinates outside image dimensions!\033[0m\n";
        return;
    }
    if (x + w > width)
        w = width - x;
    if (y + h > height)
        h = height - y;
    unsigned char *newPixels = new unsigned char[w * h * channels];
    for (int cy = 0; cy < h; cy++)
        for (int cx = 0; cx < w; cx++)
            for (int c = 0; c < channels; c++)
            {
                int oldIndex = ((y + cy) * width + (x + cx)) * channels + c;
                int newIndex = (cy * w + cx) * channels + c;
                newPixels[newIndex] = pixels[oldIndex];
            }
    delete[] pixels;
    pixels = newPixels;
    width = w;
    height = h;
    isLoaded = true;
}
void Gray_Scale_Image::resize(int newW, int newH)
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    unsigned char *newPixels = new unsigned char[newW * newH * channels];
    float xRatio = (float)width / newW;
    float yRatio = (float)height / newH;
    for (int y = 0; y < newH; y++)
    {
        for (int x = 0; x < newW; x++)
        {
            int oldX = x * xRatio;
            int oldY = y * yRatio;
            for (int c = 0; c < channels; c++)
            {
                newPixels[(y * newW + x) * channels + c] =
                    pixels[(oldY * width + oldX) * channels + c];
            }
        }
    }
    delete[] pixels;
    pixels = newPixels;
    width = newW;
    height = newH;
    isLoaded = true;
}
void Gray_Scale_Image::threshold(int t)
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    if (t < 0)
        t = 0;
    if (t > 255)
        t = 255;
    int size = width * height * channels;
    for (int i = 0; i < size; i++)
        pixels[i] = (pixels[i] < t) ? 0 : 255;
    isLoaded = true;
}
void Gray_Scale_Image::posterize(int levels)
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    if (levels < 2)
        levels = 2;
    if (levels > 255)
        levels = 255;
    int size = width * height * channels;
    float step = 255.0f / (levels - 1);
    for (int i = 0; i < size; i++)
    {
        int val = pixels[i];
        int newVal = int((val / step) + 0.5f) * step;
        if (newVal < 0)
            newVal = 0;
        if (newVal > 255)
            newVal = 255;
        pixels[i] = newVal;
    }
    isLoaded = true;
}