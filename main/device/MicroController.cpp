#include "device/MicroController.h"
#include "components/ServoComponent.h"
#include "utils/Generic.h"
#include "esp_timer.h"
#include "esp_task_wdt.h" // Required for Watchdog
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <iostream>
#include <algorithm>

MicroController::MicroController() {
    // Outputs
    ShifterServo = CreateComponent<ServoComponent>(this, GPIO_NUM_18, LEDC_CHANNEL_0);
    ClutchServo  = CreateComponent<ServoComponent>(this, GPIO_NUM_19, LEDC_CHANNEL_1);

}

void MicroController::RegisterComponent(BaseComponent* InComponent) {
    if (!InComponent) return;

    InComponent->SetOwner(this);
    Components.push_back(std::unique_ptr<BaseComponent>(InComponent));

    if (InComponent->IsTickEnabled()) {
        ActiveTickComponents.push_back(InComponent);
    }
}

void MicroController::MarkActiveTickComponent(BaseComponent* InComponent, bool bEnabled) {
    if (!InComponent) return;

    if (bEnabled) {
        auto it = std::find(ActiveTickComponents.begin(), ActiveTickComponents.end(), InComponent);
        if (it == ActiveTickComponents.end()) {
            ActiveTickComponents.push_back(InComponent);
        }
    } else {
        ActiveTickComponents.erase(
            std::remove(ActiveTickComponents.begin(), ActiveTickComponents.end(), InComponent),
            ActiveTickComponents.end()
        );
    }
}

void MicroController::Init() {
    std::cout << "=================================\n";
    std::cout << "   SYSTEM INITIALIZING           \n";
    std::cout << "=================================\n";

    // Initialize Watchdog for this task (Safe timeout 5 seconds)
    // This allows us to remove vTaskDelay but ensures we don't hang forever.
    // UPDATED FOR ESP-IDF v5+: Uses configuration struct instead of params
    esp_task_wdt_config_t twdt_config = {
        .timeout_ms = 5000,
        .idle_core_mask = (1 << portNUM_PROCESSORS) - 1, // Watch idle tasks on all available cores
        .trigger_panic = true,
    };
    esp_task_wdt_init(&twdt_config);

    esp_task_wdt_add(NULL); // Add current task to WDT

    for (const auto& Comp : Components) {
        Comp->Init();
    }
    std::cout << "[System] Board Online. Logic Started.\n";

    LogicTimer = 0.0f;
    LogicState = 0;
}

[[noreturn]] void MicroController::Run() {
    std::cout << "[System] Main Loop Started (Performance Mode).\n";

    int64_t LastTime = esp_timer_get_time();

    while (true) {
        // 1. Calculate Delta Time
        int64_t Now = esp_timer_get_time();
        float DeltaTime = (float)(Now - LastTime) / 1000000.0f;
        LastTime = Now;

        // Cap DeltaTime to prevent physics explosions on hiccups
        if(DeltaTime > 0.1f) DeltaTime = 0.1f;

        // 2. Run Logic
        Tick(DeltaTime);

        // 3. MANUAL WATCHDOG FEED
        // Since we removed vTaskDelay, we MUST feed the dog here.
        esp_task_wdt_reset();

        // NO DELAY: The loop restarts instantly.
    }
}

void MicroController::SampleCode(float InDeltaTime) {

}

void MicroController::Tick(float DeltaTime) {
    DriveComponentTick(DeltaTime);
    SampleCode(DeltaTime);
}

void MicroController::DriveComponentTick(float DeltaTime) {
    for (auto* Comp : ActiveTickComponents) {
        Comp->Tick(DeltaTime);
    }
}

MicroController::~MicroController() {
    Components.clear();
    ActiveTickComponents.clear();
}