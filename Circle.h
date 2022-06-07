//
// Created by dell on ٣٠/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_CIRCLE_H
#define GRAPHICSPROJECT_CIRCLE_H
#include "Shape.h"
#include "Draw.h"
#include "Line.h"
#include "INPUT.h"
class Circle : public Shape{
    void drawQuarterCircle(HDC &hdc, COLORREF color, int quarter,int R)
    {
        int x = 0, y = R;
        int d = 1 - R;
        int c1 = 3, c2 = 5 - 2 * R;
        Draw::drawQuarterCircle(hdc, xc, yc, x, y, color,quarter);
        while (x < y)
        {
            if (d < 0)
            {
                d += c1;
                c2 += 2;
            }
            else
            {
                d += c2;
                c2 += 4;
                y--;
            }
            c1 += 2;
            x++;
            Draw::drawQuarterCircle(hdc, xc, yc, x, y, color,quarter);
        }
    }
    void direct(HDC &hdc, COLORREF color)
    {
        int x = 0;
        int y = R;
        Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        while (x < y)
        {
            x++;
            y = sqrt((double)R*R - x*x);
            Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        }
    }
    void polar(HDC &hdc, COLORREF color)
    {
        double x = R;
        double y = 0;
        double theta = 0.0;
        Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        while (x > y)
        {
            theta+=(1.0/R);
            x = R* cos(theta);
            y = R* sin(theta);
            Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        }
    }
    void iterativePolar(HDC &hdc, COLORREF color)
    {
        double x = R;
        double y = 0;
        double dtheta = 1.0/R;
        double ct = cos(dtheta);
        double st = sin(dtheta);
        Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        while (x > y)
        {
            double  x1 = x*ct - y*st;
            y = x*st + y*ct;
            x = x1;
            Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        }
    }
    void midpoint(HDC &hdc, COLORREF color)
    {
        int x = 0;
        int y = R;
        int d = 1 - R;
        Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        while (x < y)
        {
            if(d < 0)
                d+=2*x + 3,x++;
            else
                d+=2*(x-y) + 5, x++,y--;
            Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        }
    }
    void modifiedMidpoint(HDC &hdc, COLORREF color)
    {
        int x = 0, y = R, d = 1 - R, d1 = 3, d2 = 5 - (2*R);
        Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        while (x < y)
        {
            if (d < 0)
                d+=d1,d2+=2,d1+=2,x++;
            else
                d+=d2,d2+=4,d1+=2,x++,y--;
            Draw::draw8Pixels(hdc,xc,yc,x,y,color);
        }
    }
public:
    int xc;
    int yc;
    int R;
    Circle(int xc, int yc, int R)
    {
        this->xc = xc;
        this->yc = yc;
        this->R = R;
    }
    void draw(HDC &hdc, int method, COLORREF color) override
    {
        this->BC = color;
        switch (method) {
            case MIDPOINT_CIRCLE:
                midpoint(hdc,color);
                break;
            case DIRECT_CIRCLE:
                direct(hdc,color);
                break;
            case POLAR_CIRCLE:
                polar(hdc,color);
                break;
            case ITERATIVE_POLAR_CIRCLE:
                iterativePolar(hdc,color);
                break;
            case MODIFIED_MIDPOINT_CIRCLE:
                modifiedMidpoint(hdc,color);
                break;
        }
    }
    Point getInPoint() override
    {
        return Point(xc,yc);
    }
    void FillCircleCircles(HDC &hdc,COLORREF color,int quarter, double step = 0.5) {
        drawQuarterCircle(hdc, color,quarter,R);
        for (double i = R; i > 0; i -= step) {
            drawQuarterCircle(hdc,color,quarter,i);
        }
    }
    void FillCircleLines(HDC &hdc, COLORREF color,int quarter)
    {
        int x = 0, y = R, d = 1 - R, d1 = 3, d2 = 5 - (2*R);
        vector<Point> points = Draw::getQuarterCircle(xc,yc,x,y,color,quarter);
        Line line = Line(xc,yc,points[1].x,points[1].y);
        line.draw(hdc,DDA_LINE,color);
        line = Line(xc,yc,points[0].x,points[0].y);
        line.draw(hdc,DDA_LINE,color);
        while (x < y)
        {
            if (d < 0)
                d+=d1,d2+=2,d1+=2,x++;
            else
                d+=d2,d2+=4,d1+=2,x++,y--;
            vector<Point> points = Draw::getQuarterCircle(xc,yc,x,y,color,quarter);
            Line line =  Line(xc,yc,points[1].x,points[1].y);
            line.draw(hdc,DDA_LINE,color);
            line =  Line(xc,yc,points[0].x,points[0].y);
            line.draw(hdc,DDA_LINE,color);
        }
    }

};


#endif //GRAPHICSPROJECT_CIRCLE_H
