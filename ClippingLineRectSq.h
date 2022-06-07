//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_CLIPPINGLINERECTSQ_H
#define GRAPHICSPROJECT_CLIPPINGLINERECTSQ_H

#include "ClippingOperation.h"
#include "Shape.h"
#include "Line.h"
#include "RectSquare.h"
#include "ClippingOperation.h"
#include <iostream>
using namespace std;
union outcode
{
    unsigned All:4;
    struct {unsigned left:1, right:1, bottom:1, top:1;};
};
class ClippingLineRectSq: public ClippingOperation{
   outcode getOutCode(int x,int y)
   {
       outcode r; r.All = 0;
       if (x < xl) r.left = 1; else if(x > xr) r.right = 1;
       if(y < yb) r.top = 1; else if (y > yt) r.bottom = 1;
       return r;
   }
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
    bool cohen(Line &line)
    {
       outcode code1 = getOutCode(line.x1,line.y1);
       outcode code2 = getOutCode(line.x2,line.y2);
       while (true)
       {
           if (code1.All & code2.All)
               return false;
           if (!code1.All && !code2.All)
               return true;
           if (code1.All)
           {
               if (code1.left) vIntersect(line,xl,line.x1,line.y1);
               else if(code1.right) vIntersect(line,xr,line.x1,line.y1);
               else if (code1.bottom) hIntersect(line,yt,line.x1,line.y1);
               else hIntersect(line,yb,line.x1,line.y1);
               code1 = getOutCode(line.x1,line.y1);
           }
           else
           {
               if (code2.left) vIntersect(line,xl,line.x2,line.y2);
               else if(code2.right) vIntersect(line,xr,line.x2,line.y2);
               else if (code2.bottom) hIntersect(line,yt,line.x2,line.y2);
               else hIntersect(line,yb,line.x1,line.x2);
               code2 = getOutCode(line.x2,line.y2);
           }
       }
    }
public:
    vector<Line> lines;
    int xl,xr,yb,yt;
    ClippingLineRectSq(RectSquare rs, vector<Line> lines)
    {
        this->xl = rs.getXl();
        this->xr = rs.getXr();
        this->yb = rs.getYb();
        this->yt = rs.getYt();
        this->lines = lines;
    }
    void clip(HDC &hdc, COLORREF color) override
    {
        for (int i = 0; i < lines.size(); ++i) {
            if (cohen(lines[i]))
                lines[i].draw(hdc,DDA_LINE,color);
        }
    }
    vector<Line> getInLines()
    {
        vector<Line> inLines;
        for (int i = 0; i < lines.size(); ++i) {
            if (cohen(lines[i])) inLines.push_back(lines[i]);
        }
        return inLines;
    }
};


#endif //GRAPHICSPROJECT_CLIPPINGLINERECTSQ_H
