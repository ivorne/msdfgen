
#include "save-png.h"

#include "../core/arithmetics.hpp"
#include <lodepng.h>

namespace msdfgen {

bool savePng(const Bitmap<float> &bitmap, const char *filename, bool invertY) {
    std::vector<unsigned char> pixels(bitmap.width()*bitmap.height());
    std::vector<unsigned char>::iterator it = pixels.begin();
    for (int y = 0; y < bitmap.height(); ++y)
        for (int x = 0; x < bitmap.width(); ++x){
			int yy = invertY ? bitmap.height()-1-y : y;
            *it++ = clamp(int(bitmap(x, yy)*0x100), 0xff);
		}
    return !lodepng::encode(filename, pixels, bitmap.width(), bitmap.height(), LCT_GREY);
}

bool savePng(const Bitmap<FloatRGB> &bitmap, const char *filename, bool invertY) {
    std::vector<unsigned char> pixels(4*bitmap.width()*bitmap.height());
    std::vector<unsigned char>::iterator it = pixels.begin();
    for (int y = 0; y < bitmap.height(); ++y)
        for (int x = 0; x < bitmap.width(); ++x) {
			int yy = invertY ? bitmap.height()-1-y : y;
            *it++ = clamp(int(bitmap(x, yy).r*0x100), 0xff);
            *it++ = clamp(int(bitmap(x, yy).g*0x100), 0xff);
            *it++ = clamp(int(bitmap(x, yy).b*0x100), 0xff);
            *it++ = 0xfe;
        }
    return !lodepng::encode(filename, pixels, bitmap.width(), bitmap.height(), LCT_RGBA);
}

}
