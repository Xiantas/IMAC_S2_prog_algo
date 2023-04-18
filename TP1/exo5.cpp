#include <SDL2/SDL.h>
#include <iostream>

///Pas besoin de typedef en C++
struct Point {
    double x, y; ///Vive la précision
};

Point operator+(const Point& p1, const Point& p2) {
    return Point{p1.x+p2.x, p1.y+p2.y};
}

Point operator*(const Point& p1, const Point& p2) {
    return Point{p1.x*p2.x-p1.y*p2.y, p1.x*p2.y+p1.y*p2.x};
}

bool isMandelbrot(Point z, int n, Point point) {
    // recursiv Mandelbrot
    // check length of z
    if (z.x*z.x+z.y*z.y > 4) return false;

    // check n
    if (n <= 0) return true;
    // if Mandelbrot, return 1 or n (check the difference)
    // otherwise, process the square of z and recall
    // isMandebrot
    return isMandelbrot(z*z+point, n-1, point);
}

bool handleEvents() {
    SDL_Event e; 
    while (SDL_PollEvent(&e)){ 
        if (e.type == SDL_QUIT) 
            return false; 
    }
    return true;
}

int main(int argc, char *argv[]) {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    //Create window
    SDL_Window* gWindow = SDL_CreateWindow( 
        "Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 800, SDL_WINDOW_SHOWN);

    if( gWindow == NULL )
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(gWindow, -1, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    for (double y = -2.0; y < 2.0; y += 1.0/200.0) {
        for (double x = -2.0; x < 2.0; x += 1.0/200.0) {
            SDL_SetRenderDrawColor(
                renderer,
                isMandelbrot(Point{0.0, 0.0}, 20, Point{x, y}) ? 255 : 0,
                0, 0, 255);
            SDL_RenderDrawPoint(renderer, (x+2)*200, (2-y)*200);
        }
    }

    SDL_RenderPresent(renderer);

    bool is_running = true;
    while (is_running) {
        is_running = handleEvents();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( gWindow );
    SDL_Quit();
}
