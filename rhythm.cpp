#include "gfx.hpp"
#include "menu.hpp"

int main() {
    gfxInit("Rhythm Engine");

    Menu menu;

    while (gfxPoll()) {
        gfxClear(50,10,50);
        menu.update();
        menu.draw();
    }
}
