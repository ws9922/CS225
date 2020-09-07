#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png;
  png.readFromFile(inputFile);
  cs225::PNG result(png);
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
       cs225::HSLAPixel & pixel = png.getPixel(x, y);
       cs225::HSLAPixel & resultPixel = result.getPixel(png.height() - x - 1, png.width() - y - 1);
       resultPixel = pixel;
    }
  }
  result.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3

  return png;
}
