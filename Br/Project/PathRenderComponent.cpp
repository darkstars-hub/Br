#include "PathRenderComponent.h"

#include "Helper.h"


br::PathRenderComponent::PathRenderComponent(br::Actor* owner, int priority) :
    super(owner, priority),
    _path(nullptr) {
    super::_type = ComponentType::PathRenderComponent;
}

br::PathRenderComponent::~PathRenderComponent() {
}

void br::PathRenderComponent::SetPath(std::vector<br::PathDataPointer>* path) {
    this->_path = path;
}

bool br::PathRenderComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool br::PathRenderComponent::Update(void) {
    return true;
}

bool br::PathRenderComponent::Render(Mof::CVector2 scroll) {
    if (!_path) {
        return true;
    } // if
    for (auto t : *_path) {
        auto size = def::kChipSize;
        auto pos = t->_tile->GetPosition();
        auto rect = Mof::CRectangle(pos.x, pos.y,
                                    pos.x + size, pos.y + size);
        rect.Translation(-scroll);
        ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(66, 0, 255, 0));
    } // for
    return true;
}

bool br::PathRenderComponent::Release(void) {
    return true;
}

br::Component* br::PathRenderComponent::Clone(void) {
    auto ptr = new br::PathRenderComponent(nullptr, _priority);
    return ptr;
}
