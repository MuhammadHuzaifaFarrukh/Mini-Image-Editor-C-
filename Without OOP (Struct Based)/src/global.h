#pragma once
#include <string>
#include "Image.h"
#include <limits>
#include <fstream>
using namespace std;

// Menu
void display_menu();
void ppm_operations(Image &img, const std::string &mode);
void pgm_operations(Image &img, const std::string &mode);

// Memory
void allocate_pixels(Image &img, int size);
void free_pixels(Image &img);

// File I/O
void skip_comments(ifstream &file);
void read_ppm(Image &img, const std::string &filename, const std::string &mode);
void read_pgm(Image &img, const std::string &filename, const std::string &mode);
void write_ppm(const Image &img, const std::string &filename, const std::string &mode);
void write_pgm(const Image &img, const std::string &filename, const std::string &mode);
void ask_save_image(Image &img, const std::string &mode, bool isPPM);

// Processing
void invert_ppm_colors(Image &img);
void invert_pgm_grayscale(Image &img);
void brighten_image(Image &img, int amount, bool isPPM);
void darken_image(Image &img, int amount, bool isPPM);
void flip_horizontal(Image &img, bool isPPM);
void flip_vertical(Image &img, bool isPPM);
void rotate_clockwise(Image &img, bool isPPM);
void convert_to_grayscale(Image &img);
void auto_contrast(Image &img, bool isPPM);
void blur_image(Image &img, bool isPPM);
void sharpen_image(Image &img, bool isPPM);
void merge_images(Image &img1, Image &img2, bool horizontal, bool isPPM);
void add_border(Image &img, int borderSize, int color, bool isPPM);
void crop_image(Image &img, int x, int y, int w, int h, bool isPPM);
void resize_image(Image &img, int newW, int newH, bool isPPM);
void posterize(Image &img, int levels, bool isPPM);
void threshold(Image &img, int thresholdValue, bool isPPM);
