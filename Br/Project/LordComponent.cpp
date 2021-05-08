#include "LordComponent.h"

#include "Unit.h"
#include "EffectManager.h"


br::LordComponent::LordComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::LordComponent;
    super::_resource_path =
        "Resource/sprites/lord/lord.sprite";
}

br::LordComponent::~LordComponent() {
}

void br::LordComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Lord);
    super::_state->SetMoveCount(4);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(40);
    super::_hp->SetHp(40);
    _state->GetStatus()->SetData(10, 5, 0, 5, 100, 10);

}
bool br::LordComponent::Fusion(Unit& target) {
    //auto e = super::_owner->GetScene()->GetEffectManager();
    //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
    return false;
}
bool br::LordComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::LordComponent::Update(void) {
    return true;
}

bool br::LordComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::LordComponent::Release(void) {
    return true;
}

br::Component* br::LordComponent::Clone(void) {
    auto ptr = new LordComponent(nullptr, this->_priority);
    return ptr;
}