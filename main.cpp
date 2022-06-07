#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include "Draw.h"
#include "Shape.h"
#include "Circle.h"
#include "INPUT.h"
#include "Point.h"
#include "Line.h"
#include <thread>
#include "RectSquare.h"
#include "ClippingOperation.h"
#include "ClippingPointSqRct.h"
#include "ClippingPointCircle.h"
#include "ClippingLineRectSq.h"
#include "ClippingLineCircle.h"
#include "Polygon.h"
#include "ClippingPolygonRect.h"
#include "Elipse.h"
#include <commdlg.h>
#include <cstdio>
using namespace std;
void AddControls(HWND hWnd);
HWND hMainWindow, hEdit;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HDC hdc;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
void clear()
{
    RECT    rcCli;
    GetClientRect(WindowFromDC(hdc), &rcCli);
    int nWidth = rcCli.right-rcCli.left;
    int nHeight  = rcCli.bottom-rcCli.top;
    for (int x = 0; x <= nWidth; ++x) {
        for (int y = 0; y <= nHeight ; ++y) {
            Draw::drawPixel(hdc,x,y, RGB(255,255,255));
        }
    }
}
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;
    /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    wincl.hbrBackground = brush;
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Code::Blocks Template Windows App"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            500,                 /* The programs width */
            500,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    hdc = GetDC(hwnd);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
void addMenus(HWND &hwnd) {
    hMenu = CreateMenu();

    HMENU file = CreateMenu();
    AppendMenu(file, MF_STRING, Save_FILE_BUTTON, "Save");
    AppendMenu(file, MF_STRING, OPEN_FILE_BUTTON, "Load");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) file, "File");

    HMENU colors = CreateMenu();
    AppendMenu(colors, MF_STRING, RED, "Red");
    AppendMenu(colors, MF_STRING, BLACK, "Black");
    AppendMenu(colors, MF_STRING, YELLOW, "Yellow");
    AppendMenu(colors, MF_STRING, PURPLE, "Purple");
    AppendMenu(colors, MF_STRING, GREEN, "Green");
    AppendMenu(colors, MF_STRING, BLUE, "Blue");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) colors, "Colors");

    HMENU circle = CreateMenu();
    AppendMenu(circle, MF_STRING, MIDPOINT_CIRCLE, "Midpoint");
    AppendMenu(circle, MF_STRING, MODIFIED_MIDPOINT_CIRCLE, "Modified Midpoint");
    AppendMenu(circle, MF_STRING, DIRECT_CIRCLE, "Direct");
    AppendMenu(circle, MF_STRING, POLAR_CIRCLE, "Polar");
    AppendMenu(circle, MF_STRING, ITERATIVE_POLAR_CIRCLE, "ITERATIVE POLAR");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) circle, "Circle");

    HMENU line = CreateMenu();
    AppendMenu(line, MF_STRING, MIDPOINT_LINE, "Midpoint");
    AppendMenu(line, MF_STRING, DDA_LINE, "DDA");
    AppendMenu(line, MF_STRING, PARAMETRIC_LINE, "Parametric");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) line, "Line");

    HMENU elipse = CreateMenu();
    AppendMenu(elipse, MF_STRING, MIDPOINT_ELIPSE, "Midpoint");
    AppendMenu(elipse, MF_STRING, ELIPSE_DIRECT, "Direct");
    AppendMenu(elipse, MF_STRING, POLAR_ELIPSE, "Polar Elipse");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) elipse, "Elipse");

    HMENU clipping = CreateMenu();
    AppendMenu(clipping, MF_STRING, CLIPPING_WINDOW_POINT, "Window Point");
    AppendMenu(clipping, MF_STRING, CLIPPING_WINDOW_LINE, "Window Line");
    AppendMenu(clipping, MF_STRING, CLIPPING_WINDOW_POLYGON, "Window Polygon");
    AppendMenu(clipping, MF_STRING, CLIPPING_CIRCLE_POINT, "Circle Point");
    AppendMenu(clipping, MF_STRING, CLIPPING_CIRCLE_LINE, "Circle Line");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) clipping, "Clipping");

    HMENU filling = CreateMenu();
    AppendMenu(filling, MF_STRING, FILLING_CIRCLE_LINES, "Circle Lines");
    AppendMenu(filling, MF_STRING, FILLING_CIRCLE_circles, " Circle circles");
    AppendMenu(filling, MF_STRING, FILLING_RECTANGLE_BEZIER, "Rectangle Bezier");
    AppendMenu(filling, MF_STRING, FILLING_SQUARE_HERMIT, "Square Hermite");
    AppendMenu(filling, MF_STRING, FILLING_GENERAL_POLYGON, "General Polygon");
    AppendMenu(filling, MF_STRING, FILLING_CONVEX, "Convex");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) filling, "Filling");

    HMENU quarted = CreateMenu();
    AppendMenu(quarted, MF_STRING, QUARTER_1, "1");
    AppendMenu(quarted, MF_STRING, QUARTER_2, "2");
    AppendMenu(quarted, MF_STRING, QUARTER_3, "3");
    AppendMenu(quarted, MF_STRING, QUARTER_4, "4");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) quarted, "Quarter");

    HMENU floodfilling = CreateMenu();
    AppendMenu(floodfilling, MF_STRING, FILLING_R_FLOODFILL_R, "Rectangle Recursive Flood Fill");
    AppendMenu(floodfilling, MF_STRING, FILLING_NR_FLOODFILL_R, "Rectangle non Recursive Flood Fill");
    AppendMenu(floodfilling, MF_STRING, FILLING_R_FLOODFILL_C, "Circle Recursive Flood Fill");
    AppendMenu(floodfilling, MF_STRING, FILLING_NR_FLOODFILL_C, "Circle non Recursive Flood Fill");
    AppendMenu(floodfilling, MF_STRING, FILLING_R_FLOODFILL_E, "Elipse Recursive Flood Fill");
    AppendMenu(floodfilling, MF_STRING, FILLING_NR_FLOODFILL_E, "Elipse non Recursive Flood Fill");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) floodfilling, "Flood Filling");
    AppendMenu(hMenu, MF_STRING, CLEAR, "Clear");
    AppendMenu(hMenu, MF_STRING, CARDINAL_SPLINE, "Cardinal Spline");

    SetMenu(hwnd, hMenu);
}

unsigned char* ReadBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    cout << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

            cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
        }
    }

    fclose(f);
    return data;
}

void display_file(char* path){
    ifstream file;
    file.open(path);
    RECT    rcCli;
    GetClientRect(WindowFromDC(hdc), &rcCli);
    int nWidth = rcCli.right-rcCli.left;
    int nHeight  = rcCli.bottom-rcCli.top;
    for (int x = 0; x <= nWidth; ++x) {
        for (int y = 0; y <= nHeight ; ++y) {
            COLORREF c ;

            file >> c;


            Draw::drawPixel(hdc,x,y,c);
        }
    }
}

void open_file(HWND hWnd){
    OPENFILENAME ofn;
    char file_name[100];
    ZeroMemory(&ofn,sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0]='\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source File\0*.CPP\0Text Files\0*.txt\0";
    ofn.nFilterIndex = 1; //default option

    if (GetOpenFileNameA( &ofn ))
    {std::cout << "You chose the file \"" << file_name << "\"\n";}

    display_file(ofn.lpstrFile);
}




void write_file(char* path){
    ofstream file;
    file.open(path);
    RECT    rcCli;
    GetClientRect(WindowFromDC(hdc), &rcCli);
    int nWidth = rcCli.right-rcCli.left;
    int nHeight  = rcCli.bottom-rcCli.top;
    for (int x = 0; x <= nWidth; ++x) {
        for (int y = 0; y <= nHeight ; ++y) {
            COLORREF c= GetPixel(hdc, x,y );
            file << c << endl;
        }
    }
    file.close();
}

void save_file(HWND hWnd){
    OPENFILENAME ofn;
    char file_name[100];

    ZeroMemory(&ofn,sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0]='\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source File\0*.CPP\0Text Files\0*.txt\0";
    ofn.nFilterIndex = 1; //default option

    if (GetSaveFileNameA( &ofn ))
    {std::cout << "You Saved the file \"" << file_name << "\"\n";}

    HDC hdc = GetDC(hWnd);
    write_file(ofn.lpstrFile);
}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static vector<Point> points;
    static int numberOfPoints;
    static int input = NOINPUT;
    static COLORREF color = RGB(255,0,0);
    static RectSquare window = RectSquare(0,0,0,0);
    static Circle c = Circle(0,0,0);
    static int quarter = 1;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            addMenus(hwnd);
            break;
        case WM_COMMAND:
        {
            switch (wParam) {
                case CLEAR:
                    clear();
                    break;
                case Save_FILE_BUTTON:
                    save_file(hwnd);
                    break;
                case OPEN_FILE_BUTTON:
                    open_file(hwnd);
                    break;
                case MIDPOINT_CIRCLE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case CARDINAL_SPLINE:
                {
                    cout << "click 5 points " << endl;
                    numberOfPoints = 5;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_CONVEX:
                    cout << "enter 6 clicks to form a polygon" << endl;
                    numberOfPoints=6;
                    input = wParam;
                    points.clear();
                    break;
                case ITERATIVE_POLAR_CIRCLE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case MODIFIED_MIDPOINT_CIRCLE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case POLAR_CIRCLE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case DIRECT_CIRCLE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case DDA_LINE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case MIDPOINT_LINE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case PARAMETRIC_LINE:
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                case MIDPOINT_ELIPSE:
                {
                    cout << "click on 3 points center and a and b:" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case ELIPSE_DIRECT:
                {
                    cout << "click on 3 points center and a and b:" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case POLAR_ELIPSE:
                {
                    cout << "click on 3 points center and a and b:" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case CLIPPING_WINDOW_POINT:
                {
                    cout << "click on 3 points xl,yt, xr,yt, xl,yb:" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case CLIPPING_WINDOW_LINE:
                {
                    cout << "click on 3 points xl,yt xr,yt, xl,yb for window and click on 6 points each 2 points form a line" << endl;
                    numberOfPoints = 9;
                    input = wParam;
                    points.clear();
                    break;
                }
                case CLIPPING_CIRCLE_POINT:
                {
                    cout << "Please right click on two points" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                }
                case CLIPPING_CIRCLE_LINE:
                {
                    cout << "Please right click on two points then 6 points each two form a line" << endl;
                    numberOfPoints = 8;
                    input = wParam;
                    points.clear();
                    break;
                }
                case CLIPPING_WINDOW_POLYGON:
                {
                    cout << "right click on 3 points for a rectangle and then 6 points that will form a polygon" << endl;
                    numberOfPoints = 9;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_CIRCLE_LINES:
                {
                    cout << "enter two points to draw a circle" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_CIRCLE_circles:
                {
                    cout << "enter two points to draw a circle" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_RECTANGLE_BEZIER:
                {
                    cout << "enter 3 points to draw rectangle" << endl;
                    numberOfPoints= 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_SQUARE_HERMIT:
                {
                    cout << "enter 2 points for square" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_GENERAL_POLYGON:
                {
                    cout << "enter 6 points for a polygon" << endl;
                    numberOfPoints = 6;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_R_FLOODFILL_R:
                {
                    cout << "enter 3 points for a rect" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_NR_FLOODFILL_R:
                {
                    cout << "enter 3 points for a rect" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_R_FLOODFILL_C:
                {
                    cout << "enter 2 points for a circle" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_NR_FLOODFILL_C:
                {
                    cout << "enter 2 points for a circle" << endl;
                    numberOfPoints = 2;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_R_FLOODFILL_E:
                {
                    cout << "enter 3 points for an elipse" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case FILLING_NR_FLOODFILL_E:
                {
                    cout << "enter 3 points for a elipse" << endl;
                    numberOfPoints = 3;
                    input = wParam;
                    points.clear();
                    break;
                }
                case GREEN:
                    color = RGB(0,255,0);
                    break;
                case BLACK:
                    color = RGB(0,0,0);
                    break;
                case BLUE:
                    color = RGB(0,0,255);
                    break;
                case RED:
                    color = RGB(255,0,0);
                    break;
                case PURPLE:
                    color = RGB(255,0,255);
                    break;
                case YELLOW:
                    color = RGB(255,255,0);
                    break;
                case QUARTER_1:
                    quarter = 1;
                    break;
                case QUARTER_2:
                    quarter = 2;
                    break;
                case QUARTER_3:
                    quarter = 3;
                    break;
                case QUARTER_4:
                    quarter = 4;
                    break;

            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_LBUTTONDOWN:
            break;
        case WM_RBUTTONDOWN: {
            points.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
            switch (input) {
                case MIDPOINT_CIRCLE: {
                    if (points.size() == numberOfPoints)
                    {
                         c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case CARDINAL_SPLINE:
                {
                    if(points.size() == numberOfPoints)
                    {
                        Point * points2 = new Point[numberOfPoints];
                        for (int i = 0; i < points.size(); ++i) {
                            points2[i] = points[i];
                        }
                        Draw::DrawCardinalSpline(hdc,points2,5,2,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case ITERATIVE_POLAR_CIRCLE: {
                    if (points.size() == numberOfPoints)
                    {
                         c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_CONVEX:
                {
                    if (points.size() == numberOfPoints) {
                        Polygonn polygonn = Polygonn(points);
                        polygonn.draw(hdc, DDA_LINE, color);
                        Point *points2 = new Point[numberOfPoints];
                        for (int i = 0; i < points.size(); ++i) {
                            points2[i] = points[i];
                        }

                        polygonn.ConvexFill(hdc,points2,points.size(),color);
                        input = NOINPUT;
                        points.size();
                    }
                    break;
                }
                case MODIFIED_MIDPOINT_CIRCLE: {
                    if (points.size() == numberOfPoints)
                    {
                         c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case POLAR_CIRCLE: {
                    if (points.size() == numberOfPoints)
                    {
                         c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case DIRECT_CIRCLE: {
                    if (points.size() == numberOfPoints)
                    {
                        c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case DDA_LINE: {
                    if(points.size() == numberOfPoints)
                    {
                        Line l = Line(points[0].x,points[0].y,points[1].x,points[1].y);
                        l.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case MIDPOINT_LINE: {
                    if(points.size() == numberOfPoints)
                    {
                        Line l = Line(points[0].x,points[0].y,points[1].x,points[1].y);
                        l.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case PARAMETRIC_LINE: {
                    if(points.size() == numberOfPoints)
                    {
                        Line l = Line(points[0].x,points[0].y,points[1].x,points[1].y);
                        l.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case MIDPOINT_ELIPSE: {
                    if (points.size() == numberOfPoints)
                    {
                        Elipse e = Elipse(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,
                                                                                          points[1].x,points[1].y),
                                          Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y));
                        e.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case ELIPSE_DIRECT: {
                    if (points.size() == numberOfPoints)
                    {
                        Elipse e = Elipse(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,
                                                                                          points[1].x,points[1].y),
                                          Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y));
                        e.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case POLAR_ELIPSE: {
                    if (points.size() == numberOfPoints)
                    {
                        Elipse e = Elipse(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,
                                                                                          points[1].x,points[1].y),
                                          Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y));
                        e.draw(hdc,input,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case CLIPPING_WINDOW_POINT:
                {
                    if (points.size() == numberOfPoints)
                    {
                        int l = Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y);
                        int w = Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y);

                        window = RectSquare(points[0].x,points[0].y,l,w);
                        window.draw(hdc,DDA_LINE,color);
                        (ClippingPointSqRct(window)).clip(hdc,RGB(255,255,255));
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case CLIPPING_WINDOW_LINE:
                {
                    if (points.size() == numberOfPoints)
                    {
                        vector<Line> lines;
                        for (int i = 3; i < points.size(); i+=2) {
                            lines.push_back(Line(points[i].x,points[i].y,points[i + 1].x,points[i + 1].y));
                        }
                        (ClippingLineRectSq(window,lines)).clip(hdc,color);
                        points.clear();
                        input = NOINPUT;
                    } else if (points.size() == 3)
                    {
                        int l = Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y);
                        int w = Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y);
                        window = RectSquare(points[0].x,points[0].y,l,w);
                        window.draw(hdc,DDA_LINE,color);
                    }
                    break;
                }
                case CLIPPING_CIRCLE_POINT:
                {
                    if (points.size() == 2)
                    {
                        Circle c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,DIRECT_CIRCLE,color);
                        (ClippingPointCircle(c)).clip(hdc, RGB(255,255,255));
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case CLIPPING_CIRCLE_LINE:
                {
                    if (points.size() == 2)
                    {
                        c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,DIRECT_CIRCLE,color);
                    }
                    else if (points.size() == numberOfPoints)
                    {
                        vector<Line> lines;
                        for (int i = 2; i < points.size(); i+=2) {
                            lines.push_back(Line(points[i].x,points[i].y,points[i + 1].x,points[i + 1].y));
                        }
                        (ClippingLineCircle(c,lines)).clip(hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case CLIPPING_WINDOW_POLYGON:
                {
                    if (points.size() == 3)
                    {
                        int l = Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y);
                        int w = Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y);
                        window = RectSquare(points[0].x,points[0].y,l,w);
                        window.draw(hdc,DDA_LINE,color);
                    }
                    else if (points.size() == numberOfPoints)
                    {
                        vector<Point> polygonPoints;
                        for (int i = 3; i < points.size(); ++i) {
                            polygonPoints.emplace_back(points[i]);
                        }
                        Polygonn polygonn = Polygonn(polygonPoints);
                        (ClippingPolygonRect(window,polygonn)).clip(hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_CIRCLE_LINES:
                {
                    if (points.size() == numberOfPoints)
                    {
                        c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,DIRECT_CIRCLE,color);
                        c.FillCircleLines(hdc,color,quarter);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_CIRCLE_circles:
                {
                    if (points.size() == numberOfPoints)
                    {
                        c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,DIRECT_CIRCLE,color);
                        c.FillCircleCircles(hdc,color,quarter);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_RECTANGLE_BEZIER:
                {

                    if (points.size() == numberOfPoints)
                    {
                        int l = Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y);
                        int w = Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y);
                        window = RectSquare(points[0].x,points[0].y,l,w);
                        window.draw(hdc,DDA_LINE,color);
                        window.FillRecBezier(hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_SQUARE_HERMIT:
                {

                    if (points.size() == numberOfPoints)
                    {
                        int l = Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y);
                        window = RectSquare(points[0].x,points[0].y,l,l);
                        window.draw(hdc,DDA_LINE,color);
                        window.FillSquareHermite(hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_GENERAL_POLYGON:
                {
                    if (points.size() == numberOfPoints)
                    {
                        Polygonn polygonn = Polygonn(points);
                        polygonn.draw(hdc,DDA_LINE,color);
                        polygonn.GeneralPolygonFill(hdc,points.size(),color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_R_FLOODFILL_R:
                {
                    if(points.size() == numberOfPoints)
                    {
                        int l = Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y);
                        int w = Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y);
                        window = RectSquare(points[0].x,points[0].y,l,w);
                        window.draw(hdc,DDA_LINE,color);
                        Draw::FloodFillRR(window,color,hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_NR_FLOODFILL_R:
                {
                    if(points.size() == numberOfPoints)
                    {
                        int l = Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y);
                        int w = Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y);
                        window = RectSquare(points[0].x,points[0].y,l,w);
                        window.draw(hdc,DDA_LINE,color);
                        Draw::FloodFillNR(window,color,hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_R_FLOODFILL_C:
                {
                    if(points.size() == numberOfPoints)
                    {
                        c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,DIRECT_CIRCLE,color);
                        Draw::FloodFillRR(c,color,hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_NR_FLOODFILL_C:
                {
                    if(points.size() == numberOfPoints)
                    {
                        c= Circle(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,points[1].x,points[1].y));
                        c.draw(hdc,DIRECT_CIRCLE,color);
                        Draw::FloodFillNR(c,color,hdc,color);
                        points.clear();
                        input = NOINPUT;
                    }
                    break;
                }
                case FILLING_R_FLOODFILL_E:
                {
                    if(points.size() == numberOfPoints)
                    {
                        Elipse e = Elipse(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,
                                                                                          points[1].x,points[1].y),
                                          Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y));
                        e.draw(hdc,ELIPSE_DIRECT,color);
                        Draw::FloodFillRR(e,color,hdc,color);
                        points.clear();
                        input =NOINPUT;
                    }
                    break;
                }
                case FILLING_NR_FLOODFILL_E:
                {
                    if(points.size() == numberOfPoints)
                    {
                        Elipse e = Elipse(points[0].x,points[0].y,Draw::calculateDistance(points[0].x,points[0].y,
                                                                                          points[1].x,points[1].y),
                                          Draw::calculateDistance(points[0].x,points[0].y,points[2].x,points[2].y));
                        e.draw(hdc,ELIPSE_DIRECT,color);
                        Draw::FloodFillNR(e,color,hdc,color);
                        points.clear();
                        input =NOINPUT;
                    }
                    break;
                }

            }
        }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}



void AddControls(HWND hWnd){
    CreateWindowW(L"Button",L"Open File",WS_VISIBLE | WS_CHILD ,10,10,150,36,hWnd,(HMENU)OPEN_FILE_BUTTON,NULL,NULL);
    CreateWindowW(L"Button",L"Save File",WS_VISIBLE | WS_CHILD ,170,10,150,36,hWnd,(HMENU)Save_FILE_BUTTON,NULL,NULL);

    hEdit = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,10,50,400,300,hWnd,NULL,NULL,NULL);
}