#include "Shape.hpp"
#include "Size.hpp"

class Rectangle : public Shape {

public:
	Size  m_size;
	string r_name="Rectangle";

	Rectangle(const Point& center, const Size& size) :Shape(center,size){}

	size_t area() const override {return m_size.width *(size_t)m_size.height;}

	string name() const override {return r_name;}

};
