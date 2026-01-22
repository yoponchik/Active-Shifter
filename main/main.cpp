#include "./device/MicroController.h"

MicroController Board;

extern "C" void app_main(void) {
    // Boot
    Board.Init();
    Board.Run();
}