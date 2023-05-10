#include "SDL_utils.h"
using namespace std;
//
const int SCREEN_WIDTH = 660;
const int SCREEN_HEIGHT = 660;
const string WINDOW_TITLE = "TETRIS";

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if(fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
        logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while(true)
    {
    if (SDL_WaitEvent(&e) != 0 &&
    (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
        return;
    SDL_Delay(100);
    }
}

SDL_Texture* loadTexture (string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        cout << "Unable to create texture from " << path << " SDL Error: "
            << IMG_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr)
            cout << "Unable to create texture from " << path << " SDL Error: "
                    << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dst);
}


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, int x1, int y1, int w1, int h1)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_Rect sc;
    sc.x = x1;
    sc.y = y1;
    sc.w = w1;
    sc.h = h1;

    SDL_RenderCopy(ren, tex, &sc, &dst);
}

Mix_Music* loadMusic(string path)
{
	Mix_Music* music = NULL;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
         Mix_FreeMusic(music);
         printf("%s", Mix_GetError());
	}

	music = Mix_LoadMUS(path.c_str());
	if (music == NULL)
	{
         Mix_FreeMusic(music);
		printf("%s", Mix_GetError());
	}

	return music;
}

Mix_Chunk* loadChunk(string path)
{
    Mix_Chunk* chunk = NULL;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
        Mix_FreeChunk(chunk);
        printf("%s", Mix_GetError());
	}

    chunk = Mix_LoadWAV(path.c_str());

	if (chunk == NULL)
	{
        Mix_FreeChunk(chunk);
		printf("%s", Mix_GetError());
	}

	return chunk;
}

