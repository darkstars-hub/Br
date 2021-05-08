#include "ChariotComponent.h"

#include "Unit.h"
#include "EffectManager.h"


br::ChariotComponent::ChariotComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::ChariotComponent;
    super::_resource_path =
        "Resource/sprites/chariot/chariot.sprite";
}

br::ChariotComponent::~ChariotComponent() {
}

void br::ChariotComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Chariot);
    super::_state->SetMoveCount(7);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(40);
    super::_hp->SetHp(40);
    _state->GetStatus()->SetData(8, 7, 0, 5, 95, 5);
}
bool br::ChariotComponent::Fusion(Unit& target) {
    //auto e = super::_owner->GetScene()->GetEffectManager();
    //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
    return false;
}

bool br::ChariotComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::ChariotComponent::Update(void) {
    return true;
}

bool br::ChariotComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::ChariotComponent::Release(void) {
    return true;
}

br::Component* br::ChariotComponent::Clone(void) {
    auto ptr = new ChariotComponent(nullptr, this->_priority);
    return ptr;
}