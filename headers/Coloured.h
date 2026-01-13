#pragma once
#include "GrayScale.h"
#include <string>
#include <iostream>

using namespace std;

class Coloured : public Gray_Scale_Image
{
public:
    Coloured();
    void read(const string &filename, const string &mode) override;
    void write(const string &filename, const string &mode) const override;
    void convert_to_grayscale() override;
};