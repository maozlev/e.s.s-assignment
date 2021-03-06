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
        virtual double area() const = 0; //pure virtual- every shape and its area. change area function from size_t to double
        virtual Point center() const {return shape_point;} // this function is not going to be overridden
        virtual string name() const {return "Shape";} // every shape and its name
};
ostream& operator<< (ostream& os, const Point& p) {return (os << p.x << '/'<< p.y);} // operator for print Point