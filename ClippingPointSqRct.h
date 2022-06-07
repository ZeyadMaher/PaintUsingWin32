//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_CLIPPINGPOINTSQRCT_H
#define GRAPHICSPROJECT_CLIPPINGPOINTSQRCT_H

#include "ClippingOperation.h"
#include "Shape.h"
#include "RectSquare.h"
#include "Draw.h"
class ClippingPointSqRct : public ClippingOperation{
public:
    int xl,xr,yt,yb;
    ClippingPointSqRct(RectSquare rectSquare)
    {
        xl = rectSquare.getXl();
        xr = rectSquare.getXr();
        yb = rectSquare.getYb();
        yt = rectSquare.getYt();
    }
    void clip(HDC &hdc, COLORREF color) override
    {
        RECT    rcCli;
        GetClientRect(WindowFromDC(hdc), &rcCli);
        int nWidth = rcCli.right-rcCli.left;
        int nHeight  = rcCli.bottom-rcCli.top;
        for (int x = 0; x <= nWidth; ++x) {
            for (int y = 0; y <= nHeight ; ++y) {
                if (x < xl || x > xr || y < yb || y > yt) Draw::drawPixel(hdc,x,y,color);
            }
        }
    }
};


#endif //GRAPHICSPROJECT_CLIPPINGPOINTSQRCT_H
