#include <iostream>
#include "Drawing.h"


int main(int argc, char* argv[])
{
    bool gameOver = false;

    // boards
    std::vector<std::vector<int>> movingBoard(20, std::vector<int> (10, 0));
    std::vector<std::vector<int>> storingBoard(20, std::vector<int> (10, 0));
    int posX = 5; int posY = 0; // initial position

    // visual
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    drawBorder(renderer);
    SDL_RenderPresent(renderer);

    // start
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT) break;

        if (e.type == SDL_KEYDOWN)
        {

            if (e.key.keysym.sym == SDLK_ESCAPE) break;

            switch(e.key.keysym.sym)
            {
                case (SDLK_LEFT):
                {
                    if (isPossibleMove(posX - 1, posY, storingBoard))
                    {
                        posX--;
                        updateMovingBoard(posX, posY, movingBoard);
                    }
                    break;
                }

                case (SDLK_RIGHT):
                {
                    if (isPossibleMove(posX + 1, posY, storingBoard))
                    {
                        posX++;
                        updateMovingBoard(posX, posY, movingBoard);
                    }
                    break;

                }
                case (SDLK_DOWN):
                {
                    if (isPossibleMove(posX, posY + 1, storingBoard))
                    {
                        posY++;
                        if (isToStore(posX, posY, storingBoard) == true)
                        {
                            updateStoringBoard(posX, posY, storingBoard);
                            posX = 5; posY = 0;
                        }
                        updateMovingBoard(posX, posY, movingBoard);
                    }
                    if (!isPossibleMove(posX, posY + 1, storingBoard))
                    {
                        updateStoringBoard(posX, posY, storingBoard);
                        posX = 5; posY = 0;
                    }
                    if (posY == 0 && !isFreeBlock(posX, posY + 1, storingBoard))
                    {
                        storingBoard[0][posX] = 1;
                    }
                    if (isGameOver(storingBoard))
                        gameOver = true;

                    break;
                }

                case(SDLK_SPACE):
                {
                    dropTheBlock(posX, posY, storingBoard);
                    updateStoringBoard(posX, posY, storingBoard);
                    posX = 5; posY = 0;
                    if (isGameOver(storingBoard))
                    gameOver = true;
                }
            }

            deletePossibleLines(storingBoard);
            drawScene(renderer, storingBoard, Block(posX, posY));

            if (gameOver == true)
            {
                std::cout << "GAME OVER" << std::endl;
                break;
            }
        }
    }
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
