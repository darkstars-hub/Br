#include "UnitJobComponent.h"
#include "LightCavalryComponent.h"
#include "Unit.h"
#include "UnitRange.h"


br::UnitJobComponent::UnitJobComponent(Actor* owner, int priority) :
    super(owner, priority),
    _resource_path(),
    _unit(nullptr),
    _state(nullptr),
    _motion(nullptr),
    _texture(nullptr),
    _hp(nullptr) {
    super::_type = br::ComponentType::UnitJobComponent;
}

br::UnitJobComponent::~UnitJobComponent() {
}

br::Unit* br::UnitJobComponent::GetOwnerUnit(void) const {
    return this->_unit;
}

std::shared_ptr<br::IRangeAlgorithm> br::UnitJobComponent::GetRangeAlgorithm(void) {
    return std::make_shared<br::UnitRange>();
}
/*
void br::UnitJobComponent::Fusion(br::Unit& target) {
//    target.SetActive(false);
    target.Damege(99);
    auto c = new br::LightCavalryComponent(nullptr, super::_priority);
    c->SetOwner(super::_owner);
    c->Initialize();
    _unit->SetJobComponent(c);
  //  _hp->SetMaxHp(50); _hp->Heal(50);
    super::_owner->RemoveComponent(this);
}
*/

bool br::UnitJobComponent::Initialize(void) {
    super::Initialize();
    _unit = dynamic_cast<br::Unit*>(super::_owner);
    _state = _owner->GetComponent<br::UnitStateComponent>();
    _motion = _owner->GetComponent<br::MotionComponent>();
    _texture = _owner->GetComponent<br::UnitTextureComponent>();
    _hp = _owner->GetComponent<br::HpComponent>();
    this->RegisterType();
    return true;
}

bool br::UnitJobComponent::Update(void) {
    return true;
}

bool br::UnitJobComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::UnitJobComponent::Release(void) {
    _unit = nullptr;
    return true;
}