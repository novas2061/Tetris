#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <stdexcept>

class Point
{
public:
    explicit Point(int = 0, int = 0);

	void setPoint(int, int);
	void setPointX(int);
	void setPointY(int);

	int x, y;
};

#endif // POINT_H
