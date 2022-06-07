//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_CLIPPINGLINECIRCLE_H
#define GRAPHICSPROJECT_CLIPPINGLINECIRCLE_H

#include "ClippingOperation.h"
#include "ClippingLineRectSq.h"
#include "Shape.h"
#include "RectSquare.h"
#include "Circle.h"
class ClippingLineCircle : public ClippingOperation{
public:
    int xc,yc,R;
    vector<Line> lines;
    ClippingLineCircle(Circle circle, vector<Line> lines)
    {
        xc = circle.xc;
        yc = circle.yc;
        R = circle.R;
        this->lines = lines;
    }
    void dda(HDC &hdc, COLORREF color, int x1 ,int x2, int y1 , int y2)
    {
        double dx = (x2 - x1)*1.0;
        double dy = (y2 - y1)*1.0;
        if (abs(dy) <= abs(dx))
        {
            if (x1 > x2)
                swap(x1,x2), swap(y1,y2);
            if (pow(xc - x1,2) + pow(yc - y1,2) <= pow(R,2))
            {
                Draw::drawPixel(hdc, x1, y1, color);
            }
            int x = x1;
            double y;
            while (x < x2)
            {
                x++;
                y = y1 + (x - x1) * (dy/dx);
                if (pow(xc - x,2) + pow(yc - y,2) <= pow(R,2))
                {
                    Draw::drawPixel(hdc, x, y, color);
                }
            }
        }
        else
        {
            if(y1 > y2)
                swap(x1,x2),swap(y1,y2);
            if (pow(xc - x1,2) + pow(yc - y1,2) <= pow(R,2))
            {
                Draw::drawPixel(hdc, x1, y1, color);
            }            int y = y1;
            double x;
            while (y < y2)
            {
                y++;
                x = x1 + (y - y1)*(dx/dy);
                if (pow(xc - x,2) + pow(yc - y,2) <= pow(R,2))
                {
                    Draw::drawPixel(hdc, x, y, color);
                }
            }

        }
    }
    void clip(HDC &hdc, COLORREF color) override
    {
        RectSquare rectSquare = RectSquare(xc - R, yc - R,2*R,2*R);
        vector<Line> toDrawLines = (ClippingLineRectSq(rectSquare,lines)).getInLines();
        for (int i = 0; i < toDrawLines.size(); ++i) {
            dda(hdc,color,toDrawLines[i].x1,toDrawLines[i].x2,toDrawLines[i].y1,toDrawLines[i].y2);
        }
    }
};


#endif //GRAPHICSPROJECT_CLIPPINGLINECIRCLE_H
