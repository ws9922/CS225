#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;
#include <iostream>


StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    max_ = max;
    arry = new Image*[max_];
    base = new Image(picture);
    for (unsigned int i = 0; i < max_; i++) {
        arry[i] = NULL;
    }
}
StickerSheet::~StickerSheet() {
    for (unsigned int i = 0; i < max_; i++) {
        delete arry[i];
        arry[i] = NULL;
    }
    delete[] arry;
    delete base;
}
StickerSheet::StickerSheet(const StickerSheet & other) {
    max_ = other.max_;
    arry = new Image*[max_];
    for (unsigned int i = 0; i < max_; i++) {
        arry[i] = new Image(*(other.arry[i]));
    }
    base = new Image(*(other.base));
}
const StickerSheet& StickerSheet::operator= (const StickerSheet& other) {
    if (this != &other) {
        for (unsigned int i = 0; i < max_; i++) {
            delete arry[i];
            arry[i] = NULL;
        }
        delete[] arry;
        delete base;
        max_ = other.max_;
        arry = new Image*[max_];
        for (unsigned int i = 0; i < max_; i++) {
            arry[i] = new Image(*(other.arry[i]));
        }
        base = new Image(*(other.base));
    } 
    return *this;
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    sticker.x_ = x;
    sticker.y_ = y;
    for (unsigned int i = 0; i < max_; i++) {
        if(arry[i] == NULL){
            arry[i] = new Image(sticker);
            return i;
        }
    }
    return -1;   
}

void StickerSheet::changeMaxStickers(unsigned max) {
    Image** oldarry = new Image*[max_];
    for (unsigned int i = 0; i < max_; i++) {
        oldarry[i] = arry[i];
    }
    unsigned int oldmax = this->max_;
    this->max_ = max;
    arry = new Image*[max_];
    if (oldmax >= max && max > 0) {
        for (unsigned int i = 0; i < max; i++) {
            arry[i] = oldarry[i];
        }
    }   
    if(max > oldmax && max > 0){
        for (unsigned int i = 0; i < oldmax; i++) {
            arry[i] = oldarry[i];
        }
        for (unsigned int i = oldmax; i < max; i++) {
            arry[i] = NULL;
        }
    }
    for (unsigned int i = 0; i < oldmax; i++) {
            delete oldarry[i];
            oldarry[i] = NULL;
        }
    delete[] oldarry;
}
    

Image * StickerSheet::getSticker (unsigned index) {
    if (arry[index] == NULL || index >= max_) {
        return NULL;
    }
    return arry[index];
}

void StickerSheet::removeSticker(unsigned index) {
    arry[index] = NULL;
}

Image StickerSheet::render() const {
    unsigned int width = base->width();
    unsigned int height = base->height();
    for (unsigned int i = 0; i < max_; i++) {
        if (arry[i] != NULL) {
            if ((arry[i]->width() + arry[i]->x_) > width) {
                width = arry[i]->width() + arry[i]->x_;
            }
            if ((arry[i]->height() + arry[i]->y_) > height) {
                height = arry[i]->height() + arry[i]->y_;
            }
        }
    }
    Image result;
    result.resize(width, height);
    for (unsigned x = 0; x < base->width(); x++) {
        for (unsigned y = 0; y < base->height(); y++) {
            HSLAPixel & pixel = result.getPixel(x, y);
            pixel = base->getPixel(x, y);
        }
    }
    for (unsigned int i = 0; i < max_; i++) {
        if (arry[i] != NULL) {
            for (unsigned x = arry[i]->x_; x < arry[i]->x_ + arry[i]->width(); x++) {
                for (unsigned y = arry[i]->y_; y < arry[i]->y_ + arry[i]->height(); y++) {
                    HSLAPixel & pixel = result.getPixel(x, y);
                    HSLAPixel stickerPixel = arry[i]->getPixel(x - (arry[i]->x_), y - (arry[i]->y_));
                    if (stickerPixel.a != 0) {
                        pixel = stickerPixel;
                    }
                }
            }
        }
    }
    return result;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (arry[index] == NULL || index >= max_) {
        return false;
    }
    arry[index]->x_ = x;
    arry[index]->y_ = y;
    return true;
}

  