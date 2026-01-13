#include <iostream>
#include <string>
#include "Image.h"
#include "global.h"
#include "global.cpp"

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

int main()
{
    cout << BOLD << CYAN << "=== Welcome to MINI IMAGE EDITOR ===\n\n"
         << RESET;

    Image img = {0, 0, 255, nullptr};
    string mode;

    do
    {
        cout << YELLOW << "Enter file mode (text or binary): " << RESET;
        cin >> mode;
    } while (mode != "binary" && mode != "text");

    // convert to lowercase using ASCII +32
    for (int i = 0; i < mode.length(); i++)
    {
        if (mode[i] >= 'A' && mode[i] <= 'Z')
            mode[i] += 32;
    }

    int choice;
    do
    {
        display_menu(); // We'll make this colorful in global.cpp
        cin >> choice;

        switch (choice)
        {
        case 1:
            ppm_operations(img, mode);
            break;
        case 2:
            pgm_operations(img, mode);
            break;
        case 3:
            cout << GREEN << "\nExiting MINI IMAGE EDITOR. Goodbye!\n"
                 << RESET;
            break;
        default:
            cout << RED << "Invalid choice! Try again.\n"
                 << RESET;
        }

    } while (choice != 3);

    free_pixels(img); // free memory (Deallocate the pixel array)
    return 0;
}
