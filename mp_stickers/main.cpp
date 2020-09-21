#include "Image.h"
#include "StickerSheet.h"
#include <iostream>


int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
   Image myImage, basePicture, Google, I, Apple;
   basePicture.readFromFile("alma.png");
   Google.readFromFile("google.png");
   I.readFromFile("i.png");
   Apple.readFromFile("apple.png");
   Image &sticker1 = Google;
   Image &sticker2 = I;
   Image &sticker3 = Apple;
   StickerSheet mySheet(basePicture, 3);
   mySheet.addSticker(sticker1, 0, 0);
   mySheet.addSticker(sticker2, 80, 4);
   mySheet.addSticker(sticker3, 70, 100);
   myImage = mySheet.render();
   myImage.writeToFile("myImage.png");

  return 0;
}
