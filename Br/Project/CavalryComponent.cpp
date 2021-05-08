#include "CavalryComponent.h"

#include "Unit.h"
#include "ChariotComponent.h"
#include "LightCavalryComponent.h"
#include "HeavyCavalryComponent.h"
#include "EffectManager.h"

br::CavalryComponent::CavalryComponent(Actor* owner, int priority) :
    super(owner, priority){
    super::_type = ComponentType::CavalryComponent;
    super::_resource_path =
        "Resource/sprites/cavalry/cavalry.sprite";
}

br::CavalryComponent::~CavalryComponent() {
}

void br::CavalryComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Cavalry);
    super::_state->SetMoveCount(5);
    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(20);
    super::_hp->SetHp(20);
    _state->GetStatus()->SetData(6, 4, 0, 2, 95, 5);
}

bool br::CavalryComponent::Fusion(Unit& target) {
    br::UnitJobComponent* c;
    switch (target.GetUnitType()) {
        case br::UnitType::Archer:
            c = new br::LightCavalryComponent(nullptr, super::_priority);
            break;
        case br::UnitType::Cavalry:
            c = new br::ChariotComponent(nullptr, super::_priority);
            break;
        case br::UnitType::Hoplite:
            c = new br::HeavyCavalryComponent(nullptr, super::_priority);
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

bool br::CavalryComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::CavalryComponent::Update(void) {
    return true;
}

bool br::CavalryComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::CavalryComponent::Release(void) {
    return true;
}

br::Component* br::CavalryComponent::Clone(void) {
    auto ptr = new CavalryComponent(nullptr, this->_priority);
    return ptr;
}