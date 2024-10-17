int main() {
    typedef struct point {
        int x;
        int y;
    } Point;

    Point p = {3, 5};

    typedef Point *PointPointer;

    PointPointer pp = &p;
}
