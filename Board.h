#include <vector>

void deletePossibleLines(std::vector<std::vector<int>>&);
void deleteLine(std::vector<std::vector<int>> &, int);
bool isToStore(int, int, std::vector<std::vector<int>>);
bool isFreeBlock(int, int, std::vector<std::vector<int>>);
bool isPossibleMove (int, int, std::vector<std::vector<int>>);
int posInPixels(int);
void updateStoringBoard(int, int, std::vector<std::vector<int>>&);
void initBoard(std::vector<std::vector<int>>&);
void updateMovingBoard(int, int, std::vector<std::vector<int>>&);
void dropTheBlock(int, int&, std::vector<std::vector<int>>);
bool isGameOver(std::vector<std::vector<int>>);
