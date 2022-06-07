//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_RECTSQUARE_H
#define GRAPHICSPROJECT_RECTSQUARE_H

#include "windows.h"
#include "Shape.h"
#include "Line.h"
class RectSquare : public Shape{
public:
    int l,w,xs,ys;
    RectSquare(int xs, int ys, int l, int w)
    {
        this->xs = xs;
        this->ys = ys;
        this->l = l;
        this->w = w;
    }
    void draw(HDC &hdc, int method, COLORREF color)
    {
        this->BC = color;
        Line line1 = Line(xs,ys,xs + w, ys);
        line1.draw(hdc,method,color);

        Line line2 = Line(xs,ys,xs, ys + l);
        line2.draw(hdc,method,color);

        Line line3 = Line(xs + w,ys + l,xs + w, ys);
        line3.draw(hdc,method,color);

        Line line4 = Line(xs + w,ys + l,xs, ys + l);
        line4.draw(hdc,method,color);
    }
    void FillSquareHermite(HDC hdc, COLORREF c) {
        int x = xs,y = ys;
        int xe = xs + w;
        int ye = ys + l;
        double arm = abs(xe - x);
        if (ye != 0) {
            for (double i = x; i <= x + arm; i += 1) {
                vector<Point> p;
                p.push_back(Point(i, y));
                p.push_back(Point(i, y + .25 * y));
                p.push_back(Point(i, (y + arm) - (y + arm) * .25));
                p.push_back(Point(i, y + arm));
                Point T1(3 * (p[1].x - p[0].x), 3 * (p[1].y - p[0].y));
                Point T2(3 * (p[3].x - p[2].x), 3 * (p[3].y - p[2].y));
                Draw::DrawHermiteCurve(hdc,p[0], T1, p[3], T2, c);
            }
        }
    }

    void FillRecBezier(HDC hdc,COLORREF FC) {

        vector<Point> p;
        for (int i = 0; i < 4; ++i) {
            p.push_back(Point(1,1));
        }

        p[0].y = ys + l-1;
        p[1].y = ys + l-1;
        p[2].y = ys+1;
        p[3].y = ys+1;

        int x1 = xs+1;
        while (x1 < xs + w)
        {
            p[0].x = x1;
            p[1].x = x1;
            p[2].x = x1;
            p[3].x = x1;

            Draw::DrawBezierCurve(hdc, p[0], p[1], p[2], p[3], FC);
            x1++;
        }

    }
    Point getInPoint() override
    {
        return Point(xs + (w/2),ys + (l / 2));
    }
    int getXl()
    {
        return xs;
    }
    int getXr()
    {
        return xs + w;
    }
    int getYb()
    {
        return ys;
    }
    int getYt()
    {
        return ys + l;
    }
};


#endif //GRAPHICSPROJECT_RECTSQUARE_H
