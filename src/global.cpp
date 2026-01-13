#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <limits>
#include "global.h"
#include "GrayScale.h"
#include "Coloured.h"

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
void ask_save_image(Gray_Scale_Image &img, const string &mode)
{
    char save;
    cout << "Do you want to save the modified image? (y/n): ";
    cin >> save;
    if (save == 'y' || save == 'Y')
    {
        string filename;
        filename = getValidFilename();
        img.write(filename, mode);
        cout<<"Image Saved Successfully as "<<filename<<endl;
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
void skip_comments(ifstream &file)
{
    file >> ws;
    while (file.peek() == '#')
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        file >> ws;
    }
}
// ----------------------- PPM MENU -----------------------
void ppm_operations(const string &mode)
{
    Coloured img;
    int c;
    do
    {
        bool modified = false;
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
            img.read(fname, mode);
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
            img.write(fname, mode);
            break;
        }
        case 3:
            img.invert();
            // ask_save_image(img, mode);
            
            break;
        case 4:
        {
            int newW, newH;
            cout << YELLOW << "Enter new width and height: " << RESET;
            newW = getPositiveInt();
            newH = getPositiveInt();
            img.resize(newW, newH);
            // ask_save_image(img, mode);
            
            break;
        }
        case 5:
        {
            int amt;
            cout << YELLOW << "Enter brightness amount: " << RESET;
            amt = getPositiveInt();
            img.brighten(amt);
            // ask_save_image(img, mode);
            
            break;
        }
        case 6:
        {
            int amt;
            cout << YELLOW << "Enter darken amount: " << RESET;
            amt = getPositiveInt();
            img.darken(amt);
            // ask_save_image(img, mode);
            
            break;
        }
        case 7:
            img.flip_horizontal();
            // ask_save_image(img, mode);
            
            break;
        case 8:
            img.flip_vertical();
            // ask_save_image(img, mode);
            
            break;
        case 9:
            img.rotate_clockwise();
            // ask_save_image(img, mode);
            
            break;
        case 10:
            img.convert_to_grayscale();
            // ask_save_image(img, mode);
            
            break;
        case 11:
            img.auto_contrast();
            // ask_save_image(img, mode);
            
            break;
        case 12:
            img.blur();
            // ask_save_image(img, mode);
            
            break;
        case 13:
            img.sharpen();
            // ask_save_image(img, mode);
            
            break;
        case 14:
        {
            Coloured img2;
            string fname;
            cout << YELLOW << "Enter file to merge: " << RESET;
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
            img2.read(fname, mode);
            img.merge(img2, true);
            // ask_save_image(img, mode);
            
            break;
        }
        case 15:
        {
            int size, color;
            cout << YELLOW << "Enter border size: " << RESET;
            size = getPositiveInt();
            cout << YELLOW << "Enter border color (0-" << img.getMaxValue() << "): " << RESET;
            color = getPositiveInt();
            img.add_border(size, color);
            // ask_save_image(img, mode);
            
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
            img.crop(x, y, w, h);
            // ask_save_image(img, mode);
            
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
            img.threshold(val);
            // ask_save_image(img, mode);
            
            break;
        }
        case 18:
        {
            int levels;
            cout << "Enter number of levels: ";
            levels = getPositiveInt();
            img.posterize(levels);
            // ask_save_image(img, mode);
            
            break;
        }
        case 19:
            break;
        default:
            cout << RED << "Invalid choice! Try again.\n"
                 << RESET;
        }
        if (img.getIsLoaded() && c != 19)
        {
            ask_save_image(img, mode);
        }
    } while (c != 19);
}
// ----------------------- PGM MENU -----------------------
void pgm_operations(const string &mode)
{
    Gray_Scale_Image img;
    int c;
    do
    {
        cout << BOLD << MAGENTA << "\n--- PGM MENU ---\n"
             << RESET;
        cout << BOLD << MAGENTA << "\n--- READ IMAGE BEFORE DOING ANY OPERATION ! ---\n"
             << RESET;
        cout << YELLOW << "1. Read PGM\n"
             << RESET;
        cout << YELLOW << "2. Write PGM\n"
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
            cout << YELLOW << "Enter PGM file name: " << RESET;
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
            img.read(fname, mode);
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
                    if (a == '.' && b == 'p' && c == 'g' && d == 'm')
                    {
                        break;
                    }
                }
                fname = getValidFilename();
            }
            img.write(fname, mode);
            break;
        }
        case 3:
            img.invert();
            // ask_save_image(img, mode);
            
            break;
        case 4:
        {
            int newW, newH;
            cout << YELLOW << "Enter new width and height: " << RESET;
            newW = getPositiveInt();
            newH = getPositiveInt();
            img.resize(newW, newH);
            // ask_save_image(img, mode);
            
            break;
        }
        case 5:
        {
            int amt;
            cout << YELLOW << "Enter brightness amount: " << RESET;
            amt = getPositiveInt();
            img.brighten(amt);
            // ask_save_image(img, mode);
            
            break;
        }
        case 6:
        {
            int amt;
            cout << YELLOW << "Enter darken amount: " << RESET;
            amt = getPositiveInt();
            img.darken(amt);
            // ask_save_image(img, mode);
            
            break;
        }
        case 7:
            img.flip_horizontal();
            // ask_save_image(img, mode);
            
            break;
        case 8:
            img.flip_vertical();
            // ask_save_image(img, mode);
            
            break;
        case 9:
            img.rotate_clockwise();
            // ask_save_image(img, mode);
            
            break;
        case 10:
            img.convert_to_grayscale();
            // ask_save_image(img, mode);
            
            break;
        case 11:
            img.auto_contrast();
            // ask_save_image(img, mode);
            
            break;
        case 12:
            img.blur();
            // ask_save_image(img, mode);
            
            break;
        case 13:
            img.sharpen();
            // ask_save_image(img, mode);
            
            break;
        case 14:
        {
            Gray_Scale_Image img2;
            string fname;
            cout << YELLOW << "Enter file to merge: " << RESET;
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
            img2.read(fname, mode);
            img.merge(img2, true);
            // ask_save_image(img, mode);
            
            break;
        }
        case 15:
        {
            int size, color;
            cout << YELLOW << "Enter border size: " << RESET;
            size = getPositiveInt();
            cout << YELLOW << "Enter border color (0-" << img.getMaxValue() << "): " << RESET;
            color = getPositiveInt();
            img.add_border(size, color);
            // ask_save_image(img, mode);
            
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
            img.crop(x, y, w, h);
            // ask_save_image(img, mode);
            
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
            img.threshold(val);
            // ask_save_image(img, mode);
            
            break;
        }
        case 18:
        {
            int levels;
            cout << "Enter number of levels: ";
            levels = getPositiveInt();
            img.posterize(levels);
            // ask_save_image(img, mode);
            
            break;
        }
        case 19:
            break;
        default:
            cout << RED << "Invalid choice! Try again.\n"
                 << RESET;
        }
        if (img.getIsLoaded() && c != 19)
        {
            ask_save_image(img, mode);
        }
    } while (c != 19);
}