#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "pointBuffer.hpp"

using namespace std;

const float PI = 3.1415;

auto f = [&](const float &x) -> float { return (pow(cos(x/2), 2) + sqrt(x)); };

const int WIN_WIDTH  = 640;
const int WIN_HEIGHT = 480;

struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    color(uint8_t r,
          uint8_t g,
          uint8_t b,
          uint8_t a) : r(r), g(g), b(b), a(a) {};
    color(){};
};

const color COLOR_RED  (255,   0,   0, 255);
const color COLOR_BLACK(  0,   0,   0, 255);
const color COLOR_WHITE(255, 255, 255, 255);

color getRendererColor(SDL_Renderer* renderer) {
    color old_color;
    SDL_GetRenderDrawColor(renderer, &old_color.r,
                           &old_color.g,
                           &old_color.b,
                           &old_color.a);
    return old_color;
}

void setRendererColor(SDL_Renderer* renderer, const color &newColor) {
    SDL_SetRenderDrawColor(renderer,
                           newColor.r,
                           newColor.g,
                           newColor.b,
                           newColor.a);
}

void impureDrawGraph(SDL_Renderer* renderer,
                     function<float(float)> f, const int &width) {
    // Getting current color
    color oldColor = getRendererColor(renderer);

    setRendererColor(renderer, COLOR_RED);

    pointBuffer* data = pointBuffer::calculatePoints(3*PI/2, 18*PI,
                                                     f, (size_t) width);

    SDL_Point* rendData = new SDL_Point[width];

    for (int i = 0; i < width; ++i) {
        rendData[i].x = i;//int(12*(data->getPoints()[i].x - data->getPoints()[0].x));
        rendData[i].y = int(400 - data->getPoints()[i].y*30);
    }

    SDL_RenderDrawLines(renderer, rendData, width);

    setRendererColor(renderer, oldColor);

    delete[] data;
    delete[] rendData;
}

SDL_Point genPoint(int x, int y) {
    SDL_Point res {x, y};
    return res;
};
SDL_Rect genRect(int x, int y, int w, int h) {
    SDL_Rect res{x, y, w, h};
    return res;
}

void impureDrawAxes(SDL_Renderer* renderer,
                    const int &width,
                    const int &height) {
    color oldColor = getRendererColor(renderer);

    setRendererColor(renderer, COLOR_BLACK);

    // Border axes
    SDL_Point corners[4] = {genPoint(0,0),
                            genPoint(0,height),
                            genPoint(width, height),
                            genPoint(width, 0)};

    SDL_RenderDrawLines(renderer, corners, 4);

    // BARS
    for (int i = 0; i < width; i+=80) {
        SDL_RenderDrawLine(renderer, i, 0, i, 10);
        SDL_RenderDrawLine(renderer, i, height, i, height - 10);
    }
    for (int j = 0; j < height; j+=80) {
        SDL_RenderDrawLine(renderer, 0, j, 10, j);
        SDL_RenderDrawLine(renderer, width, j, width - 10, j);
    }

    // MIDLINE
    SDL_RenderDrawLine(renderer, 0, 400, width, 400);

    // MIDLINE BARS
    for (int k = 0; k < width; k+=80) {
        SDL_RenderDrawLine(renderer, k, 400, k, 410);
        SDL_RenderDrawLine(renderer, k, 400, k, 390);
    }

    setRendererColor(renderer, oldColor);
    //cmunss

    // TODO: FIX FONT FAILURE
    TTF_Font* Sans = TTF_OpenFont("/home/timecat/Documents/sem5/ЭВМ/labs/lab3/src/test/cmfont.ttf", 26);

    if (Sans == nullptr) {
        cout << "Error: " << TTF_GetError() << endl;
    } else {

//        SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, "40",
//                                                           {0, 0, 0});
//        SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer,
//                                                            surfaceMessage);
//        SDL_Rect Message_rect = genRect(35, 20, 40, 40);

//        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

//        TTF_CloseFont(Sans);
    }
}

int main(int argc, char *argv[]) {

    SDL_Window *window;

    SDL_Point window_position = {         //    Position of window
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED
    };
    SDL_Point window_size = {WIN_WIDTH, WIN_HEIGHT};   // Size of window

    SDL_Init(SDL_INIT_VIDEO);             //    Initialize SDL2

    // Initialize TTF
    if (TTF_Init() < 0) {
        std::cout << "Couldn't initialize SDL TTF\n";
        return -1;
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "SDL test",                //    window title
            window_position.x,                //    initial x position
            window_position.y,                //    initial y position
            window_size.x,                    //    width, in pixels
            window_size.y,                    //    height, in pixels
            SDL_WINDOW_OPENGL                 //    flags - see below
    );

    // Check that the window was successfully made
    if (window == NULL) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return 1;
    }

    // Create renderer context
    SDL_Renderer* renderer =
            SDL_CreateRenderer(window, -1,   SDL_RENDERER_ACCELERATED
                                           | SDL_RENDERER_PRESENTVSYNC);

    SDL_Rect background = genRect(0, 0, WIN_WIDTH, WIN_HEIGHT);

    SDL_RenderFillRect(renderer, &background);

    impureDrawGraph(renderer, f, WIN_WIDTH);

    impureDrawAxes(renderer, WIN_WIDTH, WIN_HEIGHT);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // TTF cleanu
    TTF_Quit();

    // Clean up
    SDL_Quit();

    return 0;
}

