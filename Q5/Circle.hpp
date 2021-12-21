#include "Shape.hpp"
#include <math.h>

class Circle : public Shape {

public:
	double  c_radius;
	string c_name="Circle";

	Circle(const Point& center, const double radius) :Shape(center, radius){}

	size_t area() const override{return M_PI * c_radius* c_radius;}

	string name() const override {return c_name;}
};
