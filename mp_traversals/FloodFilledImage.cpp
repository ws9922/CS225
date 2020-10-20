#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png):png_(&png) {
  /** @todo [Part 2] */
  store_tvs = std::vector<ImageTraversal*>();
  store_cp = std::vector<ColorPicker*>();
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  store_tvs.push_back(&traversal);
  store_cp.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  PNG after = *png_;
  int step = 0;
  int size = store_tvs.size();
  animation.addFrame(after);
  for (int i = 0; i < size; i++) {
    ImageTraversal * tvs = store_tvs[i];
    ColorPicker * cp = store_cp[i];
    for (ImageTraversal::Iterator it = tvs->begin(); it != tvs->end(); ++it) {
      Point to_change_point = *it;
      HSLAPixel& to_change_pixel = after.getPixel(to_change_point.x, to_change_point.y);
      to_change_pixel = cp->getColor(to_change_point.x, to_change_point.y);
      step++;
      if (step % frameInterval == 0) {
        animation.addFrame(after);
      }
    }
  }
  animation.addFrame(after);
  /**if (step % frameInterval != 0) {
    animation.addFrame(after);
  }**/
  

  return animation;
}
