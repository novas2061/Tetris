#include "Drawing.h"

const int SCREEN_WIDTH = 310;
const int SCREEN_HEIGHT = 610;
const std::string WINDOW_TITLE = "TETRIS";

void drawBorder(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green

    SDL_Rect border;
    // upper
    border.x = 0;
    border.y = 0;
    border.w = SCREEN_WIDTH;
    border.h = 5;
    SDL_RenderFillRect(renderer, &border);
    // lower
    border.x = 0;
    border.y = SCREEN_HEIGHT - 5;
    border.w = SCREEN_WIDTH;
    border.h = 5;

    SDL_RenderFillRect(renderer, &border);

    // left
    border.x = 0;
    border.y = 5;
    border.w = 5;
    border.h = SCREEN_HEIGHT - 10;
    SDL_RenderFillRect(renderer, &border);

    // right
    border.x = SCREEN_WIDTH - 5;
    border.y = 5;
    border.w = 5;
    border.h = SCREEN_HEIGHT - 10;
    SDL_RenderFillRect(renderer, &border);
}

SDL_Rect Block(int posX, int posY)
{
    SDL_Rect block;
    block.x = posInPixels(posX);
    block.y = posInPixels(posY);
    block.w = 30;
    block.h = 30;
    return block;
}

void drawBlock(SDL_Renderer* renderer, const SDL_Rect& rect, std::string status)
{
	if (status == "FILLED")
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
	else
    	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   // blue

    SDL_RenderFillRect(renderer, &rect);
}

void drawStoredBlocks(SDL_Renderer* renderer, std::vector<std::vector<int>> storedBlock)
{
    for (int posY = 0; posY < 20; posY++)
    {
        for (int posX = 0; posX < 10; posX++)
        {
            if (!isFreeBlock(posX, posY, storedBlock))
            {
                drawBlock(renderer, Block(posX, posY), "FILLED");
            }
        }
    }
}

void drawFreeBlocks(SDL_Renderer* renderer, std::vector<std::vector<int>> storedBlock)
{
    for (int posY = 0; posY < 20; posY++)
    {
        for (int posX = 0; posX < 10; posX++)
        {
            if (isFreeBlock(posX, posY, storedBlock))
            {
                drawBlock(renderer, Block(posX, posY), "FREE");
            }
        }
    }
}

void drawScene(SDL_Renderer* renderer, std::vector<std::vector<int>> storedBlock, const SDL_Rect& movingBlock) // draw border, stored blocks, free blocks, moving block
{
	drawBorder(renderer);
	drawStoredBlocks(renderer, storedBlock);
	drawFreeBlocks(renderer, storedBlock);
	drawBlock(renderer, movingBlock, "FILLED"); // current block
	drawBlockLine(renderer);
	SDL_RenderPresent(renderer);
}

void drawBlockLine(SDL_Renderer* renderer)
{
    // vertical
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);   // purple
    for (int x = 5; x <= 305; x += 30)
    {
        SDL_RenderDrawLine(renderer, x, 5, x, 605);
    }

    // horizontal
    for (int y = 5; y <= 605; y += 30)
    {
        SDL_RenderDrawLine(renderer, 5, y, 305, y);
    }
}
