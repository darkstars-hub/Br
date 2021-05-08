#include "RangeRenderComponent.h"

#include "Helper.h"


br::RangeRenderComponent::RangeRenderComponent(br::Actor* owner, int priority) :
    super(owner, priority),
    _range(nullptr),
    _attack_range(nullptr),
    _fusion_range(nullptr),
    _sight_range(nullptr),
    _select(nullptr) {
    super::_type = ComponentType::RangeRenderComponent;
}

br::RangeRenderComponent::~RangeRenderComponent() {
}

void br::RangeRenderComponent::SetRange(std::vector<br::RangeDataPointer>* range) {
    this->_range = range;
}

void br::RangeRenderComponent::SetAttackRange(std::vector<br::Tile*>* range) {
    this->_attack_range = range;
}

void br::RangeRenderComponent::SetFusionRange(std::vector<br::Tile*>* range) {
    this->_fusion_range = range;
}

void br::RangeRenderComponent::SetSightRange(std::vector<br::RangeDataPointer>* range) {
    this->_sight_range = range;
}

bool br::RangeRenderComponent::Initialize(void) {
    super::Initialize();
    _select = _owner->GetComponent<br::SelectableComponent>();
    return true;
}

bool br::RangeRenderComponent::Update(void) {
    return true;
}

bool br::RangeRenderComponent::Render(Mof::CVector2 scroll) {
    if (_range) {
        // ˆÚ“®”ÍˆÍ•`‰æ
        for (auto t : *_range) {
            auto size = def::kChipSize;
            auto pos = t->_tile->GetPosition();
            auto rect = Mof::CRectangle(pos.x, pos.y,
                                        pos.x + size, pos.y + size);
            rect.Translation(-scroll);

            int a = 60;
            if (_select->IsSelected()) {
                a += 50;
            } // if
            ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(a, 0, 0, 200));
        } // for
    } // if

    // UŒ‚”ÍˆÍ•`‰æ
    if (_attack_range) {
        for (auto t : *_attack_range) {
            auto size = def::kChipSize;
            auto pos = t->GetPosition();
            auto rect = Mof::CRectangle(pos.x, pos.y,
                                        pos.x + size, pos.y + size);
            rect.Translation(-scroll);

            int a = 100;
            if (_select->IsSelected()) {
                a += 50;
            } // if
            ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(a, 200, 0, 0));
        } // for
    } // if

    // ‡‘Ì”ÍˆÍ•`‰æ
    if (_fusion_range) {
        for (auto t : *_fusion_range) {
            auto size = def::kChipSize;
            auto pos = t->GetPosition();
            auto rect = Mof::CRectangle(pos.x, pos.y,
                                        pos.x + size, pos.y + size);
            rect.Translation(-scroll);

            int a = 100;
            if (_select->IsSelected()) {
                a += 50;
            } // if
            ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(a, 200, 0, 200));
        } // for
    } // if

    // ‰ÂŽ‹”ÍˆÍ•`‰æ
    if (_sight_range) {
        for (auto p : *_sight_range) {
            auto size = def::kChipSize;
            auto pos = p->_tile->GetPosition();
            auto rect = Mof::CRectangle(pos.x, pos.y,
                                        pos.x + size, pos.y + size);
            rect.Translation(-scroll);

            int a = 100;
            if (_select->IsSelected()) {
                a += 50;
            } // if
            ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(a, 200, 200, 0));
        } // for
    } // if

    return true;
}

bool br::RangeRenderComponent::Release(void) {
    return true;
}

br::Component* br::RangeRenderComponent::Clone(void) {
    auto ptr = new br::RangeRenderComponent(nullptr, _priority);
    return ptr;
}