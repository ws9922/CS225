
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

#include "cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "imageTraversal/BFS.h"
#include "imageTraversal/DFS.h"

using namespace cs225;

PNG getTestPNG() {
  PNG png(4, 4);
  HSLAPixel blackPixel(180, 1, 0);
  
  for (unsigned i = 0; i < 4; i++) {
    png.getPixel(i, 0) = blackPixel;
    png.getPixel(0, i) = blackPixel;
    png.getPixel(i, 3) = blackPixel;
    png.getPixel(3, i) = blackPixel;
  }
    
  return png;
}

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */

  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  DFS t(png, startPoint, 0.2);
  ImageTraversal::Iterator it = t.begin();
  std::cout<< (*it).x << "," << (*it).y << std::endl;
  while (it != t.end()) {
    std::cout<< (*it).x << "," << (*it).y << std::endl;
  }
  /**REQUIRE( *it == Point(0, 0) ); ++it;
  REQUIRE( *it == Point(0, 1) ); ++it;
  REQUIRE( *it == Point(0, 2) ); ++it;
  REQUIRE( *it == Point(0, 3) ); ++it;
  REQUIRE( *it == Point(1, 3) ); ++it;
  REQUIRE( *it == Point(2, 3) ); ++it;  
  REQUIRE( *it == Point(3, 3) ); ++it;
  REQUIRE( *it == Point(3, 2) ); ++it;
  REQUIRE( *it == Point(3, 1) ); ++it;  
  REQUIRE( *it == Point(3, 0) ); ++it;
  REQUIRE( *it == Point(2, 0) ); ++it;
  REQUIRE( *it == Point(1, 0) ); ++it;  **/



  return 0;
}


