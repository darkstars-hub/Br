#include "RenderComponent.h"


br::RenderComponent::RenderComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::RenderComponent;
    if (owner) {
        owner->AddRenderComponent(this);
    } // if
}

br::RenderComponent::~RenderComponent() {
}

bool br::RenderComponent::IsRender(void) {
    return true;
}

bool br::RenderComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool br::RenderComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::RenderComponent::Release(void) {
    return true;
}