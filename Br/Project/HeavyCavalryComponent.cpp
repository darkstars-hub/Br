#include "HeavyCavalryComponent.h"

#include "Unit.h"
#include "EffectManager.h"


br::HeavyCavalryComponent::HeavyCavalryComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::HeavyCavalryComponent;
    super::_resource_path =
        "Resource/sprites/heavy_cavalry/heavy_cavalry.sprite";
}

br::HeavyCavalryComponent::~HeavyCavalryComponent() {
}

void br::HeavyCavalryComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::HeavyCavalry);
    super::_state->SetMoveCount(6);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(40);
    super::_hp->SetHp(40);
    _state->GetStatus()->SetData(7, 8, 0, 5, 100, 10);
}
bool br::HeavyCavalryComponent::Fusion(Unit& target) {
    //auto e = super::_owner->GetScene()->GetEffectManager();
    //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
    return false;
}

bool br::HeavyCavalryComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::HeavyCavalryComponent::Update(void) {
    return true;
}

bool br::HeavyCavalryComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::HeavyCavalryComponent::Release(void) {
    return true;
}

br::Component* br::HeavyCavalryComponent::Clone(void) {
    auto ptr = new HeavyCavalryComponent(nullptr, this->_priority);
    return ptr;
}