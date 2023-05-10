#include <ctime>
#include "Visual.h"

using namespace std;

void renderText(SDL_Surface*, SDL_Texture*, string);
int getRand(int a, int b);
void createNewPiece(Piece* curPiece, Piece* nextPiece);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture* background = loadTexture("images/background/menu.jpg", renderer);
    SDL_Texture* gameOverBG = loadTexture("images/background/869.jpeg", renderer);

    SDL_Texture* block = loadTexture("images/tiles.bmp", renderer);
    SDL_Texture* edge = loadTexture("images/edge.bmp", renderer);

    Mix_Music* BGM = loadMusic("sounds/bgm.mp3");
    Mix_Chunk* clearRowsEffect = loadChunk("sounds/clearRows.wav");
    Mix_Chunk* dropPieceEffect = loadChunk("sounds/dropPiece.wav");

     //game starts here
    unsigned long WAIT_TIME = 2000;
    unsigned long PLAYER_SCORE = 0;
    unsigned long LINES_CLEARED = 0;
    Board gBoard;
    // piece
    Piece curPiece(getRand(0, 6), getRand(0, 3), 0, 0, (Color)(getRand(0, 6)));
    curPiece.moveToInitialSpot();
    Piece nextPiece(getRand(0, 6), getRand(0, 3), 0, 0, (Color)(getRand(0, 6)));
    nextPiece.moveToInitialSpot();

    Mix_PlayMusic(BGM, -1);

    if (TTF_Init() == -1)
        cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << endl;

    TTF_Font* font = TTF_OpenFont("fonts/8bitOperatorPlus8-Regular.ttf", 25);
    TTF_Font* gOver = TTF_OpenFont("fonts/8bitOperatorPlus8-Regular.ttf", 70);

    if(font == nullptr)
    {
        cout << "Could not load font" << endl;
        exit(1);
    }

    unsigned long mTime1 = SDL_GetTicks();

    SDL_Event e;

    while(!gBoard.isGameOver())
    {

        string lines = "LINES: ";
        lines += to_string(LINES_CLEARED);

        string score = "SCORE: ";
        score += to_string(PLAYER_SCORE);

        SDL_Surface* surfaceLines = TTF_RenderText_Solid (font,lines.c_str(),{255,255,255});
        SDL_Texture* textureLines = SDL_CreateTextureFromSurface(renderer,surfaceLines);
        SDL_FreeSurface(surfaceLines);

        SDL_Surface* surfaceScore = TTF_RenderText_Solid	 (font,score.c_str(),{255,255,255});
        SDL_Texture* textureScore = SDL_CreateTextureFromSurface(renderer,surfaceScore);
        SDL_FreeSurface(surfaceScore);

        SDL_Surface* surfaceNext = TTF_RenderText_Solid	 (font,"NEXT PIECE",{255,255,255});
        SDL_Texture* textureNext = SDL_CreateTextureFromSurface(renderer,surfaceNext);
        SDL_FreeSurface(surfaceNext);

        renderTexture(textureNext, renderer, (BOARD_WIDTH + 2) * STEP, STEP);
        renderTexture(textureScore, renderer, (BOARD_WIDTH + 2) * STEP, BOARD_HEIGHT / 2 * STEP);
        renderTexture(textureLines, renderer, (BOARD_WIDTH + 2) * STEP, (BOARD_HEIGHT / 2 + 3) * STEP);

        if (e.key.keysym.sym == SDLK_ESCAPE) break;

        if (e.type == SDL_QUIT) break;

        renderBackground(background, renderer);
        renderEdges(edge, renderer);
        drawBoard(block, renderer, &gBoard);
        renderPiece(block, renderer, &curPiece);
        renderNextPiece(block, renderer, &nextPiece);
        drawLine(renderer);
        renderTexture(textureNext, renderer, (BOARD_WIDTH + 2) * STEP, STEP);
        renderTexture(textureScore, renderer, (BOARD_WIDTH + 2) * STEP, BOARD_HEIGHT / 2 * STEP);
        renderTexture(textureLines, renderer, (BOARD_WIDTH + 2) * STEP, (BOARD_HEIGHT / 2 + 3) * STEP);


        SDL_RenderPresent(renderer);

        unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME)
		{
                if (gBoard.isPossibleMovement(curPiece.getType(), curPiece.getRotation(),
                                              curPiece.getX(), curPiece.getY() + 1))
                    curPiece.moveDown();
                else
                {
                    gBoard.place(&curPiece);
                    createNewPiece(&curPiece, &nextPiece);
                }
                mTime1 = SDL_GetTicks();
                WAIT_TIME = 2000 - (LINES_CLEARED / 10) * 200;
		}

        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                cout << "\nPLAYER'S SCORE: " << PLAYER_SCORE;
                cout << "\nLINES CLEARED: " << LINES_CLEARED;
                cout << "\nWAIT_TIME: " << WAIT_TIME;
                if (e.key.keysym.sym == SDLK_ESCAPE) break;

                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (gBoard.isPossibleMovement(curPiece.getType(), curPiece.getRotation(),
                                                  curPiece.getX() - 1, curPiece.getY()))
                        curPiece.moveLeft();
                }
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (gBoard.isPossibleMovement(curPiece.getType(), curPiece.getRotation(),
                                                  curPiece.getX() + 1, curPiece.getY()))
                        curPiece.moveRight();
                }

                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    if ((gBoard.isPossibleMovement(curPiece.getType(), (curPiece.getRotation() + 1) % 4,
                                                  curPiece.getX(), curPiece.getY() + 1)))
                                curPiece.setRotation((curPiece.getRotation() + 1) % 4);
                }

                if (e.key.keysym.sym == SDLK_DOWN)
                {
                    if (gBoard.isPossibleMovement(curPiece.getType(), curPiece.getRotation(),
                                                  curPiece.getX(), curPiece.getY() + 1))
                    {
                        curPiece.moveDown();
                        PLAYER_SCORE++;
                    }
                    else
                    {
                        gBoard.place(&curPiece);
                        createNewPiece(&curPiece, &nextPiece);

                        if (gBoard.rowsToDelete().size() != 0)
                        {
                            Mix_PlayChannel(-1, clearRowsEffect, 0);
                            switch(gBoard.rowsToDelete().size())
                            {
                            case 1:
                                PLAYER_SCORE += 100;
                                LINES_CLEARED += 1;
                                break;
                            case 2:
                                PLAYER_SCORE += 300;
                                LINES_CLEARED += 1;
                                break;
                            case 3:
                                PLAYER_SCORE += 500;
                                LINES_CLEARED += 1;
                                break;
                            case 4:
                                PLAYER_SCORE += 800;
                                LINES_CLEARED += 1;
                                break;
                            default:
                                break;
                            }
                            WAIT_TIME = 2000 - (LINES_CLEARED / 10) * 200;

                        }
                    }
                }

                if (e.key.keysym.sym == SDLK_UP)
                {
                    Mix_PlayChannel(-1, dropPieceEffect, 0);
                    PLAYER_SCORE += 2 * gBoard.dropHeight(&curPiece);
                    gBoard.dropPiece(&curPiece);
                    gBoard.place(&curPiece);

                    if (gBoard.rowsToDelete().size() != 0)
                    {
                        Mix_PlayChannel(-1, clearRowsEffect, 0);
                        switch(gBoard.rowsToDelete().size())
                        {
                        case 1:
                            PLAYER_SCORE += 100;
                            LINES_CLEARED += 1;
                            break;
                        case 2:
                            PLAYER_SCORE += 300;
                            LINES_CLEARED += 1;
                            break;
                        case 3:
                            PLAYER_SCORE += 500;
                            LINES_CLEARED += 1;
                            break;
                        case 4:
                            PLAYER_SCORE += 800;
                            LINES_CLEARED += 1;
                            break;
                        default:
                            break;
                        }
                    }
                    createNewPiece(&curPiece, &nextPiece);
                    gBoard.deletePossibleRows();
                    WAIT_TIME = 2000 - (LINES_CLEARED / 10) * 200;
                }
            }
        }
    }

    string game_over = "GAME OVER!";
    SDL_Surface* surfaceGameOver = TTF_RenderText_Solid (gOver,game_over.c_str(),{255,255,255});
    SDL_Texture* textureGameOver = SDL_CreateTextureFromSurface(renderer,surfaceGameOver);
    SDL_FreeSurface(surfaceGameOver);

    string final_score = " FINAL SCORE: ";
    final_score += to_string(PLAYER_SCORE);
    SDL_Surface* surfaceFinal = TTF_RenderText_Solid (font,final_score.c_str(),{255,255,255});
    SDL_Texture* textureFinal = SDL_CreateTextureFromSurface(renderer,surfaceFinal);
    SDL_FreeSurface(surfaceFinal);

    renderBackground(gameOverBG, renderer);
    renderTexture(textureGameOver, renderer, 160, 270);
    renderTexture(textureFinal, renderer, 230, 400);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

int getRand(int a, int b)
{
    srand((int)time(0));
    return a + rand() % b;
}

void createNewPiece(Piece* curPiece, Piece* nextPiece)
{
    curPiece->setType(nextPiece->getType());
    curPiece->setRotation(nextPiece->getRotation());
    curPiece->setX(nextPiece->getX());
    curPiece->setY(nextPiece->getY());
    curPiece->setShade(nextPiece->getShade());

    nextPiece->setType(getRand(0, 6));
    nextPiece->setRotation(getRand(0, 3));
    nextPiece->setX(0);
    nextPiece->setY(0);
    nextPiece->setShade((Color)(getRand(0, 6) % 7));
    nextPiece->moveToInitialSpot();
}
