#include "HunterComponent.h"
#include "Unit.h"
#include "EffectManager.h"

br::HunterComponent::HunterComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::HunterComponent;
    super::_resource_path =
        "Resource/sprites/hunter/hunter.sprite";
}

br::HunterComponent::~HunterComponent() {
}

void br::HunterComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Hunter);
    super::_state->SetMoveCount(3);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(30);
    super::_hp->SetHp(30);
    _state->GetStatus()->SetData(6, 3, 0, 5, 100, 5);
}
bool br::HunterComponent::Fusion(Unit& target) {
    //auto e = super::_owner->GetScene()->GetEffectManager();
    //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
    return false;
}

bool br::HunterComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::HunterComponent::Update(void) {
    return true;
}

bool br::HunterComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::HunterComponent::Release(void) {
    return true;
}

br::Component* br::HunterComponent::Clone(void) {
    auto ptr = new HunterComponent(nullptr, this->_priority);
    return ptr;
}