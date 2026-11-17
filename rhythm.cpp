#include "gfx.hpp"

int main() {
    gfxInit("Rhythm Engine");

    while (gfxPoll()) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderLine(renderer, 0, 0, 100, 100);
        SDL_RenderPresent(renderer);
    }
}