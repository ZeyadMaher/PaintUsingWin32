//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_CLIPPINGOPERATION_H
#define GRAPHICSPROJECT_CLIPPINGOPERATION_H

#include "windows.h"
class ClippingOperation {

    virtual void clip(HDC &hdc, COLORREF color) = 0;
};


#endif //GRAPHICSPROJECT_CLIPPINGOPERATION_H
