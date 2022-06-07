//
// Created by dell on ٣٠/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_DRAW_H
#define GRAPHICSPROJECT_DRAW_H
#include "windows.h"
#include "Point.h"
#include <math.h>
#include "Shape.h"
#include <vector>
using namespace std;
class Draw{
public:
    virtual void abstract() = 0;
    static void drawPixel(HDC & hdc,int x,int y, COLORREF color)
    {
        SetPixel(hdc,x,y,color);
    }
    static void draw8Pixels(HDC &hdc,int xc, int yc, int x, int y,COLORREF color)
    {
        SetPixel(hdc,x + xc, y + yc,color);
        SetPixel(hdc,-x + xc, y + yc,color);
        SetPixel(hdc,x + xc, -y + yc,color);
        SetPixel(hdc,-x + xc, -y + yc,color);
        SetPixel(hdc,y + xc, x + yc,color);
        SetPixel(hdc,-y + xc, x + yc,color);
        SetPixel(hdc,-y + xc, -x + yc,color);
        SetPixel(hdc,y + xc, -x + yc,color);
    }
    static void drawQuarterCircle(HDC &hdc,int xc, int yc, int x, int y,COLORREF color, int quarter)
    {
        switch (quarter) {
            case 1:
                SetPixel(hdc,x + xc, y + yc,color);
                SetPixel(hdc,y + xc, x + yc,color);
                break;
            case 2:
                SetPixel(hdc,x + xc, -y + yc,color);
                SetPixel(hdc,y + xc, -x + yc,color);
                break;
            case 3:
                SetPixel(hdc,-y + xc, -x + yc,color);
                SetPixel(hdc,-x + xc, -y + yc,color);
                break;
            case 4:
                SetPixel(hdc,-x + xc, y + yc,color);
                SetPixel(hdc,-y + xc, x + yc,color);
                break;
        }
    }
    static vector<Point> getQuarterCircle(int xc, int yc, int x, int y,COLORREF color, int quarter)
    {
        vector<Point> qpts;
        switch (quarter) {
            case 1:
                qpts.push_back(Point(x + xc, y + yc,color));
                qpts.push_back(Point(y + xc, x + yc,color));
                break;
            case 2:
                qpts.push_back(Point(x + xc, -y + yc,color));
                qpts.push_back(Point(y + xc, -x + yc,color));
                break;
            case 3:
                qpts.push_back(Point(-y + xc, -x + yc,color));
                qpts.push_back(Point(-x + xc, -y + yc,color));
                break;
            case 4:

                qpts.push_back(Point(-x + xc, y + yc,color));
                qpts.push_back(Point(-y + xc, x + yc,color));
                break;
        }
        return qpts;
    }
    static void DrawHermiteCurve(HDC hdc, Point p1, Point T1, Point p2, Point T2, COLORREF c)
    {
        double a0 = p1.x, a1 = T1.x,
                a2 = -3 * p1.x - 2 * T1.x + 3 * p2.x - T2.x,
                a3 = 2 * p1.x + T1.x - 2 * p2.x + T2.x;
        double b0 = p1.y, b1 = T1.y,
                b2 = -3 * p1.y - 2 * T1.y + 3 * p2.y - T2.y,
                b3 = 2 * p1.y + T1.y - 2 * p2.y + T2.y;
        for (double t = 0; t <= 1; t += 0.001)
        {
            double t2 = t * t, t3 = t2 * t;
            double x = a0 + a1 * t + a2 * t2 + a3 * t3;
            double y = b0 + b1 * t + b2 * t2 + b3 * t3;
            drawPixel(hdc, x, y, c);
        }
    }
    static void DrawBezierCurve(HDC hdc, Point& P0, Point& P1, Point& P2, Point& P3,COLORREF c)
    {
        Point T0(3 * (P1.x - P0.x), 3 * (P1.y - P0.y));
        Point T1(3 * (P3.x - P2.x), 3 * (P3.y - P2.y));
        DrawHermiteCurve(hdc, P0, T0, P3, T1, c);
    }
    static void FloodFillNR(Shape &shape,COLORREF BC,HDC &hdc,COLORREF FC)
    {
        stack <Point> st;//last in first out
        st.push(shape.getInPoint());
        while(!st.empty())
        {
            Point p=st.top();
            st.pop();
            COLORREF c= GetPixel(hdc, p.x,p.y );
            if (c==BC ||c==FC)
            {
                continue;
            }
            SetPixel(hdc,p.x,p.y,FC);
            st.push(Point(p.x+ 1,p.y));
            st.push(Point(p.x,p.y - 1));
            st.push(Point(p.x-1,p.y));
            st.push(Point(p.x,p.y + 1));
        }
    }
    static void DrawCardinalSpline(HDC &hdc,Point P[],int n,int c,COLORREF C) {
        double c1 = c / 2;
        Point T[n];
        for (int i = 1; i < n - 1; i++) {

            T[i].x = c1 * (P[i + 1].x - P[i - 1].x);
            T[i].y = c1 * (P[i + 1].y - P[i - 1].y);
        }
        T[0].x = c1 * (P[1].x - P[0].x);
        T[0].y = c1 * (P[1].y - P[0].y);

        T[n - 1].x = c1 * (P[n - 1].x - P[n - 2].x);
        T[n - 1].y = c1 * (P[n - 1].y - P[n - 2].y);
        for (int i = 0; i < n - 1; i++) {
            DrawHermiteCurve(hdc, P[i], T[i], P[i + 1], T[i + 1], C);
        }
    }
    static void FloodFillRR(Shape &shape, COLORREF BC, HDC &hdc, COLORREF FC) {
        FloodFillR(shape,BC,hdc,FC,shape.getInPoint());
    }

    static void FloodFillR(Shape &shape,COLORREF BC,HDC &hdc,COLORREF FC, Point p)
    {

            COLORREF c= GetPixel(hdc, p.x,p.y );
            if (c==BC ||c==FC)
                return;
            SetPixel(hdc,p.x,p.y,FC);
            FloodFillR(shape,BC,hdc,FC,(Point(p.x+1,p.y)));
            FloodFillR(shape,BC,hdc,FC,(Point(p.x,p.y - 1)));
            FloodFillR(shape,BC,hdc,FC,(Point(p.x-1,p.y)));
            FloodFillR(shape,BC,hdc,FC,(Point(p.x,p.y + 1)));

    }
    static void draw4Pixels(HDC &hdc,int xc, int yc, int a, int b, COLORREF c)
    {
        SetPixel(hdc, xc + a, yc + b, c);
        SetPixel(hdc, xc + a, yc - b, c);
        SetPixel(hdc, xc - a, yc + b, c);
        SetPixel(hdc, xc - a, yc - b, c);
    }
    static int calculateDistance(int x1, int y1, int x2, int y2)
    {
        double dist = sqrt(pow(x2-x1,2.0) + pow(y2 - y1,2.0));
        return round(dist);
    }
};


#endif //GRAPHICSPROJECT_DRAW_H
