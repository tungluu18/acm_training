struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    double distance(const Point& other) {
        return sqrt((other.x - x) * (other.x - x)
                + (other.y - y) * (other.y - y));
    }
    bool operator < (const Point& other) {
        return x < other.x || (x == other.x && y < other.y);
    }
};

struct Line {
    double a, b, c;
    void extract(const Point& A, const Point& B) {
        a = A.y - B.y;
        b = B.x - A.x;
        c = - (a * A.x + b * A.y);
    }

    bool intersect(const Line& other, Point& result) {
        double determinant = this->a * other.b - this->b * other.a;
        if (fabs(determinant) < eps) return false;  //two lines are parallel

        result.x = (this->b * other.c - this->c * other.b) / determinant;
        result.y = (this->c * other.a - this->a * other.c) / determinant;
        return true;
    }
};

int ccw(Point A, Point B, Point C) {
    double t = (B.x - A.x) * (C.y - B.y) - (C.x - B.x) * (B.y - A.y);
    if (t > 0) return 1;  //turn left
    if (t < 0) return -1;   //turn right
    return 0;  //they are on a line
}

bool layOn(Point A, Line L) { return (L.a * A.x + L.b * A.y + L.c == 0); }

double triangle_area (const Point& p1, const Point& p2, const Point& p3) {
    return abs((double) p1.x * p2.y +
               (double) p2.x * p3.y +
               (double) p3.x * p1.y -
               (double) p1.y * p2.x -
               (double) p2.y * p3.x -
               (double) p3.y * p1.x) / 2.0;
}

double polygonArea(Point P[], int n)
{
    double area = 0.0;

    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (P[j].x + P[i].x) * (P[j].y - P[i].y);
        j = i;  // j is previous vertex to i
    }

    // Return absolute value
    return abs(area / 2.0);
}

poly find_convex() {
    U.clear(); L.clear();   sort(p+1,p+n+1);   ///Prepare
    rep(i,1,n) {
        while (U.size()>=2 && CCW(U[U.size()-2],U[U.size()-1],p[i])<=0)
            U.pop_back();
        U.push_back(p[i]);
    }
    rap(i,n,1) {
        while (L.size()>=2 && CCW(L[L.size()-2],L[L.size()-1],p[i])<=0)
            L.pop_back();
        L.push_back(p[i]);
    }
    U.pop_back(); L.pop_back();
    rep(i,0,L.size()-1) U.push_back(L[i]);
    return U;
}
