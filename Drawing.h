#include <SDL.h>
#include <string>
#include "SDL_utils.h"
#include "Board.h"

void drawBorder(SDL_Renderer*);
SDL_Rect Block(int, int);
void drawBlock(SDL_Renderer*, const SDL_Rect&, std::string);
void drawStoredBlocks(SDL_Renderer*, std::vector<std::vector<int>>);
void drawFreeBlocks(SDL_Renderer*, std::vector<std::vector<int>>);
void drawScene(SDL_Renderer*, std::vector<std::vector<int>>, const SDL_Rect&);
void drawBlockLine(SDL_Renderer*);
