#include "components/BaseComponent.h"
#include "device/MicroController.h"

void BaseComponent::SetTickEnabled(bool bEnabled) {
    // 1. Update internal state
    bTickEnabled = bEnabled;

    // 2. Notify the Owner to move us to/from the Active list
    if (Owner) {
        Owner->MarkActiveTickComponent(this, bEnabled);
    }
}

bool BaseComponent::IsTickEnabled() const {
    return bTickEnabled;
}

void BaseComponent::SetOwner(MicroController* InOwner) {
    Owner = InOwner;
}

MicroController* BaseComponent::GetOwner() const {
    return Owner;
}