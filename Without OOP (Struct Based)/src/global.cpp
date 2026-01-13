#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "global.h"

using namespace std;

// ANSI Colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"

// ----------------------- MENU -----------------------
void display_menu()
{
    cout << BOLD << MAGENTA << "\n=== MINI IMAGE EDITOR ===\n"
         << RESET;
    cout << YELLOW << "1. PPM Operations\n"
         << RESET;
    cout << YELLOW << "2. PGM Operations\n"
         << RESET;
    cout << RED << "3. Exit\n"
         << RESET;
    cout << BOLD << CYAN << "Select operation: " << RESET;
}

// for ask_save_image

string getValidFilename()
{
    string filename;

    while (true)
    {
        cout << "Enter filename : ";
        cin >> filename;

        int n = filename.length();

        if (n >= 4)
        {

            char c1 = filename[n - 4];
            char c2 = filename[n - 3];
            char c3 = filename[n - 2];
            char c4 = filename[n - 1];

            // Check for ".pgm"
            if (c1 == '.' && c2 == 'p' && c3 == 'g' && c4 == 'm')
            {
                return filename;
            }

            // Check for ".ppm
            if (c1 == '.' && c2 == 'p' && c3 == 'p' && c4 == 'm')
            {
                return filename;
            }
        }

        cout << "Invalid! Filename must end with .pgm or .ppm.\n";
    }
}
// Helper function to ask user to save modified image
void ask_save_image(Image &img, const string &mode, bool isPPM)
{
    char save;
    cout << "Do you want to save the modified image? (y/n): ";
    cin >> save;

    if (save == 'y' || save == 'Y')
    {
        string filename;
        filename = getValidFilename();

        if (isPPM)
            write_ppm(img, filename, mode);
        else
            write_pgm(img, filename, mode);
    }
}

// get positive integer

int getPositiveInt()
{
    int num;

    while (true)
    {
        cout << "Enter a positive integer: ";
        cin >> num;

        if (!cin.fail() && num > 0)
        {
            return num;
        }

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid! Please enter a positive integer only.\n";
    }
}

// ----------------------- MEMORY -----------------------
void allocate_pixels(Image &img, int size)
{
    
    img.pixels = new unsigned char[size]; // FIXED: int → unsigned char
}

void free_pixels(Image &img)
{
    delete[] img.pixels;
    img.pixels = nullptr;
}

// ----------------------- PPM MENU -----------------------
void ppm_operations(Image &img, const string &mode)
{
    int c;
    do
    {
        cout << BOLD << MAGENTA << "\n--- PPM MENU ---\n"
             << RESET;
        cout << BOLD << MAGENTA << "\n--- READ IMAGE BEFORE DOING ANY OPERATION ! ---\n"
             << RESET;
        cout << YELLOW << "1. Read PPM\n"
             << RESET;
        cout << YELLOW << "2. Write PPM\n"
             << RESET;
        cout << CYAN << "3. Invert Colors\n4. Resize (Stretch / Compress)\n"
             << RESET;
        cout << CYAN << "5. Brighten\n6. Darken\n7. Flip Horizontal\n8. Flip Vertical\n"
             << RESET;
        cout << CYAN << "9. Rotate Clockwise\n10. Grayscale (PPM->PGM)\n11. Auto Contrast\n"
             << RESET;
        cout << CYAN << "12. Blur\n13. Sharpen\n14. Merge Image\n15. Add Border / Frame\n16. Crop Region\n17. Threshold Image\n18. Posterize Image\n"
             << RESET;
        cout << RED << "19. Back to Main Menu\n"
             << RESET;
        cout << BOLD << CYAN << "Select operation: " << RESET;
        cin >> c;

        switch (c)
        {
        case 1:
        {
            string fname;
            cout << YELLOW << "Enter PPM file name: " << RESET;
            fname = getValidFilename();
            while (true)
            {
                int length = fname.length();
                if (length >= 4)
                {
                    char d = fname[length - 1];
                    char c = fname[length - 2];
                    char b = fname[length - 3];
                    char a = fname[length - 4];

                    if (a == '.' && b == 'p' && c == 'p' && d == 'm')
                    {
                        break;
                    }
                    
                }
                
                fname = getValidFilename();
            }
            read_ppm(img, fname, mode);
            break;
        }
        case 2:
        {
            string fname;
            cout << YELLOW << "Enter output file name: " << RESET;
            fname = getValidFilename();
            while (true)
            {
                int length = fname.length();
                if (length >= 4)
                {
                    char d = fname[length - 1];
                    char c = fname[length - 2];
                    char b = fname[length - 3];
                    char a = fname[length - 4];
                    if (a == '.' && b == 'p' && c == 'p' && d == 'm')
                    {
                        break;
                    }
                   
                }
                 fname = getValidFilename();
            }
            write_ppm(img, fname, mode);
            break;
        }
        case 3:
        
            invert_ppm_colors(img);
            ask_save_image(img, mode, true);
            break;
        case 4:
        {
            int newW, newH;
            cout << YELLOW << "Enter new width and height: " << RESET;
            newW = getPositiveInt();
            newH = getPositiveInt();
            resize_image(img, newW, newH, true);
            ask_save_image(img, mode, true);
            break;
        }
        case 5:
        {
            int amt;
            cout << YELLOW << "Enter brightness amount: " << RESET;
            amt = getPositiveInt();
            brighten_image(img, amt, true);
            ask_save_image(img, mode, true);
            break;
        }
        case 6:
        {
            int amt;
            cout << YELLOW << "Enter darken amount: " << RESET;
            amt = getPositiveInt();
            darken_image(img, amt, true);
            ask_save_image(img, mode, true);
            break;
        }
        case 7:
            flip_horizontal(img, true);
            ask_save_image(img, mode, true);
            break;
        case 8:
            flip_vertical(img, true);
            ask_save_image(img, mode, true);
            break;
        case 9:
            rotate_clockwise(img, true);
            ask_save_image(img, mode, true);
            break;
        case 10:
            convert_to_grayscale(img);
            ask_save_image(img, mode, false);
            break;
        case 11:
            auto_contrast(img, true);
            ask_save_image(img, mode, true);
            break;
        case 12:
            blur_image(img, true);
            ask_save_image(img, mode, true);
            break;
        case 13:
            sharpen_image(img, true);
            ask_save_image(img, mode, true);
            break;
        case 14:
        {
            Image img2 = {0, 0, 255, nullptr};
            string fname;
            cout << YELLOW << "Enter file to merge: " << RESET;
            fname=getValidFilename();
              while (true)
            {
                int length = fname.length();
                if (length >= 4)
                {
                    char d = fname[length - 1];
                    char c = fname[length - 2];
                    char b = fname[length - 3];
                    char a = fname[length - 4];

                    if (a == '.' && b == 'p' && c == 'p' && d == 'm')
                    {
                        break;
                    }
                   
                }
                 fname = getValidFilename();
            }
            read_ppm(img2, fname, mode);
            merge_images(img, img2, true, true);
            ask_save_image(img, mode, true);
            free_pixels(img2);
            break;
        }
        case 15:
        {
            int size, color;
            cout << YELLOW << "Enter border size: " << RESET;
            size = getPositiveInt();
            cout << YELLOW << "Enter border color (0-" << img.maxValue << "): " << RESET;
            color = getPositiveInt();
            add_border(img, size, color, true);
            ask_save_image(img, mode, true);
            break;
        }
        case 16:
        {
            int x, y, w, h;
            cout << YELLOW << "Enter crop x , y , width and height one by one : " << RESET;
            x = getPositiveInt();
            y = getPositiveInt();
            w = getPositiveInt();
            h = getPositiveInt();
            crop_image(img, x, y, w, h, true);
            ask_save_image(img, mode, true);
            break;
        }
        case 17:
        {
            int val;
            cout << "Enter threshold value : (0-255) : ";
            while (true)
            {
                val = getPositiveInt();
                if (val < 255)
                {
                    break;
                }
            }

            threshold(img, val, true);
            ask_save_image(img, mode, true);
            break;
        }
        case 18:
        {
            int levels;
            cout << "Enter levels of Posterization (2-255) : ";
            while (true)
            {
                levels = getPositiveInt();
                if (levels >= 2 && levels <= 255)
                {
                    break;
                }
            }

            posterize(img, levels, true);
            ask_save_image(img, mode, true);
            break;
        }
        case 19:
            cout << GREEN << "Returning to main menu...\n"
                 << RESET;
            break;
        default:
            cout << RED << "Invalid choice!\n"
                 << RESET;
        }
    } while (c != 19);
}

void skip_comments(ifstream &file)
{
    char ch;
    file >> ws;
    while (file.peek() == '#')
        file.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ----------------------- PGM MENU -----------------------
void pgm_operations(Image &img, const string &mode)
{
    int c;
    do
    {
        cout << BOLD << MAGENTA << "\n--- PGM MENU ---\n"
             << RESET;
        cout << YELLOW << "1. Read PGM\n2. Write PGM\n"
             << RESET;
        cout << CYAN << "3. Invert Grayscale\n4. Resize\n5. Brighten\n6. Darken\n"
             << RESET;
        cout << CYAN << "7. Flip Horizontal\n8. Flip Vertical\n9. Rotate Clockwise\n10. Auto Contrast\n"
             << RESET;
        cout << CYAN << "11. Blur\n12. Sharpen\n13. Merge Image\n14. Add Border\n15. Crop\n16. Threshold Image\n17. Posterize Image\n"
             << RESET;
        cout << RED << "18. Back to Main Menu\n"
             << RESET;
        cout << BOLD << CYAN << "Select operation: " << RESET;
        cin >> c;

        switch (c)
        {
        case 1:
        {
            string fname;
            cout << YELLOW << "Enter PGM filename: " << RESET;
            fname = getValidFilename();
            while (true)
            {
                int length = fname.length();
                if (length >= 4)
                {
                    char d = fname[length - 1];
                    char c = fname[length - 2];
                    char b = fname[length - 3];
                    char a = fname[length - 4];

                    if (a == '.' && b == 'p' && c == 'g' && d == 'm')
                    {
                        break;
                    }
                    
                }
                fname = getValidFilename();
            }

            read_pgm(img, fname, mode);
            break;
        }
        case 2:
        {
            string fname;
            cout << YELLOW << "Enter output file: " << RESET;
            fname = getValidFilename();
            while (true)
            {
                int length = fname.length();
                if (length >= 4)
                {
                    char d = fname[length - 1];
                    char c = fname[length - 2];
                    char b = fname[length - 3];
                    char a = fname[length - 4];

                    if (a == '.' && b == 'p' && c == 'g' && d == 'm')
                    {
                        break;
                    }
                   
                }
                 fname = getValidFilename();
            }
            write_pgm(img, fname, mode);
            break;
        }
        case 3:
            invert_pgm_grayscale(img);
            ask_save_image(img, mode, false);
            break;
        case 4:
        {
            int newW, newH;
            cout << YELLOW << "Enter new width & height: " << RESET;
            newW = getPositiveInt();
            newH = getPositiveInt();
            resize_image(img, newW, newH, false);
            ask_save_image(img, mode, false);
            break;
        }
        case 5:
        {
            int amt;
            cout << YELLOW << "Brighten amount: " << RESET;
            amt = getPositiveInt();
            brighten_image(img, amt, false);
            ask_save_image(img, mode, false);
            break;
        }
        case 6:
        {
            int amt;
            cout << YELLOW << "Darken amount: " << RESET;
            amt = getPositiveInt();
            darken_image(img, amt, false);
            ask_save_image(img, mode, false);
            break;
        }
        case 7:
            flip_horizontal(img, false);
            ask_save_image(img, mode, false);
            break;
        case 8:
            flip_vertical(img, false);
            ask_save_image(img, mode, false);
            break;
        case 9:
            rotate_clockwise(img, false);
            ask_save_image(img, mode, false);
            break;
        case 10:
            auto_contrast(img, false);
            ask_save_image(img, mode, false);
            break;
        case 11:
            blur_image(img, false);
            ask_save_image(img, mode, false);
            break;
        case 12:
            sharpen_image(img, false);
            ask_save_image(img, mode, false);
            break;
        case 13:
        {
            Image img2 = {0, 0, 255, nullptr};
            string fname;
            cout << YELLOW << "Enter second image: " << RESET;
            
             fname = getValidFilename();
            while (true)
            {
                int length = fname.length();
                if (length >= 4)
                {
                    char d = fname[length - 1];
                    char c = fname[length - 2];
                    char b = fname[length - 3];
                    char a = fname[length - 4];

                    if (a == '.' && b == 'p' && c == 'g' && d == 'm')
                    {
                        break;
                    }
                    
                }
                fname = getValidFilename();
            }

            read_pgm(img2, fname, mode);
            merge_images(img, img2, true, false); // horizontal
            free_pixels(img2);
            ask_save_image(img, mode, false);
            break;
        }
        case 14:
        {
            int size, color;
            cout << YELLOW << "Border size: " << RESET;
            size=getPositiveInt();
            cout << YELLOW << "Border color: " << RESET;
            color=getPositiveInt();
            add_border(img, size, color, false);
            ask_save_image(img, mode, false);
            break;
        }
        case 15:
        {
            int x, y, w, h;
            cout << YELLOW << "Enter crop x , y , width and height one by one :" << RESET;
            x=getPositiveInt();
            y=getPositiveInt();
            w=getPositiveInt();
            h=getPositiveInt();
            crop_image(img, x, y, w, h, false);
            ask_save_image(img, mode, false);
            break;
        }
        case 16:
        {
            int val;
            cout << "Enter threshold value : (0-255) : ";
            val=getPositiveInt();
            threshold(img, val, false);
            ask_save_image(img, mode, false);
            break;
        }
        case 17:
        {
            int levels;
            cout << "Enter levels of Posterization (2-255) : ";
            levels=getPositiveInt();

            posterize(img, levels, false);
            ask_save_image(img, mode, false);
            break;
        }
        case 18:
            cout << GREEN << "Returning to main menu...\n"
                 << RESET;
            break;
        }

    } while (c != 18);
}

// ----------------------- PPM/PGM READ -----------------------
void read_pgm(Image &img, const string &filename, const string &mode)
{
    ifstream file;

    if (mode == "binary")
        file.open(filename, ios::binary);
    else
        file.open(filename);

    if (!file.is_open())
    {
        cout << "Error: Could not open file!\n";
        return;
    }

    string magic;
    file >> magic;

    if (magic != "P2" && magic != "P5")
    {
        cout << "Error: Not a valid PGM file!\n";
        return;
    }


    skip_comments(file);
    file >> img.width;

    skip_comments(file);
    file >> img.height;

    skip_comments(file);
    file >> img.maxValue;

    file.ignore(); // skip newline

    int total = img.width * img.height;

    if (img.pixels)
        delete[] img.pixels;
    img.pixels = new unsigned char[total];

    if (magic == "P2") // TEXT
    {
        for (int i = 0; i < total; i++)
        {
            int val;
            file >> val;
            img.pixels[i] = (unsigned char)val;
            if (!file.good())
            {
                cout << "Error reading P2 pixel data!\n";
                break;
            }
        }
    }
    else if (magic == "P5") // BINARY
    {
        file.read(reinterpret_cast<char *>(img.pixels), total);
        if (!file.good())
        {
            cout << "Error reading P5 pixel data!\n";
            return;
        }
    }

    file.close();
    cout << "PGM Loaded Successfully!\n";
}

void read_ppm(Image &img, const string &filename, const string &mode)
{
    ifstream file;

    if (mode == "binary")
        file.open(filename, ios::binary);
    else
        file.open(filename);

    if (!file.is_open())
    {
        cout << "Error: Could not open file!\n";
        return;
    }

    string magic;
    file >> magic;

    if (magic != "P3" && magic != "P6")
    {
        cout << "Error: Not a valid PPM file!\n";
        return;
    }

    skip_comments(file);
    file >> img.width;

    skip_comments(file);
    file >> img.height;

    skip_comments(file);
    file >> img.maxValue;

    file.ignore(); // remove 1 byte newline

    int channels = 3;
    int total = img.width * img.height * channels;

    if (img.pixels)
        delete[] img.pixels;
    img.pixels = new unsigned char[total];

    if (magic == "P3") // TEXT MODE
    {
        for (int i = 0; i < total; i++)
        {
            int val;
            file >> val;
            img.pixels[i] = (unsigned char)val;

            if (!file.good())
            {
                cout << "Error reading P3 pixel data!\n";
                break;
            }
        }
    }
    else if (magic == "P6") // BINARY MODE
    {
        file.read(reinterpret_cast<char *>(img.pixels), total);

        if (!file.good())
        {
            cout << "Error reading P6 pixel data!\n";
            return;
        }
    }

    file.close();
    cout << "PPM Loaded Successfully!\n";
}

// ----------------------- PPM/PGM WRITE -----------------------
void write_ppm(const Image &img, const string &filename, const string &mode)
{
    ofstream file;

    if (mode == "binary")
        file.open(filename, ios::binary);
    else
        file.open(filename);

    if (mode == "binary")
    {
        file << "P6\n"
             << img.width << " " << img.height << "\n"
             << img.maxValue << "\n";

        file.write((char *)img.pixels, img.width * img.height * 3);
    }
    else
    {
        file << "P3\n"
             << img.width << " " << img.height << "\n"
             << img.maxValue << "\n";

        for (int i = 0; i < img.width * img.height * 3; i++)
        {
            file << (int)img.pixels[i] << " ";
            if ((i + 1) % 3 == 0)
                file << "\n";
        }
    }

    cout << GREEN << "PPM written successfully!\n"
         << RESET;
}

void write_pgm(const Image &img, const string &filename, const string &mode)
{
    ofstream file;

    if (mode == "binary")
        file.open(filename, ios::binary);
    else
        file.open(filename);

    if (mode == "binary")
    {
        file << "P5\n"
             << img.width << " " << img.height << "\n"
             << img.maxValue << "\n";
        file.write((char *)img.pixels, img.width * img.height);
    }
    else
    {
        file << "P2\n"
             << img.width << " " << img.height << "\n"
             << img.maxValue << "\n";

        for (int i = 0; i < img.width * img.height; i++)
        {
            file << (int)img.pixels[i] << " ";
            if ((i + 1) % img.width == 0)
                file << "\n";
        }
    }

    cout << GREEN << "PGM written successfully!\n"
         << RESET;
}

// ----------------------- IMAGE PROCESSING -----------------------
void invert_ppm_colors(Image &img)
{
    if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    
    int size = img.width * img.height * 3;
    for (int i = 0; i < size; i++)
        img.pixels[i] = img.maxValue - img.pixels[i];
}

void invert_pgm_grayscale(Image &img)
{
    if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int size = img.width * img.height;
    for (int i = 0; i < size; i++)
        img.pixels[i] = img.maxValue - img.pixels[i];
}

void brighten_image(Image &img, int amount, bool isPPM)
{
    if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int size = img.width * img.height * (isPPM ? 3 : 1);

    for (int i = 0; i < size; i++)
        img.pixels[i] = min((int)img.pixels[i] + amount, img.maxValue);
}

void darken_image(Image &img, int amount, bool isPPM)
{
     if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int size = img.width * img.height * (isPPM ? 3 : 1);

    for (int i = 0; i < size; i++)
        img.pixels[i] = max((int)img.pixels[i] - amount, 0);
}

void flip_horizontal(Image &img, bool isPPM)
{
      if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;
    int rowSize = img.width * channels;

    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width / 2; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int left = y * rowSize + x * channels + c;
                int right = y * rowSize + (img.width - 1 - x) * channels + c;
                swap(img.pixels[left], img.pixels[right]);
            }
        }
    }
}

void flip_vertical(Image &img, bool isPPM)
{
    if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;
    int rowSize = img.width * channels;

    for (int y = 0; y < img.height / 2; y++)
    {
        int top = y * rowSize;
        int bottom = (img.height - 1 - y) * rowSize;

        for (int i = 0; i < rowSize; i++)
            swap(img.pixels[top + i], img.pixels[bottom + i]);
    }
}

void rotate_clockwise(Image &img, bool isPPM)
{if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;

    int newW = img.height;
    int newH = img.width;

    unsigned char *newPixels = new unsigned char[newW * newH * channels];

    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int oldIndex = (y * img.width + x) * channels + c;
                int newIndex = (x * newW + (newW - 1 - y)) * channels + c;

                newPixels[newIndex] = img.pixels[oldIndex];
            }
        }
    }

    delete[] img.pixels;
    img.pixels = newPixels;

    img.width = newW;
    img.height = newH;
}

void convert_to_grayscale(Image &img)
{
     if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    unsigned char *newPixels = new unsigned char[img.width * img.height];

    for (int i = 0; i < img.width * img.height; i++)
    {
        int r = img.pixels[i * 3];
        int g = img.pixels[i * 3 + 1];
        int b = img.pixels[i * 3 + 2];

        newPixels[i] = (0.299 * r + 0.587 * g + 0.114 * b);
    }

    delete[] img.pixels;
    img.pixels = newPixels;
}

void auto_contrast(Image &img, bool isPPM)
{
     if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;
    int size = img.width * img.height * channels;

    int minVal = 255, maxVal = 0;

    for (int i = 0; i < size; i++)
    {
        minVal = min(minVal, (int)img.pixels[i]);
        maxVal = max(maxVal, (int)img.pixels[i]);
    }

    float scale = 255.0f / (maxVal - minVal + 1);

    for (int i = 0; i < size; i++)
    {
        img.pixels[i] = (img.pixels[i] - minVal) * scale;
    }
}

void blur_image(Image &img, bool isPPM)
{
      if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;
    int W = img.width;
    int H = img.height;
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
                        sum += img.pixels[idx] * karr[k++];
                    }
                }

                out[(y * W + x) * channels + c] = sum / 9;
            }
        }
    }

    delete[] img.pixels;
    img.pixels = out;
}

void sharpen_image(Image &img, bool isPPM)
{
      if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;
    int W = img.width;
    int H = img.height;

    unsigned char *out = new unsigned char[W * H * channels];

    int karr[9] = {0, -1, 0,
                     -1, 5, -1,
                     0, -1, 0};

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
                        sum += img.pixels[idx] * karr[k++];
                    }
                }

                sum = max(0, min(255, sum));
                out[(y * W + x) * channels + c] = sum;
            }
        }
    }

    delete[] img.pixels;
    img.pixels = out;
}

void merge_images(Image &img1, Image &img2, bool horizontal, bool isPPM)
{
      if ((img1.pixels==nullptr) || ( img2.pixels==nullptr))
    {
        cout<<"No Operations can be performed , First Read Image!";
        return;
    }
    int channels = isPPM ? 3 : 1;

    int newW = horizontal ? img1.width + img2.width : max(img1.width, img2.width);
    int newH = horizontal ? max(img1.height, img2.height) : img1.height + img2.height;

    unsigned char *newPixels = new unsigned char[newW * newH * channels];

    // Initialize all pixels to 0 (instead of memset)
    for (int i = 0; i < newW * newH * channels; i++)
    {
        newPixels[i] = 0;
    }

    // copy img1
    for (int y = 0; y < img1.height; y++)
    {
        for (int x = 0; x < img1.width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int newIndex = (y * newW + x) * channels + c;
                int oldIndex = (y * img1.width + x) * channels + c;

                newPixels[newIndex] = img1.pixels[oldIndex];
            }
        }
    }

    // copy img2
    for (int y = 0; y < img2.height; y++)
    {
        for (int x = 0; x < img2.width; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                int nx = horizontal ? img1.width + x : x;
                int ny = horizontal ? y : img1.height + y;

                int newIndex = (ny * newW + nx) * channels + c;
                int oldIndex = (y * img2.width + x) * channels + c;

                newPixels[newIndex] = img2.pixels[oldIndex];
            }
        }
    }

    delete[] img1.pixels;
    img1.pixels = newPixels;

    img1.width = newW;
    img1.height = newH;
}

void add_border(Image &img, int borderSize, int color, bool isPPM)
{if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;

    int newW = img.width + borderSize * 2;
    int newH = img.height + borderSize * 2;

    unsigned char *newPixels = new unsigned char[newW * newH * channels];

    // fill border
    for (int i = 0; i < newW * newH * channels; i++)
        newPixels[i] = color;

    // copy original image
    for (int y = 0; y < img.height; y++)
        for (int x = 0; x < img.width; x++)
            for (int c = 0; c < channels; c++)
            {
                int newIndex = ((y + borderSize) * newW + (x + borderSize)) * channels + c;
                int oldIndex = (y * img.width + x) * channels + c;
                newPixels[newIndex] = img.pixels[oldIndex];
            }

    delete[] img.pixels;
    img.pixels = newPixels;
    img.width = newW;
    img.height = newH;
}

void crop_image(Image &img, int x, int y, int w, int h, bool isPPM)
{
    if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;

    if (!img.pixels)
    {
        cout << "\033[31mError: Image must be read first before cropping!\033[0m\n";
        return;
    }

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= img.width || y >= img.height)
    {
        cout << "\033[31mError: Crop coordinates outside image dimensions!\033[0m\n";
        return;
    }
    if (x + w > img.width)
        w = img.width - x;
    if (y + h > img.height)
        h = img.height - y;

    unsigned char *newPixels = new unsigned char[w * h * channels];

    for (int cy = 0; cy < h; cy++)
        for (int cx = 0; cx < w; cx++)
            for (int c = 0; c < channels; c++)
            {
                int oldIndex = ((y + cy) * img.width + (x + cx)) * channels + c;
                int newIndex = (cy * w + cx) * channels + c;
                newPixels[newIndex] = img.pixels[oldIndex];
            }

    delete[] img.pixels;
    img.pixels = newPixels;
    img.width = w;
    img.height = h;
}

void resize_image(Image &img, int newW, int newH, bool isPPM)
{
      if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    int channels = isPPM ? 3 : 1;
    unsigned char *newPixels = new unsigned char[newW * newH * channels];

    float xRatio = (float)img.width / newW;
    float yRatio = (float)img.height / newH;

    for (int y = 0; y < newH; y++)
    {
        for (int x = 0; x < newW; x++)
        {
            int oldX = x * xRatio;
            int oldY = y * yRatio;

            for (int c = 0; c < channels; c++)
            {
                newPixels[(y * newW + x) * channels + c] =
                    img.pixels[(oldY * img.width + oldX) * channels + c];
            }
        }
    }

    delete[] img.pixels;
    img.pixels = newPixels;
    img.width = newW;
    img.height = newH;
}

void threshold(Image &img, int t, bool isPPM)
{
     if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    if (t < 0)
        t = 0;
    if (t > 255)
        t = 255;

    int channels = isPPM ? 3 : 1;
    int size = img.width * img.height * channels;

    for (int i = 0; i < size; i++)
        img.pixels[i] = (img.pixels[i] < t) ? 0 : 255;
}

void posterize(Image &img, int levels, bool isPPM)
{
    if (img.pixels == nullptr)
{
    cout << "No Operations can be performed, First Read Image!";
    return;
}

    if (levels < 2)
        levels = 2;
    if (levels > 255)
        levels = 255;

    int channels = isPPM ? 3 : 1;
    int size = img.width * img.height * channels;

    float step = 255.0f / (levels - 1);

    for (int i = 0; i < size; i++)
    {
        int val = img.pixels[i];
        int newVal = int((val / step) + 0.5f) * step;
        if (newVal < 0)
            newVal = 0;
        if (newVal > 255)
            newVal = 255;
        img.pixels[i] = newVal;
    }
}
