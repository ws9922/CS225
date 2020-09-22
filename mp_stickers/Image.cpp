#include "Image.h"

#include <string>
using std::string;

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;
using cs225::PNG;


void Image::darken() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l <= 0.1) {
                pixel.l = 0;
            } else {
                pixel.l -= 0.1;
            }
        }
    }
}

void Image::darken(double amount) {
     for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l - amount <= 0) {
                pixel.l = 0;
            } else {
                pixel.l -= amount;
            }
        }
    }
}

void Image::desaturate() {
     for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s <= 0.1) {
                pixel.s = 0;
            } else {
                pixel.s -= 0.1;
            }
        }
    }
}

void Image::desaturate(double amount) {
     for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s - amount <= 0) {
                pixel.s = 0;
            } else {
                pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale() {
   for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::illinify() {
     for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if ((pixel.h >= 0 && pixel.h <= 113.5) || (pixel.h > 293.5 && pixel.h < 360)) {
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    } 
}

void Image::lighten() {
     for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l >= 0.9) {
                pixel.l = 1;
            } else {
                pixel.l += 0.1;
            }
        }
    }
}

void Image::lighten(double amount) {
     for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l + amount >= 1) {
                pixel.l = 1;
            } else {
                pixel.l += amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s >= 0.9) {
                pixel.s = 1;
            } else {
                pixel.s += 0.1;
            }
        }
    }
}

void Image::saturate(double amount) {
      for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.s + amount >= 1) {
                pixel.s = 1;
            } else {
                pixel.s += amount;
            }
        }
    }
}

void Image::rotateColor(double degrees) {
     for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.h + degrees >= 360) {
                pixel.h = pixel.h + degrees - 360;
            } else if(pixel.h + degrees <= 0) {
                pixel.h = pixel.h + degrees + 360;
            } else {
                pixel.h = pixel.h + degrees;
            }
        }
    } 
}

void Image::scale(double factor) {
    Image old = *this;
    unsigned int newwidth = width() * factor;
    unsigned int newheight = height() * factor;
    this->resize(newwidth, newheight);
    for (unsigned x = 0; x < newwidth; x++) {
        for (unsigned y = 0; y < newheight; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel = old.getPixel((int)(x/factor), (int)(y/factor));
        }
    } 
}

void Image::scale(unsigned w, unsigned h) {
    Image old = *this;
    double width_factor = (double)w / (double) width();
    double height_factor = (double)h / (double) height();
    unsigned int newwidth = 0;
    unsigned int newheight = 0;
    double factor = 0;
    if (width_factor <= height_factor) {
        newwidth = width_factor * width();
        newheight = width_factor * height();
        factor = width_factor;
    } else {
        newwidth = height_factor * width();
        newheight = height_factor * height();
        factor = height_factor;
    }
    this->resize(newwidth, newheight);
    for (unsigned x = 0; x < newwidth; x++) {
        for (unsigned y = 0; y < newheight; y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel = old.getPixel((int)(x/factor), (int)(y/factor));
        }
    } 
}