#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png;
  if (png.readFromFile(inputFile)) {
    cs225::PNG result(png);
    for (unsigned int i = 0; i < png.width(); i++) {
      for (unsigned int j = 0; j < png.height(); j++) {
        cs225::HSLAPixel & resultPixel = result.getPixel(i, j);
        resultPixel = png.getPixel(png.width() - 1 - i, png.height() - 1 - j);
        }
      }
  result.writeToFile(outputFile);
  }
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      if (x < 360) {
        pixel.h = x;
      } else {
        pixel.h = y / 10;
      }
      pixel.l = 0.5;
      pixel.s = 0.5;
    }
  }
  return png;
}
