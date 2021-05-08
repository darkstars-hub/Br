#include "UpdateComponent.h"


br::UpdateComponent::UpdateComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::UpdateComponent;
    if (owner) {
        owner->AddUpdateComponent(this);
    } // if
}

br::UpdateComponent::~UpdateComponent() {
}

bool br::UpdateComponent::IsUpdate(void) {
    return true;
}

bool br::UpdateComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool br::UpdateComponent::Update(void) {
    return true;
}