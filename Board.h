#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

enum Status {FILLED, FREE};

class Board
{
public:
    explicit Board();

    std::vector<std::vector<Status>> getGrid() const;
    std::vector<int> getSkirt() const;
    std::vector<std::vector<Color>> getBlockColor() const;

    bool isPossibleMovement(int, int, int, int);

    std::vector<int> rowsToDelete();
    void deletePossibleRows();
    int dropHeight(Piece*) const;
    void dropPiece(Piece*);
    void place(Piece*);

    bool isGameOver();

private:
    std::vector<std::vector<Status>> grid;
    std::vector<std::vector<Color>> bColor; // block color
    std::vector<int> skirt; // smallest filled y for each x

    void initBoard();
    void deleteRow (int);
    void updateSkirt();

};

#endif // BOARD_H
