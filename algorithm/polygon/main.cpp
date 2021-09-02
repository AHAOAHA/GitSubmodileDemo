#include "ploygon.h"
 
using namespace std;
 
int main(int argc, char** argv)
{
    // subject polygon
    // 标记好的多边形顶点，顶点顺序顺时针
    Ploygon polygon = std::vector<point2D>{
	    // {5,15}, {20,5}, {35,15},
        // {35,30},{25,30},{20,35},
        // {15,35},{10,25},{10,20}
        {5,15}, {20,5}, {35,15},
        {35,30},{25,30},{10,25}
    };

    if (polygon.IsLegal()) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    polygon.DrawPloygon();
     
    // int subjectPolygonSize = sizeof(subjectPolygon) / sizeof(subjectPolygon[0]);
 
    // // clipping polygon
    // // 目标多边形顶点，顶点顺序与标记的多边形一致
    // point2D clipPolygon[] = { {0,0}, {0,10}, {10,10}, {0,10} };
    // int clipPolygonSize = sizeof(clipPolygon) / sizeof(clipPolygon[0]);
 
    // // define the new clipped polygon (empty)、
    // // 新的多边形，相交区域组成的新的多边形的所有顶点
    // int newPolygonSize = 0;
    // point2D newPolygon[N] = { 0 };
 
    // // apply clipping
    // SutherlandHodgman(subjectPolygon, subjectPolygonSize, clipPolygon, clipPolygonSize, newPolygon, newPolygonSize);
 
    // // print clipped polygon points
    // cout << "Clipped polygon points:" << endl;
    // for(int i = 0; i < newPolygonSize; i++)
    //     cout << "(" << newPolygon[i].x << ", " << newPolygon[i].y << ")" << endl;
 
    return 0;
}
