#include "Piece.h"
using namespace std;

vector<vector<vector<Point>>> nPieces
{
	// square
	{
		{Point(1, 1), Point(1, 2), Point(2, 1), Point(2, 2)},
		{Point(1, 1), Point(1, 2), Point(2, 1), Point(2, 2)},
		{Point(1, 1), Point(1, 2), Point(2, 1), Point(2, 2)},
		{Point(1, 1), Point(1, 2), Point(2, 1), Point(2, 2)}
	},

	// I
	{
		{Point(2, 0), Point(2, 1), Point(2, 2), Point(2, 3)},
		{Point(1, 2), Point(2, 2), Point(3, 2), Point(4, 2)},
		{Point(2, 1), Point(2, 2), Point(2, 3), Point(2, 4)},
		{Point(0, 2), Point(1, 2), Point(2, 2), Point(3, 2)}
	},

	// left N
	{
		{Point(1, 2), Point(1, 3), Point(2, 1), Point(2, 2)},
		{Point(1, 1), Point(2, 1), Point(2, 2), Point(3, 2)},
		{Point(2, 2), Point(2, 3), Point(3, 1), Point(3, 2)},
		{Point(1, 2), Point(2, 2), Point(2, 3), Point(3, 3)}
	},

	// right N
	{
		{Point(2, 1), Point(2, 2), Point(3, 2), Point(3, 3)},
		{Point(1, 3), Point(2, 2), Point(2, 3), Point(3, 2)},
		{Point(1, 1), Point(1, 2), Point(2, 2), Point(2, 3)},
		{Point(1, 2), Point(2, 1), Point(2, 2), Point(3, 1)}
	},

	// left L
	{
		{Point(1, 2), Point(2, 0), Point(2, 1), Point(2, 2)},
		{Point(2, 1), Point(2, 2), Point(3, 2), Point(4, 2)},
		{Point(2, 2), Point(2, 3), Point(2, 4), Point(3, 2)},
		{Point(0, 2), Point(1, 2), Point(2, 2), Point(2, 3)}
	},

	// right L
	{
		{Point(2, 0), Point(2, 1), Point(2, 2), Point(3, 2)},
		{Point(2, 2), Point(2, 3), Point(3, 2), Point(4, 2)},
		{Point(1, 2), Point(2, 2), Point(2, 3), Point(2, 4)},
		{Point(0, 2), Point(1, 2), Point(2, 1), Point(2, 2)}
	},

	// T
	{
		{Point(1, 2), Point(2, 1), Point(2, 2), Point(3, 2)},
		{Point(2, 1), Point(2, 2), Point(2, 3), Point(3, 2)},
		{Point(1, 2), Point(2, 2), Point(2, 3), Point(3, 2)},
		{Point(1, 2), Point(2, 1), Point(2, 2), Point(2, 3)}
	}
};

// skirt: largest y for each x

vector<vector<vector<int>>> pSkirt
{
    {
        {2, 2},  {2, 2},  {2, 2},  {2, 2}
    },

    {
        {3},  {2, 2, 2, 2},  {4},  {2, 2, 2, 2}
    },

    {
        {3, 2},  {1, 2, 2},  {3, 2},  {2, 3, 3}
    },

    {
        {2, 3},  {3, 3, 2},  {2, 3},  {2, 2, 1}
    },

    {
        {2, 2},  {2, 2, 2},  {4, 2},  {2, 2, 3}
    },

    {
        {2, 2},  {3, 2, 2},  {2, 4},  {2, 2, 2}

    },

    {
        {2, 2, 2},  {3, 2},  {2, 3, 2},  {2, 3}
    }
};

//*************************************************************************************************************//


Piece::Piece(int pType, int pRotation, int pX, int pY, Color pColor)
{
	setType(pType);
	setRotation(pRotation);
	setX(pX);
	setY(pY);
	setShade(pColor);
}

void Piece::setType(int pType)
{
	type = pType;
}
void Piece::setRotation(int pRotation)
{
	rotation = pRotation;
}
void Piece::setX(int pX)
{
	x = pX;
}
void Piece::setY(int pY)
{
	y = pY;
}
void Piece::setShade(Color pColor)
{
	shade = pColor;
}

// get functions
int Piece::getType					() const { return type; }
int Piece::getRotation					() const { return rotation; }
int Piece::getX					    	() const { return x; }
int Piece::getY 					() const { return y; }
Color Piece::getShade 					() const { return shade; }

int Piece::minX(std::vector<Point> pVec) const
{
	int mi = pVec[0].x;
	for (unsigned int i = 1; i < pVec.size(); i++)
		if (pVec[i].x < mi)
			mi = pVec[i].x;
	return mi;
}
int Piece::minY(std::vector<Point> pVec) const
{
	int mi = pVec[0].y;
	for (unsigned int i = 1; i < pVec.size(); i++)
		if (pVec[i].y < mi)
			mi = pVec[i].y;
	return mi;

}

int Piece::maxX(std::vector<Point> pVec) const
{
	int ma = pVec[0].x;
	for (unsigned int i = 1; i < pVec.size(); i++)
		if (pVec[i].x > ma)
			ma = pVec[i].x;
	return ma;

}

int Piece::maxY(std::vector<Point> pVec) const
{
	int ma = pVec[0].y;
	for (unsigned int i = 1; i < pVec.size(); i++)
		if (pVec[i].y > ma)
			ma = pVec[i].y;
	return ma;
}

int Piece::minX() const
{
	return minX(getBody()) + getX();
}

int Piece::minY() const
{
	return minY(getBody()) + getY();
}
int Piece::maxX() const
{
	return maxX(getBody()) + getX();
}

int Piece::maxY() const
{
	return maxY(getBody()) + getY();
}

std::vector<Point> Piece::getBody() const
{
	return nPieces[getType()][getRotation()];
}

std::vector<int> Piece::getSkirt() const // largest y for each x
{
	return pSkirt[getType()][getRotation()];
}

void Piece::moveToInitialSpot()
{
	setX(BOARD_WIDTH / 2 - 3);
    int maxSkirt = getSkirt()[0];
    for (unsigned int i = 1; i < getSkirt().size(); i++)
        if (getSkirt()[i] > maxSkirt)
            maxSkirt = getSkirt()[i];
    setY(-maxSkirt);
}

void Piece::moveLeft()
{
    setX(getX() - 1);
}
void Piece::moveRight()
{
    setX(getX() + 1);
}
void Piece::moveDown()
{
    setY(getY() + 1);
}

