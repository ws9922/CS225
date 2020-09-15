/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        Image* getSticker(unsigned index);
};
 
