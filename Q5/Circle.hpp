#include "Shape.hpp"
#include <math.h>

class Circle : public Shape {

public:
	string c_name="Circle";

	Circle(const Point& center, const double radius) :Shape(center, radius){}

	size_t area() const override{return M_PI * radius_* radius_;}

	string name() const override {return c_name;}
};
