#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void ActiveShifter_Main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << " on ESP32!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;

        // Blocking delay (1000ms)
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    std::cout << "Setup complete. Entering main loop...\n";

    // Standard embedded main loop
    while (true) {
        for (int i = 1; i <= 100; i++) {
            std::cout << "i = " << i << std::endl;

            // Blocking delay (1000ms)
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        // Your Active Shifter logic will eventually go here
        vTaskDelay(100 / portTICK_PERIOD_MS); // Yield to other tasks
    }
}

// ---------------------------------------------------------
// The ESP-IDF Entry Point - Main Funciton Wrapper
// ---------------------------------------------------------
extern "C" void app_main(void) {
    ActiveShifter_Main();
}