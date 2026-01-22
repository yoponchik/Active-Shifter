#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

// Forward declaration to avoid circular dependency
class MicroController;

class BaseComponent {
protected:
    bool bTickEnabled = true;
    // Necessary for the Component to notify the Controller of state changes
    MicroController* Owner = nullptr;

public:
    virtual ~BaseComponent() = default;

    virtual void Init() = 0;
    virtual void Tick(float DeltaTime) = 0;

    bool IsTickEnabled() const;

    void SetTickEnabled(bool bEnabled);

    void SetOwner(MicroController* InOwner);
    MicroController* GetOwner() const;

};

#endif // BASECOMPONENT_H