//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_CLIPPINGPOINTCIRCLE_H
#define GRAPHICSPROJECT_CLIPPINGPOINTCIRCLE_H

#include "ClippingOperation.h"
#include "Shape.h"
#include "INPUT.h"
#include "Circle.h"
class ClippingPointCircle : public ClippingOperation{
public:
    int xc,yc,R;
public:
    ClippingPointCircle(Circle circle)
    {
        this->xc = circle.xc;
        this->yc = circle.yc;
        this->R = circle.R;
    }
    void clip(HDC &hdc, COLORREF color) override
    {
        RECT    rcCli;
        GetClientRect(WindowFromDC(hdc), &rcCli);
        int nWidth = rcCli.right-rcCli.left;
        int nHeight  = rcCli.bottom-rcCli.top;
        for (int x = 0; x <= nWidth; ++x) {
            for (int y = 0; y <= nHeight ; ++y) {
                if (pow(xc - x,2) + pow(yc - y,2) > pow(R,2))
                {
                    Draw::drawPixel(hdc, x, y, color);
                }
            }
        }
    }
};


#endif //GRAPHICSPROJECT_CLIPPINGPOINTCIRCLE_H
