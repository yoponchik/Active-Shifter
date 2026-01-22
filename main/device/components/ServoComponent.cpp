#include "ServoComponent.h"
#include <iostream>

ServoComponent::ServoComponent(gpio_num_t InPin, ledc_channel_t InChannel)
    : ConnectedPin(InPin), LEDCChannel(InChannel), CurrentAngle(90.0) {}

uint32_t ServoComponent::ConvertMicroSecondsToDuty(int InMicroseconds) {
    return (InMicroseconds * 16384) / 20000;
}

void ServoComponent::Init() {
    ledc_timer_config_t timerConf = {};
    timerConf.speed_mode = MODE;
    timerConf.duty_resolution = RES;
    timerConf.timer_num = TIMER;
    timerConf.freq_hz = FREQ_HZ;
    timerConf.clk_cfg = LEDC_AUTO_CLK;
    ledc_timer_config(&timerConf);

    ledc_channel_config_t chanConf = {};
    chanConf.gpio_num = ConnectedPin;
    chanConf.speed_mode = MODE;
    chanConf.channel = LEDCChannel;
    chanConf.timer_sel = TIMER;
    chanConf.duty = 0;
    chanConf.hpoint = 0;
    chanConf.sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD;
    ledc_channel_config(&chanConf);

    std::cout << "[ServoComponent] Attached to Pin " << ConnectedPin << ".\n";
    SetAngle(InitialAngle);
}

void ServoComponent::Tick(float DeltaTime) {

}

void ServoComponent::SetAngle(double InAngle) {
    if (InAngle < 0) InAngle = 0;
    if (InAngle > 180) InAngle = 180;
    
    CurrentAngle = InAngle;

    uint32_t PulseWidth = 500 + (((2500 - 500) * InAngle) / 180);
    ledc_set_duty(MODE, LEDCChannel, ConvertMicroSecondsToDuty(PulseWidth));
    ledc_update_duty(MODE, LEDCChannel);
}