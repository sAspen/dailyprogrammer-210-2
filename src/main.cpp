#include <iostream>
#include <tuple>

#include "Netpbm.h"

using std::cin;
using std::cout;



void
drawGradient(unsigned int width, unsigned int height,
             std::tuple<uint8_t, uint8_t, uint8_t> color1,
             std::tuple<uint8_t, uint8_t, uint8_t> color2)
{
  Netpbm image("output.ppm", width, height, RGB_BINARY, 255);

  //Unpack the tuples into local variables
  uint8_t red1, green1, blue1;
  std::tie(red1, green1, blue1) = color1;

  uint8_t red2, green2, blue2;
  std::tie(red2, green2, blue2) = color2;

  //Calculate the stepping interval for each color per pixel
  double redStep, greenStep, blueStep;
  redStep = ((double) red2 - (double) red1) / (double) width;
  greenStep = ((double) green2 - (double) green1) / (double) width;
  blueStep = ((double) blue2 - (double) blue1) / (double) width;

  //Output the raster data
  for (unsigned int i = 0; i < height; i++) {
    //Next row
    //Reset the color components
    double red = red1, green = green1, blue = blue1;
    for (unsigned int j = 0; j < width; j++) {
      //Next column/pixel
      //Write the RGB bytes
      image.writePixel(red, green, blue);
      //Step the color components
      red += redStep;
      green += greenStep;
      blue += blueStep;
    }
  }
}



void
readInputFile(char* name)
{
  std::ifstream inFile(name);

  if (!inFile) {
    std::string s("Could not open ");
    throw std::invalid_argument(s + name);
  }

  unsigned int width, height;
  unsigned int rgb[3];

  inFile >> width;
  inFile >> height;

  for (int i = 0; i < 3; i++) {
    inFile >> rgb[i];
  }
  std::tuple<uint8_t, uint8_t, uint8_t> color1(rgb[0], rgb[1], rgb[2]);

  for (int i = 0; i < 3; i++) {
    inFile >> rgb[i];
  }
  std::tuple<uint8_t, uint8_t, uint8_t> color2(rgb[0], rgb[1], rgb[2]);

  drawGradient(width, height, color1, color2);
}



void
readConsoleInput(void)
{
  unsigned int width, height;
  unsigned int rgb[3];

  cout << "Width: ";
  cin >> width;

  cout << "Height: ";
  cin >> height;

  cout << "Color 1 (R G B): ";
  scanf("%d %d %d", &rgb[0], &rgb[1], &rgb[2]);
  std::tuple<uint8_t, uint8_t, uint8_t> color1(rgb[0], rgb[1], rgb[2]);


  cout << "Color 2 (R G B): ";
  scanf("%d %d %d", &rgb[0], &rgb[1], &rgb[2]);
  std::tuple<uint8_t, uint8_t, uint8_t> color2(rgb[0], rgb[1], rgb[2]);

  drawGradient(width, height, color1, color2);
}



int
main(int argc, char** argv)
{
  //If we've got an argument, assume it's a file and use it as input.
  //Otherwise, request and read input from console.
  bool fileInput = (argc > 1);

  if (fileInput) {
    readInputFile(argv[1]);
  }
  else {
    readConsoleInput();
  }

  return 0;
}

