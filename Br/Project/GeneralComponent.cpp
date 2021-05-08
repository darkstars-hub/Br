#include "GeneralComponent.h"

#include "Unit.h"
#include "EffectManager.h"


br::GeneralComponent::GeneralComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::GeneralComponent;
    super::_resource_path =
        "Resource/sprites/general/general.sprite";
}

br::GeneralComponent::~GeneralComponent() {
}

void br::GeneralComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::General);
    super::_state->SetMoveCount(4);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(50);
    super::_hp->SetHp(50);
    _state->GetStatus()->SetData(10, 5, 0, 5, 100, 5);
}

bool br::GeneralComponent::Fusion(Unit& target) {
    //auto e = super::_owner->GetScene()->GetEffectManager();
    //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
    return false;
}

bool br::GeneralComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::GeneralComponent::Update(void) {
    return true;
}

bool br::GeneralComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::GeneralComponent::Release(void) {
    return true;
}

br::Component* br::GeneralComponent::Clone(void) {
    auto ptr = new GeneralComponent(nullptr, this->_priority);
    return ptr;
}