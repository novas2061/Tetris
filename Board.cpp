#include "Board.h"

using namespace std;

Board::Board()
{
    initBoard();
}

vector<vector<Status>> Board::getGrid() const                   { return grid; }
vector<int>  Board::getSkirt() const                            { return skirt; }
std::vector<std::vector<Color>> Board::getBlockColor() const    { return bColor; }


bool Board::isPossibleMovement(int pType, int pRotation, int pX, int pY)
{
    Piece tmp (pType, pRotation, pX, pY);
    for (int i = 0; i < 4; i++)
    {
        int posX = tmp.getBody()[i].x + pX;
        int posY = tmp.getBody()[i].y + pY;

        if (posY >= 0)
        {
            if (posX < 0 || posX >= BOARD_WIDTH ||
                posY >= BOARD_HEIGHT)
                    return false;
            if (grid[posY][posX] == FILLED)
                    return false;
        }

        else
        {
            if (posX < 0 || posX >= BOARD_WIDTH)
                return false;
            else continue;
        }
    }
    return true;
}

vector<int> Board::rowsToDelete()
{
    vector<int> rows;
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
    {
        int filledBlocks = 0;
        for (int j = 0; j < BOARD_WIDTH; j++)
            if (getGrid()[i][j] == FILLED) filledBlocks++;
        if (filledBlocks == BOARD_WIDTH)
            rows.push_back(i);
    }

    return rows;
}


void Board::deletePossibleRows()
{
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
    {
        int filledBlocks = 0;
        for (int j = 0; j < BOARD_WIDTH; j++)
            if (getGrid()[i][j] == FILLED) filledBlocks++;
        if (filledBlocks == BOARD_WIDTH)
        {
            deleteRow(i);
            i++;
        }
    }
    updateSkirt();
}


int Board::dropHeight(Piece* nPiece) const
{
    int height = 20;
    vector<int> pSkirt = nPiece->getSkirt();
    int mi = nPiece->minX(),
        ma = nPiece->maxX();
    for (int i = mi; i <= ma; i++)
        if (getSkirt()[i] - (pSkirt[i - mi] + nPiece->getY()) < height)
            height = getSkirt()[i] - (pSkirt[i - mi] + nPiece->getY());
    return height - 1;
}

void Board::dropPiece(Piece* nPiece)
{
    nPiece->setY(nPiece->getY() + dropHeight(nPiece));
}

void Board::place(Piece* nPiece)
{
    for (int i = 0; i < 4; i++)
    {
        Color pColor = nPiece->getShade();
        int pX = nPiece->getBody()[i].x + nPiece->getX();
        int pY = nPiece->getBody()[i].y + nPiece->getY();
        if (pY >= 0)
        {
            grid[pY][pX] = FILLED;
            bColor[pY][pX] = pColor;
        }
    }
    updateSkirt();
}

bool Board::isGameOver()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        if (getGrid()[0][i] == FILLED)
            return true;
    return false;
}


void Board::initBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
        grid.push_back(vector<Status>(BOARD_WIDTH, FREE));

    for (int i = 0; i < BOARD_HEIGHT; i++)
        bColor.push_back(vector<Color>(BOARD_WIDTH, WHITE));

    for (int i = 0; i < BOARD_WIDTH; i++)
        skirt.push_back(BOARD_HEIGHT);
}

void Board::deleteRow (int row) // move all lines down
{
    for (int i = row; i > 0; i--)
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            grid[i][j] = grid[i - 1][j];
            bColor[i][j] = bColor[i - 1][j];
        }
}

void Board::updateSkirt()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        int freeBlocks = 0;
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (grid[j][i] == FILLED)
            {
                skirt[i] = j;
                break;
            }
            else freeBlocks++;
        }
        if (freeBlocks == BOARD_HEIGHT)
            skirt[i] = BOARD_HEIGHT;
    }
}

