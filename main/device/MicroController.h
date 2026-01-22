#ifndef ACTIVESHIFTER_MICROCONTROLLER_H
#define ACTIVESHIFTER_MICROCONTROLLER_H

#include <memory>
#include <vector>
#include "components/BaseComponent.h"

class ServoComponent;
class HallSensorComponent; // Forward Declaration

class MicroController {
protected:
    std::vector<std::unique_ptr<BaseComponent>> Components;
    std::vector<BaseComponent*> ActiveTickComponents;

public:
    MicroController();
    virtual ~MicroController();

    void RegisterComponent(BaseComponent* InComponent);
    void MarkActiveTickComponent(BaseComponent* InComponent, bool bEnabled);

    // Logic
    void SampleCode(float InDeltaTime);

private:
    // Outputs
    ServoComponent* ShifterServo;
    ServoComponent* ClutchServo;

    // Inputs (Sensors)
    HallSensorComponent* UpshiftSensor;
    HallSensorComponent* DownshiftSensor;

    // Logic State variables
    float LogicTimer;
    int LogicState;

    void DriveComponentTick(float DeltaTime);

public:
    void Init();
    [[noreturn]] void Run();
    void Tick(float DeltaTime);
};

#endif //ACTIVESHIFTER_MICROCONTROLLER_H