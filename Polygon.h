//
// Created by dell on ٣١/٠٥/٢٠٢٢.
//

#ifndef GRAPHICSPROJECT_POLYGON_H
#define GRAPHICSPROJECT_POLYGON_H
#include "Shape.h"
#include "Point.h"
#include "INPUT.h"
#include <vector>
#include "Line.h"
#define MAXENTRIES 600
long long const MaxInteger= 1e6 + 5;
struct EdgeRecord
{
    double x;
    double mInv;
    int yMax;
    bool operator<(EdgeRecord r)
    {
        return x<r.x;
    }
};
struct Input{
    int xMin,xMax;
};
typedef list<EdgeRecord> EdgeList;

using namespace std;
class Polygonn: public Shape{
    EdgeRecord InitEdgeRec(Point& v1, Point& v2)
    {
        if(v1.y>v2.y)swap(v1,v2);
        EdgeRecord rec{};
        rec.x=v1.x;
        rec.yMax=v2.y;
        rec.mInv=(double)(v2.x-v1.x)/(v2.y-v1.y);
        return rec;
    }
    void DrawSanLines(HDC hdc, Input table[], COLORREF color)
    {
        for(int y=0;y<MAXENTRIES;y++)
            if(table[y].xMin<table[y].xMax)
                for(int x=table[y].xMin;x<=table[y].xMax;x++)
                    SetPixel(hdc,x,y,color);
    }
    void ScanEdge(Point v1, Point v2, Input table[])
    {
        if(v1.y==v2.y)return;
        if(v1.y>v2.y)swap(v1,v2);
        double mInv=(double)(v2.x-v1.x)/(v2.y-v1.y);
        double x=v1.x;
        int y=v1.y;
        while(y<v2.y)
        {
            if(x<table[y].xMin)table[y].xMin=(int)ceil(x);
            if(x>table[y].xMax)table[y].xMax=(int)floor(x);
            y++;
            x+=mInv;
        }
    }
    void InitEdgeTable(int n,EdgeList table[])
    {
        Point v1=points[n-1];
        for(int i=0;i<n;i++)
        {
            Point v2=points[i];
            if(v1.y==v2.y){v1=v2;continue;}
            EdgeRecord rec=InitEdgeRec(v1, v2);
            table[v1.y].push_back(rec);
            v1=points[i];
        }
    }
    void InitEntries(Input table[])
    {
        for(int i=0;i<MAXENTRIES;i++)
        {
            table[i].xMin=MaxInteger;
            table[i].xMax=(-MaxInteger);
        }
    }
public:
    vector<Point> points;
    Polygonn(vector<Point> points)
    {
        this->points = points;
    }
    Point getInPoint() override
    {
        return Point(0,0);
    }
    void draw(HDC &hdc, int method, COLORREF color) override
    {
        for (int i = 0; i < points.size() - 1; ++i) {
            (Line(points[i].x,points[i].y, points[i + 1].x, points[i + 1].y)).draw(hdc,method,color);
        }
        int n = points.size() - 1;
        (Line(points[n].x,points[n].y, points[0].x, points[0].y)).draw(hdc,method,color);
    }
    void ConvexFill(HDC hdc,Point p[],int n,COLORREF c)
    {
        auto *table=new Input[MAXENTRIES];
        InitEntries(table);
        Point v1=p[n-1];
        for(int i=0;i<n;i++)
        {
            Point v2=p[i];
            ScanEdge(v1,v2,table);
            v1=p[i];
        }
        DrawSanLines(hdc,table,c);
        delete[] table;
    }
    void GeneralPolygonFill(HDC &hdc,int n,COLORREF c)
    {
        auto *table=new EdgeList [MAXENTRIES];
        InitEdgeTable(n,table);
        int y=0;
        while(y<MAXENTRIES && table[y].empty())y++;
        if(y==MAXENTRIES)return;
        EdgeList ActiveList=table[y];
        while (!ActiveList.empty())
        {
            ActiveList.sort();
            for(auto it=ActiveList.begin();it!=ActiveList.end();it++)
            {
                int x1=(int)ceil(it->x);
                it++;
                int x2=(int)floor(it->x);
                for(int x=x1;x<=x2;x++)SetPixel(hdc,x,y,c);
            }
            y++;
            auto it=ActiveList.begin();
            while(it!=ActiveList.end())
                if(y==it->yMax) it=ActiveList.erase(it); else it++;
            for(auto & it : ActiveList)
                it.x+=it.mInv;
            ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
        }
        delete[] table;
    }

};


#endif //GRAPHICSPROJECT_POLYGON_H
