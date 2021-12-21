#pragma once
#include<iostream>
struct Size {

	Size() :
		width(0),
		height(0){}

	Size(int width_, int height_) :
		width(width_),
		height(height_){}

	int width;
	int height;
};