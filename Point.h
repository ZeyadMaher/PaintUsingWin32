//
// Created by dell on ٣٠/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_POINT_H
#define GRAPHICSPROJECT_POINT_H
#include "windows.h"
class Point {
public:
    int x;
    int y;
    COLORREF color;
    Point(int x, int y, COLORREF color)
    {
        this->x = x;
        this->y = y;
        this->color = color;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Point()
    {

    }
};


#endif //GRAPHICSPROJECT_POINT_H
