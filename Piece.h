#ifndef PIECE_H
#define PIECE_H

#include "Constants.h"
#include "Point.h"
#include <vector>

enum Color {PURPLE, ORANGE, CYAN, BLUE, RED, YELLOW, GREEN, WHITE};

class Piece
{
public:
	explicit Piece(int i = 0, int = 0, int = 0, int = 0, Color = PURPLE);

   	// set functions
    	void setPiece				(int, int, int, int, Color);
	void setType				(int);
	void setRotation			(int);
	void setX				(int);
	void setY 				(int);
	void setShade				(Color);

	// get functions
	int getType				() const;
	int getRotation				() const;
    	int getX				() const;
	int getY 				() const;
	Color getShade 				() const;

	int minX(std::vector<Point>) const;
	int minY(std::vector<Point>) const;
	int maxX(std::vector<Point>) const;
	int maxY(std::vector<Point>) const;

    	int minX() const;
	int minY() const;
	int maxX() const;
	int maxY() const;

	std::vector<Point> getBody() const;
	std::vector<int> getSkirt() const; // largest y for each x

	void moveToInitialSpot();
    	void moveLeft();
    	void moveRight();
    	void moveDown();
private:
	int type, rotation, x, y;
	Color shade;
};

#endif // PIECE_H
