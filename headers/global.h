#pragma once
#include <iostream>
#include <string>
#include "GrayScale.h"
using namespace std;

// ----------------------- MENU -----------------------
void display_menu();
void ppm_operations(const string &mode);
void pgm_operations(const string &mode);
// Helper
string getValidFilename();
void ask_save_image(Gray_Scale_Image &img, const string &mode);
int getPositiveInt();
void skip_comments(ifstream &file);