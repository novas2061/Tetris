#include "Board.h"

void deletePossibleLines(std::vector<std::vector<int>> &storingBoard)
{
    for (int i = 0; i < 20; i++)
    {
        int cnt = 0;
        for (int j = 0; j < 10; j++)
            if (storingBoard[i][j] == 1) cnt++;
        if (cnt == 10)
            deleteLine(storingBoard, i);
    }
}

void deleteLine(std::vector<std::vector<int>> &storingBoard, int line)
{
    for (int j = line; j > 0; j--)
        for (int i = 0; i < 10; i++)
            storingBoard[j][i] = storingBoard[j - 1][i];
}

bool isToStore(int posX, int posY, std::vector<std::vector<int>> storingBoard)
{
    if (posY == 19 || !isFreeBlock(posX, posY + 1, storingBoard))
        return true;
    return false;
}

bool isFreeBlock(int posX, int posY, std::vector<std::vector<int>> storingBoard)
{
    if (storingBoard[posY][posX] == 1) return false;
    else return true;
}

bool isPossibleMove (int posX, int posY, std::vector<std::vector<int>> storingBoard)
{
    if ((0 <= posX && posX <= 9) && posY <= 19 && isFreeBlock(posX, posY, storingBoard) == true)
        return true;
    return false;
}

int posInPixels(int pos)
{
    return pos * 30 + 5;
}

void updateStoringBoard(int posX, int posY, std::vector<std::vector<int>>& storingBoard)
{
    storingBoard[posY][posX] = 1;
}

void initBoard(std::vector<std::vector<int>> &b)
{
    std::vector<std::vector<int>> vec(20, std::vector<int> (10, 0));
    b = vec;
}

void updateMovingBoard(int posX, int posY, std::vector<std::vector<int>>& board)
{
    initBoard(board);
    board[posY][posX] = 1;
}

void dropTheBlock(int posX, int& posY, std::vector<std::vector<int>> storingBoard)
{
    for (int line = 19; line >= 0; line--)
    {
        if (isPossibleMove(posX, line, storingBoard))
        {
            posY = line;
            break;
        }
    }
}

bool isGameOver(std::vector<std::vector<int>> storingBoard)
{
    for (int i = 0; i < 10; i++)
    {
        if (!isFreeBlock(i, 0, storingBoard)) return true;
    }
    return false;
}
