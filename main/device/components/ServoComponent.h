#ifndef BASESERVOCOMPONENT_H
#define BASESERVOCOMPONENT_H

#include "BaseComponent.h"
#include <driver/gpio.h>
#include <driver/ledc.h>

class ServoComponent : public BaseComponent {
private:
    gpio_num_t ConnectedPin;
    ledc_channel_t LEDCChannel;

    // Config Constants
    static constexpr int FREQ_HZ = 50;
    static constexpr ledc_timer_t TIMER = LEDC_TIMER_0;
    static constexpr ledc_mode_t MODE = LEDC_LOW_SPEED_MODE;
    static constexpr ledc_timer_bit_t RES = LEDC_TIMER_14_BIT;

    double InitialAngle = 90.0;
    double CurrentAngle;

    uint32_t ConvertMicroSecondsToDuty(int InMicroseconds);

public:
    ServoComponent(gpio_num_t InPin, ledc_channel_t InChannel);

    void Init() override;
    void Tick(float DeltaTime) override;
    void SetAngle(double InAngle);
};

#endif // BASESERVOCOMPONENT_H