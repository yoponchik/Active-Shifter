#ifndef ACTIVESHIFTER_GENERIC_H
#define ACTIVESHIFTER_GENERIC_H

#include <utility> // For std::forward

template <typename ComponentType, typename OwnerType, typename... Args>
ComponentType* CreateComponent(OwnerType* Owner, Args&&... args) {
    // 1. Allocate on Heap (Manual Memory)
    ComponentType* NewComp = new ComponentType(std::forward<Args>(args)...);

    // 2. Register it so the Owner tracks it and ticks it
    Owner->RegisterComponent(NewComp);

    // 3. Return the pointer so you can store it
    return NewComp;
}

#endif //ACTIVESHIFTER_GENERIC_H