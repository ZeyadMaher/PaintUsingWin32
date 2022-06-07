//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_CLIPPINGPOLYGONRECT_H
#define GRAPHICSPROJECT_CLIPPINGPOLYGONRECT_H
#include "ClippingOperation.h"
#include "Polygon.h"
#include "RectSquare.h"
class ClippingPolygonRect : public ClippingOperation{
    void vIntersect(Line line, int xedge, int &x,int &y)
    {
        double z = ((double)(line.y2 - line.y1)/(double)(line.x2 - line.x1));
        double yres = (double)line.y1 +  (double)(xedge - line.x1) * z;
        y = yres;
        x = xedge;
    }
    void hIntersect(Line line, int yedge, int &x,int &y)
    {
        double z = ((double)(line.x2 - line.x1)/(double)(line.y2 - line.y1));
        double xres = ((double)line.x1 +  (double)(yedge - line.y1) * z);
        x = xres;
        y = yedge;
    }
    void clipLeft()
    {
        vector<Point> points;
        map<int,int> point;
        for (int i = 0; i < poPoints.size(); ++i) {
            if (poPoints[i].x < xl)
                point[i] = 0;
            else
                point[i] = 1;
        }
        int n = poPoints.size()-1;
        if (!point[n] && point[0])
        {
            int xin,yin;
            vIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),xl,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
            points.push_back(poPoints[0]);
        }
        else if (point[n] && !point[0])
        {
            int xin,yin;
            vIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),xl,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
        }
        else if(point[n] && point[0])
            points.push_back(poPoints[0]);
        for (int i = 0; i < n; ++i) {
            if (!point[i] && point[i + 1])
            {
                int xin,yin;
                vIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),xl,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
                points.push_back(poPoints[i + 1]);
            }
            else if (point[i] && !point[i + 1])
            {
                int xin,yin;
                vIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),xl,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
            }
            else if(point[i] && point[i + 1])
                points.push_back(poPoints[i + 1]);
        }
        poPoints = points;
    }
    void clipRight()
    {
        vector<Point> points;
        map<int,int> point;
        for (int i = 0; i < poPoints.size(); ++i) {
            if (poPoints[i].x > xr)
                point[i] = 0;
            else
                point[i] = 1;
        }
        int n = poPoints.size()-1;
        if (!point[n] && point[0])
        {
            int xin,yin;
            vIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),xr,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
            points.push_back(poPoints[0]);
        }
        else if (point[n] && !point[0])
        {
            int xin,yin;
            vIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),xr,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
        }
        else if(point[n] && point[0])
            points.push_back(poPoints[0]);
        for (int i = 0; i < n; ++i) {
            if (!point[i] && point[i + 1])
            {
                int xin,yin;
                vIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),xr,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
                points.push_back(poPoints[i + 1]);
            }
            else if (point[i] && !point[i + 1])
            {
                int xin,yin;
                vIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),xr,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
            }
            else if(point[i] && point[i + 1])
                points.push_back(poPoints[i + 1]);
        }
        poPoints = points;
    }
    void clipTop()
    {
        vector<Point> points;
        map<int,int> point;
        for (int i = 0; i < poPoints.size(); ++i) {
            if (poPoints[i].y < yb)
                point[i] = 0;
            else
                point[i] = 1;
        }
        int n = poPoints.size()-1;
        if (!point[n] && point[0])
        {
            int xin,yin;
            hIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),yb,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
            points.push_back(poPoints[0]);
        }
        else if (point[n] && !point[0])
        {
            int xin,yin;
            hIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),yb,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
        }
        else if(point[n] && point[0])
            points.push_back(poPoints[0]);
        for (int i = 0; i < n; ++i) {
            if (!point[i] && point[i + 1])
            {
                int xin,yin;
                hIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),yb,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
                points.push_back(poPoints[i + 1]);
            }
            else if (point[i] && !point[i + 1])
            {
                int xin,yin;
                hIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),yb,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
            }
            else if(point[i] && point[i + 1])
                points.push_back(poPoints[i + 1]);
        }
        poPoints = points;
    }
    void clipBottom()
    {
        vector<Point> points;
        map<int,int> point;
        for (int i = 0; i < poPoints.size(); ++i) {
            if (poPoints[i].y > yt)
                point[i] = 0;
            else
                point[i] = 1;
        }
        int n = poPoints.size()-1;
        if (!point[n] && point[0])
        {
            int xin,yin;
            hIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),yt,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
            points.push_back(poPoints[0]);
        }
        else if (point[n] && !point[0])
        {
            int xin,yin;
            hIntersect(Line(poPoints[n].x,poPoints[n].y,poPoints[0].x,poPoints[0].y),yt,xin,yin);
            Point in = Point(xin,yin, RGB(0,0,0));
            points.push_back(in);
        }
        else if(point[n] && point[0])
            points.push_back(poPoints[0]);
        for (int i = 0; i < n; ++i) {
            if (!point[i] && point[i + 1])
            {
                int xin,yin;
                hIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),yt,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
                points.push_back(poPoints[i + 1]);
            }
            else if (point[i] && !point[i + 1])
            {
                int xin,yin;
                hIntersect(Line(poPoints[i].x,poPoints[i].y,poPoints[i + 1].x,poPoints[i + 1].y),yt,xin,yin);
                Point in = Point(xin,yin, RGB(0,0,0));
                points.push_back(in);
            }
            else if(point[i] && point[i + 1])
                points.push_back(poPoints[i + 1]);
        }
        poPoints = points;
    }
public:
    vector<Point> poPoints;
    int xl,xr,yb,yt;
    ClippingPolygonRect(RectSquare rs, Polygonn polygonn)
    {
        xl = rs.getXl();
        xr = rs.getXr();
        yb = rs.getYb();
        yt = rs.getYt();
        poPoints = polygonn.points;
    }
    void clip(HDC &hdc, COLORREF color) override
    {
        clipLeft();
        clipRight();
        clipBottom();
        clipTop();
        (Polygonn(poPoints)).draw(hdc,DDA_LINE,color);
    }

};


#endif //GRAPHICSPROJECT_CLIPPINGPOLYGONRECT_H
