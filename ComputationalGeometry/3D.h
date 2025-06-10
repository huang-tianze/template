#include <cmath>
using namespace std;

typedef double CoordType;

struct Point {
    CoordType x;
    CoordType y;
    CoordType z;
};

Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Point operator*(const Point &a, double b) {
    return {a.x * b, a.y * b, a.z * b};
}

Point operator/(const Point &a, double b) {
    return {a.x / b, a.y / b, a.z / b};
}

double length(const Point &a) { return hypot(a.x, a.y, a.z); }

Point normalize(const Point &a) {
    double l = length(a);
    return {a.x / l, a.y / l, a.z / l};
}

double getAng(double a, double b, double c) {
    return std::acos((a * a + b * b - c * c) / 2 / a / b);
}

double getAng(const Point &a) { return getAng(a.x, a.y, a.z); }

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross(const Point &a, const Point &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
}
