//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_ELIPSE_H
#define GRAPHICSPROJECT_ELIPSE_H

#include "Shape.h"
#include "INPUT.h"
#include "Draw.h"
class Elipse : public Shape{
    void direct(HDC hdc, COLORREF c) {
        int x = 0;
        double y = b;
        Draw::draw4Pixels(hdc, xc, yc, 0, b, c);
        while (x * b * b < y * a * a) {
            x++;
            y = b * sqrt(1.0 - (double) x * x / (a * a));
            Draw::draw4Pixels(hdc, xc, yc, x, y, c);
        }

        int y1 = 0;
        double x1 = a;
        Draw::draw4Pixels(hdc, xc, yc, a, 0, c);
        while (x1 * b * b > y1 * a * a) {
            y1++;
            x1 = a * sqrt(1.0 - (double) y1 * y1 / (b * b));
            Draw::draw4Pixels(hdc, xc, yc,x1, y1, c);
        }
    }
    void midPointEllipse(HDC &hdc, int B, int A, COLORREF c)
    {
        float dx, dy, d1, d2, x, y;
        x = 0;
        y = A;

        // Initial decision parameter of region 1
        d1 = (A * A) - (B * B * A) +
             (0.25 * B * B);
        dx = 2 * A * A * x;
        dy = 2 * B * B * y;

        // For region 1
        while (dx < dy)
        {

            // Print points based on 4-way symmetA
            Draw::draw4Pixels(hdc, xc, yc, x, y, c);

            // Checking and updating value of
            // decision parameter based on algorithm
            if (d1 < 0)
            {
                x++;
                dx = dx + (2 * A * A);
                d1 = d1 + dx + (A * A);
            }
            else
            {
                x++;
                y--;
                dx = dx + (2 * A * A);
                dy = dy - (2 * B * B);
                d1 = d1 + dx - dy + (A * A);
            }
        }

        // Decision parameter of region 2
        d2 = ((A * A) * ((x + 0.5) * (x + 0.5))) +
             ((B * B) * ((y - 1) * (y - 1))) -
             (B * B * A * A);

        // Plotting points of region 2
        while (y >= 0)
        {
            Draw::draw4Pixels(hdc, xc, yc, x, y, c);

            // Print points based on 4-way symmetA

            // Checking and updating parameter
            // value based on algorithm
            if (d2 > 0)
            {
                y--;
                dy = dy - (2 * B * B);
                d2 = d2 + (B * B) - dy;
            }
            else
            {
                y--;
                x++;
                dx = dx + (2 * A * A);
                dy = dy - (2 * B * B);
                d2 = d2 + dx - dy + (B * B);
            }
        }
    }
    void polar(HDC &hdc, COLORREF color)
    {
        double theta = 0.0, endTheta = 90.0;
        while (theta <= endTheta)
        {
            int x = (a* cos(theta));
            int y = (b * sin(theta));
            Draw::draw4Pixels(hdc,xc,yc,x,y,color);
            theta+=0.01;
        }
    }
    public:
        int xc,yc,a,b;
    Point getInPoint() override
    {
        return Point(xc,yc);
    }
    void draw(HDC &hdc, int method, COLORREF color) override
    {
        this->BC = color;
        switch (method) {
            case ELIPSE_DIRECT:
                direct(hdc,color);
                break;
            case MIDPOINT_ELIPSE:
                midPointEllipse(hdc,a,b,color);
                break;
            case POLAR_ELIPSE:
                polar(hdc,color);
                break;
        }
    }
    Elipse(int xc, int yc, int a, int b)
    {
        this->xc = xc;
        this->yc = yc;
        this->a = a;
        this->b = b;
    }
};


#endif //GRAPHICSPROJECT_ELIPSE_H
