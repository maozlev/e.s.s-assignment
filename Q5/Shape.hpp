#pragma once
#include <iostream>
#include "Point.hpp"
#include "Size.hpp"

using namespace std;

class Shape {
    public:
        Point shape_point;
        Size size_;
        double radius_;
        Shape()= default;
        Shape(const Point& center, const Size& size) :shape_point(center),size_(size){}
        Shape(const Point& center, const double radius) :shape_point(center),radius_(radius){}

        virtual Point center() const {return shape_point;} // this function is not going to be overridden
        virtual size_t area() const = 0; // every shape and its area
        virtual string name() const {return "Shape";} // every shape and its name
};
ostream& operator<< (ostream& os, const Point& p) {return (os << p.x << '/'<< p.y);} // operator for print Point