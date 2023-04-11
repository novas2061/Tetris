#include <vector>

void deletePossibleLines(std::vector<std::vector<int>>&);
void deleteLine(std::vector<std::vector<int>> &, int);
bool isToStore(int posX, int posY, std::vector<std::vector<int>> storingBoard);
bool isFreeBlock(int posX, int posY, std::vector<std::vector<int>> storingBoard);
bool isPossibleMove (int posX, int posY, std::vector<std::vector<int>> storingBoard);
int posInPixels(int pos);
void updateStoringBoard(int posX, int posY, std::vector<std::vector<int>>&);
void initBoard(std::vector<std::vector<int>>&);
void updateMovingBoard(int posX, int posY, std::vector<std::vector<int>>&);
void dropTheBlock(int posX, int& posY, std::vector<std::vector<int>> storingBoard);
bool isGameOver(std::vector<std::vector<int>>);
