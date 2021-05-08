#include "LightCavalryComponent.h"
#include "Unit.h"
#include "EffectManager.h"

br::LightCavalryComponent::LightCavalryComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::LightCavalryComponent;
    super::_resource_path =
        "Resource/sprites/light_cavalry/light_cavalry.sprite";
}

br::LightCavalryComponent::~LightCavalryComponent() {
}

void br::LightCavalryComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::LightCavalry);
    super::_state->SetMoveCount(6);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(30);
    super::_hp->SetHp(30);
    _state->GetStatus()->SetData(7, 4, 0, 5, 95, 5);
}
bool br::LightCavalryComponent::Fusion(Unit& target) {
    //auto e = super::_owner->GetScene()->GetEffectManager();
    //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
    return false;
}
bool br::LightCavalryComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::LightCavalryComponent::Update(void) {
    return true;
}

bool br::LightCavalryComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::LightCavalryComponent::Release(void) {
    return true;
}

br::Component* br::LightCavalryComponent::Clone(void) {
    auto ptr = new LightCavalryComponent(nullptr, this->_priority);
    return ptr;
}