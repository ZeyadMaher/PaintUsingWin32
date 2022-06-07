//
// Created by dell on ٣٠/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_SHAPE_H
#define GRAPHICSPROJECT_SHAPE_H
#include<windows.h>
class Shape {
public:
    COLORREF BC;
    virtual void draw(HDC &hdc, int method, COLORREF color) = 0;
    virtual Point getInPoint() = 0;
};


#endif //GRAPHICSPROJECT_SHAPE_H
