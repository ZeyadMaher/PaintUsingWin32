cmake_minimum_required(VERSION 3.19)
project(GraphicsProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(GraphicsProject main.cpp Shape.h Circle.h Draw.h Point.h INPUT.h Line.h all_includes.h RectSquare.h ClippingOperation.h ClippingPointSqRct.h ClippingPointCircle.h ClippingLineRectSq.h ClippingLineCircle.h Polygon.h ClippingPolygonRect.h Elipse.h)