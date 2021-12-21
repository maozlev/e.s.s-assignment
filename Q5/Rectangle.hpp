#include "Shape.hpp"
#include "Size.hpp"

class Rectangle : public Shape {

public:
	string r_name="Rectangle";

	Rectangle(const Point& center, const Size& size) :Shape(center,size){}

	size_t area() const override {return size_.width *(size_t)size_.height;}

	string name() const override {return r_name;}

};
