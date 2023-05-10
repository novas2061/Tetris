#ifndef VISUAL_H
#define VISUAL_H

#include "SDL_utils.h"
#include "Board.h"

void renderBackground	 (SDL_Texture*, SDL_Renderer*);
void renderBlock         (SDL_Texture* block, SDL_Renderer* renderer, int posX, int posY, Color pColor);
void renderEdges         (SDL_Texture*, SDL_Renderer*);
void renderPiece         (SDL_Texture* block, SDL_Renderer* renderer, Piece* nPiece);
void drawBoard			 (SDL_Texture* block, SDL_Renderer* rendereer, Board* nBoard);
void drawLine            (SDL_Renderer*);
void renderNextPiece	 (SDL_Texture* block, SDL_Renderer* renderer, Piece* nPiece);

#endif // VISUAL_H
