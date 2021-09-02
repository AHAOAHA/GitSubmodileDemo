#pragma once
#include <iostream>
#include <vector>

const int N = 9;

struct point2D { float x, y; };

struct LINESEG { 
    point2D s; 
    point2D e; 
    LINESEG(point2D a, point2D b) { s=a; e=b;} 
    LINESEG() { }
};

struct LINE { 
   double a; 
   double b; 
   double c; 
   LINE(double d1=1, double d2=-1, double d3=0) {a=d1; b=d2; c=d3;} 
}; 

class Ploygon {
    public:

        Ploygon(std::vector<point2D> ploygon = std::vector<point2D>());
        ~Ploygon();

        bool IsLegal();
        void DrawPloygon();
    
    private:

    private:
        std::vector<point2D> _ploygon;
        const int64_t _max_point_N; // max point num
};

double multiply(point2D sp,point2D ep,point2D op);
bool intersect(LINESEG u,LINESEG v);
// 判断点是否为简单多边形
// 说 明：简单多边形定义： 
// 1：循环排序中相邻线段对的交是他们之间共有的单个点 
// 2：不相邻的线段不相交 
bool issimple(std::vector<point2D> polygon);
// 返回值：按输入顺序返回多边形顶点的凸凹性判断，bc[i]=1,iff:第i个顶点是凸顶点 
void checkconvex(int vcount,point2D polygon[],bool bc[]);

bool isconvex(std::vector<point2D> polygon);

// check if a point is on the LEFT side of an edge
bool inside(point2D p, point2D p1, point2D p2);
// calculate intersection point
point2D intersection(point2D cp1, point2D cp2, point2D s, point2D e);

// Sutherland-Hodgman clipping
void SutherlandHodgman(point2D *subjectPolygon, int &subjectPolygonSize, point2D *clipPolygon, int &clipPolygonSize, point2D (&newPolygon)[N], int &newPolygonSize);