#include "RangeComponent.h"

#include "ArcherRange.h"
#include "UnitRange.h"


br::RangeComponent::RangeComponent(Actor* owner, int priority) :
    super(owner, priority),
    _range(),
    _range_render(nullptr) {
}

br::RangeComponent::~RangeComponent() {
}

const std::vector<br::RangeDataPointer>& br::RangeComponent::GetRange(void) const {
    return this->_range;
}

void br::RangeComponent::ConputeRange(br::Tile* origin, int move) {
    this->Clear();
    //ArcherRange ran(super::_owner->GetScene()->GetStage());
    // Range ran;
    //br::ArcherRange;
    auto ran = _owner->GetComponent<br::UnitJobComponent>()->GetRangeAlgorithm();
    ran->ConputeRange(origin, move, _range);
    _range_render->SetRange(&_range);
}

void br::RangeComponent::Clear(void) {
    _range.clear();
}

bool br::RangeComponent::Initialize(void) {
    _range_render = _owner->GetComponent<br::RangeRenderComponent>();
    return true;
}

bool br::RangeComponent::Update(void) {
    return false;
}

bool br::RangeComponent::Render(Mof::CVector2 scroll) {
    return false;
}

br::Component* br::RangeComponent::Clone(void) {
    auto ptr = new br::RangeComponent(nullptr, _priority);
    return ptr;
}