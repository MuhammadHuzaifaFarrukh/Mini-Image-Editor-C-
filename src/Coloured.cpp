#include "Coloured.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "global.h"

using namespace std;
Coloured::Coloured() : Gray_Scale_Image(3) {}
void Coloured::read(const string &filename, const string &mode)
{
    ifstream file(filename, mode == "binary" ? ios::binary : ios::in);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string magic;
    file >> magic;
    if (magic != (mode == "text" ? "P3" : "P6"))
    {
        cout << "Invalid PPM format!" << endl;
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
void Coloured::write(const string &filename, const string &mode) const
{
    ofstream file(filename, mode == "binary" ? ios::binary : ios::out);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string magic = (mode == "text" ? "P3" : "P6");
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
void Coloured::convert_to_grayscale()
{
    if (pixels == nullptr)
    {
        cout << "No Operations can be performed, First Read Image!";
        isLoaded = false;
        return;
    }
    unsigned char *newPixels = new unsigned char[width * height];
    for (int i = 0; i < width * height; i++)
    {
        int r = pixels[i * 3];
        int g = pixels[i * 3 + 1];
        int b = pixels[i * 3 + 2];
        newPixels[i] = (0.299 * r + 0.587 * g + 0.114 * b);
    }
    delete[] pixels;
    pixels = newPixels;
    channels = 1;
    isLoaded = true;
}