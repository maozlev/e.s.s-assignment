#pragma once
#include<iostream>

struct Point {

	Point() :
		x(0),
		y(0)
	{}

	Point(int x_, int y_) :
		x(x_),
		y(y_)
	{}

    public:
	    int x;
	    int y;

};