#include "Visual.h"

using namespace std;

void renderBackground	(SDL_Texture* background, SDL_Renderer* renderer)
{
	renderTexture(background, renderer, SCREEN_EDGE, SCREEN_EDGE, 600, 600);
}

void renderBlock (SDL_Texture* block, SDL_Renderer* renderer, int posX, int posY, Color pColor)
{
	renderTexture(block, renderer,
        posX * STEP + SCREEN_EDGE,
        posY * STEP + SCREEN_EDGE,
        STEP, STEP,
        (pColor % 7) * 100 , 0, 100, 100);
}

void renderEdges(SDL_Texture* edge, SDL_Renderer* renderer)
{
    for (int i = 0; i <= BOARD_WIDTH * 2 + 1; i++)
    {
        renderTexture(edge, renderer,
            i * STEP, 0, STEP, STEP);
        renderTexture(edge, renderer,
            i * STEP, STEP * (BOARD_HEIGHT + 1), STEP, STEP);
    }

    for (int i = 1; i <= BOARD_HEIGHT + 1; i++)
    {
        renderTexture(edge, renderer,
                      0, i * STEP, STEP, STEP);
        renderTexture(edge, renderer,
                      STEP * (BOARD_WIDTH * 2 + 1), i * STEP, STEP, STEP);
        renderTexture(edge, renderer,
                    STEP * (BOARD_WIDTH + 1), i * STEP, STEP, STEP);
    }
}

void renderPiece (SDL_Texture* block, SDL_Renderer* renderer, Piece* nPiece)
{
	int pX, pY;
    for (int i = 0; i < 4; i++)
	{
        pX = nPiece->getBody()[i].x + nPiece->getX(),
        pY = nPiece->getBody()[i].y + nPiece->getY();

	    if(pY >= 0)
            renderBlock(block, renderer, pX, pY, nPiece->getShade());
	}
}

void renderNextPiece(SDL_Texture* block, SDL_Renderer* renderer, Piece* nPiece)
{
    int pX, pY;
    for (int i = 0; i < 4; i++)
    {
        pX = nPiece->getBody()[i].x,
        pY = nPiece->getBody()[i].y,
        renderBlock(block, renderer, pX + 3 + BOARD_WIDTH, pY + 2, nPiece->getShade());
    }
}

void drawBoard  (SDL_Texture* block, SDL_Renderer* renderer, Board* nBoard)
{
        for (int i = 0; i < BOARD_HEIGHT; i++)
            for (int j = 0; j < BOARD_WIDTH; j++)
                if (nBoard->getGrid()[i][j] == FILLED)
                    renderBlock(block, renderer, j, i, nBoard->getBlockColor()[i][j]);
}

void drawLine            (SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    // vertical
    for (int i = SCREEN_EDGE; i <= STEP * BOARD_WIDTH + SCREEN_EDGE; i+= STEP)
        SDL_RenderDrawLine(renderer, i, SCREEN_EDGE, i, STEP * BOARD_HEIGHT + SCREEN_EDGE);
    // horizontal
    for (int i = SCREEN_EDGE; i <= STEP * BOARD_HEIGHT + SCREEN_EDGE; i+= STEP)
       SDL_RenderDrawLine(renderer, SCREEN_EDGE, i, STEP * BOARD_WIDTH + SCREEN_EDGE, i);
}

