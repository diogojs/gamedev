/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = nullptr;
SDL_Surface *screenSurface = nullptr;
SDL_Surface *imgSurface = nullptr;

bool initSDL() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  // The window we'll be rendering to
  window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
    return false;
  }

  // The surface contained by the window
  screenSurface = SDL_GetWindowSurface(window);
  return true;
}

SDL_Surface* loadSurface(std::string path) {
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == nullptr) return nullptr;

  SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
  if (optimizedSurface == nullptr) {
    std::cout << "Error loading img " << path << std::endl;
  }
  SDL_FreeSurface(loadedSurface);

  return optimizedSurface;
}

bool loadMedia() {
    imgSurface = loadSurface("./hello_world.bmp");
    if (imgSurface == nullptr) {
        std::cout << "Unable to load img: hello_world.bmp\n"
                  << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void closeSDL() {
    SDL_FreeSurface(imgSurface);
    imgSurface = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

int main(int argc, char *args[]) {

  if (!initSDL()) return -1;

  if (!loadMedia()) return -1;

  // Apply img
  SDL_BlitSurface(imgSurface, nullptr, screenSurface, nullptr);

  // Update the surface
  SDL_UpdateWindowSurface(window);

  // Wait two seconds
  SDL_Delay(2000);

  closeSDL();

  return 0;
}
