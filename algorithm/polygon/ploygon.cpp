#include "ploygon.h"

Ploygon::Ploygon(std::vector<point2D> ploygon):_ploygon(ploygon), _max_point_N(9) {}

Ploygon::~Ploygon() {}

bool Ploygon::IsLegal() {
    if (_ploygon.size() > _max_point_N) {
        // 多边形条数判断
        return false;
    }

    // 多边形相交性判断
    if(!issimple(_ploygon)) {
        return false;
    }

    return isconvex(_ploygon);
}

double multiply(point2D sp, point2D ep, point2D op) {
    return ((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y)); 
}

bool intersect(LINESEG u,LINESEG v) { 
    return ((std::max(u.s.x,u.e.x)>=std::min(v.s.x,v.e.x))&&                     //排斥实验 
            (std::max(v.s.x,v.e.x)>=std::min(u.s.x,u.e.x))&& 
            (std::max(u.s.y,u.e.y)>=std::min(v.s.y,v.e.y))&& 
            (std::max(v.s.y,v.e.y)>=std::min(u.s.y,u.e.y))&& 
            (multiply(v.s,u.e,u.s)*multiply(u.e,v.e,u.s)>=0)&&         //跨立实验 
            (multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0)); 
}

// 判断点是否为简单多边形
// 说 明：简单多边形定义： 
// 1：循环排序中相邻线段对的交是他们之间共有的单个点 
// 2：不相邻的线段不相交 
bool issimple(std::vector<point2D> polygon) {
    int i,cn; 
    LINESEG l1,l2; 
    for(i=0;i<polygon.size();i++) { 
        l1.s=polygon[i]; 
        l1.e=polygon[(i+1)%polygon.size()]; 
        cn=polygon.size()-3; 
        while(cn) { 
            l2.s=polygon[(i+2)%polygon.size()]; 
            l2.e=polygon[(i+3)%polygon.size()]; 
            if(intersect(l1,l2)) 
                break; 
            cn--; 
        } 
        if(cn) 
            return false; 
    } 
    return true; 
}

// 返回值：按输入顺序返回多边形顶点的凸凹性判断，bc[i]=1,iff:第i个顶点是凸顶点 
void checkconvex(const std::vector<point2D>& polygon ,std::vector<bool>& bc) {
    int i, index=0; 
    point2D tp=polygon[0]; 
    for(i=1; i<polygon.size(); i++) { // 寻找第一个凸顶点  
        if(polygon[i].y<tp.y || (polygon[i].y == tp.y&&polygon[i].x<tp.x)) { 
            tp=polygon[i]; 
            index=i; 
        } 
    } 
    int count=polygon.size()-1; 
    bc[index]=true;
    while(count) {  // 判断凸凹性 
        if(multiply(polygon[(index+1)%polygon.size()],polygon[(index+2)%polygon.size()],polygon[index])>=0) 
            bc[(index+1)%polygon.size()]=true; 
        else 
            bc[(index+1)%polygon.size()]=false; 
        index++; 
        count--; 
    } 
}

// 返回值：多边形polygon是凸多边形时，返回true  
bool isconvex(std::vector<point2D> polygon) {
    std::vector<bool> bc;
    for (int i = 0; i < polygon.size(); i++) {
        bc.push_back(false);
    }
    checkconvex(polygon, bc);
    // for (auto e : bc) {
    //     std::cout << e << " " ;
    // }
    for(int i=0; i<bc.size(); i++) // 逐一检查顶点，是否全部是凸顶点 
        if(!bc[i]) 
            return false; 
    return true; 
}

// check if a point is on the LEFT side of an edge
bool inside(point2D p, point2D p1, point2D p2) {
    return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + (p2.x * p1.y - p1.x * p2.y) < 0;
}

// calculate intersection point
point2D intersection(point2D cp1, point2D cp2, point2D s, point2D e) {
    point2D dc = { cp1.x - cp2.x, cp1.y - cp2.y };
    point2D dp = { s.x - e.x, s.y - e.y };
 
    float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
    float n2 = s.x * e.y - s.y * e.x;
    float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);
 
    return { (n1 * dp.x - n2 * dc.x) * n3, (n1 * dp.y - n2 * dc.y) * n3 };
}

// Sutherland-Hodgman clipping
void SutherlandHodgman(point2D *subjectPolygon, int &subjectPolygonSize, point2D *clipPolygon, int &clipPolygonSize, point2D (&newPolygon)[N], int &newPolygonSize) {
    point2D cp1, cp2, s, e, inputPolygon[N];
 
    // copy subject polygon to new polygon and set its size
    // 将标记好的多边形顶点复制到新的多边形顶点数组里
    for(int i = 0; i < subjectPolygonSize; i++)
        newPolygon[i] = subjectPolygon[i];
 
    newPolygonSize = subjectPolygonSize;
 
    for(int j = 0; j < clipPolygonSize; j++)
    {
        // copy new polygon to input polygon & set counter to 0
        for(int k = 0; k < newPolygonSize; k++){ inputPolygon[k] = newPolygon[k]; }
        int counter = 0;
 
        // get clipping polygon edge
        cp1 = clipPolygon[j]; // 标记的多边形顶点1
        cp2 = clipPolygon[(j + 1) % clipPolygonSize];
 
        for(int i = 0; i < newPolygonSize; i++)
        {
            // get subject polygon edge
            s = inputPolygon[i];
            e = inputPolygon[(i + 1) % newPolygonSize];
 
            // Case 1: Both vertices are inside:
            // Only the second vertex is added to the output list
            if(inside(s, cp1, cp2) && inside(e, cp1, cp2))
                newPolygon[counter++] = e;
 
            // Case 2: First vertex is outside while second one is inside:
            // Both the point of intersection of the edge with the clip boundary
            // and the second vertex are added to the output list
            else if(!inside(s, cp1, cp2) && inside(e, cp1, cp2))
            {
                newPolygon[counter++] = intersection(cp1, cp2, s, e);
                newPolygon[counter++] = e;
            }
 
            // Case 3: First vertex is inside while second one is outside:
            // Only the point of intersection of the edge with the clip boundary
            // is added to the output list
            else if(inside(s, cp1, cp2) && !inside(e, cp1, cp2))
                newPolygon[counter++] = intersection(cp1, cp2, s, e);
 
            // Case 4: Both vertices are outside
            else if(!inside(s, cp1, cp2) && !inside(e, cp1, cp2))
            {
                // No vertices are added to the output list
            }
        }
        // set new polygon size
        newPolygonSize = counter;
    }
}

void Ploygon::DrawPloygon() {
    std::vector<std::vector<int>> map;
    for (int row = 0; row < 100; row++) {
        map.push_back(std::vector<int>());
        for (int rowe = 0; rowe < 100; rowe++) {
            map[row].push_back(0);
        }
    }

    for (int index = 0; index < _ploygon.size(); ++index) {
        map[_ploygon[index].y][_ploygon[index].x] = (index + 1);
    }

    for (auto &row : map) {
        for (auto &e : row) {
            if (e != 0) {
                std::cout << e;
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}