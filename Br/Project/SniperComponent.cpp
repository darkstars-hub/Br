#include "SniperComponent.h"

#include "Unit.h"
#include "EffectManager.h"


br::SniperComponent::SniperComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::SniperComponent;
    super::_resource_path =
        "Resource/sprites/sniper/sniper.sprite";
}

br::SniperComponent::~SniperComponent() {
}

void br::SniperComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Sniper);
    super::_state->SetMoveCount(4);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(30);
    super::_hp->SetHp(30);
    _state->GetStatus()->SetData(10, 3, 0, 5, 100, 5);
}

bool br::SniperComponent::Fusion(Unit& target) {
    //auto e = super::_owner->GetScene()->GetEffectManager();
    //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
    return false;
}

bool br::SniperComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::SniperComponent::Update(void) {
    return true;
}

bool br::SniperComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::SniperComponent::Release(void) {
    return true;
}

br::Component* br::SniperComponent::Clone(void) {
    auto ptr = new SniperComponent(nullptr, this->_priority);
    return ptr;
}