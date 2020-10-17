#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(
  HSLAPixel backgroundColor, double spacing, double increment
) : backgroundColor(backgroundColor), spacing(spacing), hue(20), increment(increment) {}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue, 0.5, 0.2);
  hue += increment;
  if (hue >= 360) {hue -= 360;}
  if (x % spacing == 0 || y % spacing == 0) {
    return pixel;
  } else {
    return backgroundColor;
  }
}
