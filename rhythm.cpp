#include "gfx.hpp"
#include "audio.hpp"
#include "menu.hpp"
#include "stage.hpp"

int main() {
    gfxInit("Rhythm Engine");
    audioInit();
    loadStageAssets();

    Menu menu;
    Stage test("whats-new");

    test.start();
    while (gfxPoll()) {
        if (menu.state == MENU_STAGE) {
            test.update();
            test.draw();
        } else {
            menu.update();
            menu.draw();
        }
    }
}
