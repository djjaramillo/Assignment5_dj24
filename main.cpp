#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pixel.h"


using namespace std;

// Function declarations

void average_colors(vector<Pixel> &pixel_list);
void flip_vertically(vector<Pixel> &pixel_list);

int main(int argc, char *argv[])
{
    // Check if filename was provided
    if (argc < 2)
    {
        cout << "Please enter a filename." << endl;
        return 1;
    }

    // Open input file
    ifstream input(argv[1]);

    if (!input.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Create vector to store pixels
    vector<Pixel> pixel_list;
    string line;

    // Read every line from the file
    while (getline(input, line))



{
        Pixel pixel;

        // Find commas and extract values
        // find() locates the comma
        // substr() extracts the value
        // erase() removes the value and comma

        int comma = line.find(',');
        pixel.x = stoi(line.substr(0, comma));
        line.erase(0, comma + 1);

        comma = line.find(',');
        pixel.y = stoi(line.substr(0, comma));
        line.erase(0, comma + 1);

        comma = line.find(',');
        pixel.r = stof(line.substr(0, comma));
        line.erase(0, comma + 1);

        comma = line.find(',');
        pixel.g = stof(line.substr(0, comma));
        line.erase(0, comma + 1);

        pixel.b = stof(line);

        // Store pixel in vector
        pixel_list.push_back(pixel);
    }

    input.close();

    // Display number of pixels
    cout << "Pixels read: " << pixel_list.size() << endl;

    // Calculate the average RGB values
    average_colors(pixel_list);

    // Flip pixels 
    flip_vertically(pixel_list);

    // Open output file
    ofstream output("flipped.dat");

    if (!output.is_open())
    {
        cout << "Error creating output file." << endl;
        return 1;
    }

    // Write pixels in the required order
    // Each x coordinate has 256 y coordinates
    for (int x = 0; x < 512; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            int i = x * 256 + (255 - y);

            output << x << ","
                   << y << ","
                   << pixel_list[i].r << ","
                   << pixel_list[i].g << ","
                   << pixel_list[i].b << endl;
        }
    }

    output.close();

    cout << "Flipped data saved to flipped.dat" << endl;

    return 0;
}

// Function to calculate average RGB values
void average_colors(vector<Pixel> &pixel_list)
{
    double red = 0;
    double green = 0;
    double blue = 0;

    for (int i = 0; i < pixel_list.size(); i++)
    {
        red += pixel_list[i].r;
        green += pixel_list[i].g;
        blue += pixel_list[i].b;
    }

    if (pixel_list.empty())
    {
        cout << "No pixels found." << endl;
        return;
    }

    cout << "Average Red: "
         << red / pixel_list.size() << endl;

    cout << "Average Green: "
         << green / pixel_list.size() << endl;

    cout << "Average Blue: "
         << blue / pixel_list.size() << endl;
}

// Function to flip image vertically
void flip_vertically(vector<Pixel> &pixel_list)
{
    for (int i = 0; i < pixel_list.size(); i++)
    {
        pixel_list[i].y = 255 - pixel_list[i].y;
    }
}
