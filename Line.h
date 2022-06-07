//
// Created by dell on ٣٠/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_LINE_H
#define GRAPHICSPROJECT_LINE_H

#include "Shape.h"
#include "Draw.h"
#include "INPUT.h"
class Line : public Shape{
    void midPoint(HDC &hdc, COLORREF color)
    {
        int dx = abs(x1-x2);
        int dy = abs(y1-y2);

        if (dy <= dx)
        {
            double y,m;
            if (x1 > x2)
            {
                std::swap(x1,x2);
                std::swap(y1,y2);
            }
            m = ((y2 - y1)*1.0)/(x2 - x1);
            Draw::drawPixel(hdc,x1,y1,color);
            y = y1;
            while (x1 < x2)
            {
                x1++;
                y+=m;
                Draw::drawPixel(hdc,x1,y,color);
            }
        }
        else
        {
            double x,m;
            if (y1 > y2)
            {
                std::swap(x1,x2);
                std::swap(y1,y2);
            }
            m = ((x2 - x1)*1.0)/(y2 - y1);
            Draw::drawPixel(hdc,x1,y1,color);
            x = x1;
            while (y1 < y2)
            {
                x+= m;
                y1++;
                Draw::drawPixel(hdc,x,y1,color);
            }
        }
    }
    void dda(HDC &hdc, COLORREF color)
    {
        double dx = (x2 - x1)*1.0;
        double dy = (y2 - y1)*1.0;
        if (abs(dy) <= abs(dx))
        {
            if (x1 > x2)
                swap(x1,x2), swap(y1,y2);
            Draw::drawPixel(hdc,x1,y1,color);
            int x = x1;
            double y;
            while (x < x2)
            {
                x++;
                y = y1 + (x - x1) * (dy/dx);
                Draw::drawPixel(hdc,x,y,color);
            }
        }
        else
        {
            if(y1 > y2)
                swap(x1,x2),swap(y1,y2);
            Draw::drawPixel(hdc,x1,y1,color);
            int y = y1;
            double x;
            while (y < y2)
            {
                y++;
                x = x1 + (y - y1)*(dx/dy);
                Draw::drawPixel(hdc,x,y,color);
            }

        }
    }
    Point getInPoint() override
    {
        return Point(0,0);
    }
    void parametric(HDC &hdc, COLORREF color)
    {
        for (double t = 0; t < 1; t+=0.001) {
            int x=  x1 + t*(x2 - x1);
            int y = y1 + t*(y2 - y1);
            Draw::drawPixel(hdc,x,y,color);
        }
    }
public:
    int x1,y1,x2,y2;
    Line(int x1, int y1, int x2, int y2)
    {
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
    }
    void draw(HDC &hdc,int method, COLORREF color) override
    {
        switch (method) {
            case PARAMETRIC_LINE:
                parametric(hdc,color);
                break;
            case DDA_LINE:
                dda(hdc,color);
                break;
            case MIDPOINT_LINE:
                midPoint(hdc,color);
                break;
        }
    }
};


#endif //GRAPHICSPROJECT_LINE_H
