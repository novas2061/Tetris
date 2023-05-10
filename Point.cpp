#include "Point.h"

using namespace std;

Point::Point(int initX, int initY)
{
	setPoint(initX, initY);
}

void Point::setPoint(int initX, int initY)
{
	setPointX(initX);
	setPointY(initY);
}

void Point::setPointX(int initX)
{
    x = initX;
}

void Point::setPointY(int initY)
{
    y = initY;
}

