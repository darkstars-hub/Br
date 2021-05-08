#include "HopliteComponent.h"

#include "Unit.h"
#include "GeneralComponent.h"
#include "HeavyCavalryComponent.h"
#include "HunterComponent.h"
#include "EffectManager.h"


br::HopliteComponent::HopliteComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::HopliteComponent;
    super::_resource_path =
        "Resource/sprites/hoplite/hoplite.sprite";
}

br::HopliteComponent::~HopliteComponent() {
}

void br::HopliteComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Hoplite);
    super::_state->SetMoveCount(3);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(30);
    super::_hp->SetHp(30);
    _state->GetStatus()->SetData(7, 5, 0, 1, 100, 0);
}
bool br::HopliteComponent::Fusion(Unit& target) {
    br::UnitJobComponent* c;
    switch (target.GetUnitType()) {
        case br::UnitType::Archer:
            c = new br::HunterComponent(nullptr, super::_priority);
            break;
        case br::UnitType::Cavalry:
            c = new br::HeavyCavalryComponent(nullptr, super::_priority);
            break;
        case br::UnitType::Hoplite:
            c = new br::GeneralComponent(nullptr, super::_priority);
            break;
        default:
            //auto e = super::_owner->GetScene()->GetEffectManager();
            //e->Start("Resource/sprites/miss_effect/miss_effect.sprite", target.GetPosition());
            return false;
    } // switch
    target.Damege(99);
    c->SetOwner(super::_owner);
    c->Initialize();
    _unit->SetJobComponent(c);

    _unit->AddComponent(c);
    _unit->AddUpdateComponent(c);

    super::_owner->RemoveComponent(this);
    return true;
}
bool br::HopliteComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::HopliteComponent::Update(void) {
    return true;
}

bool br::HopliteComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::HopliteComponent::Release(void) {
    return true;
}

br::Component* br::HopliteComponent::Clone(void) {
    auto ptr = new HopliteComponent(nullptr, this->_priority);
    return ptr;
}