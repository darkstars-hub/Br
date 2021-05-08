#include "ArcherComponent.h"

#include "Unit.h"
#include "SniperComponent.h"
#include "LightCavalryComponent.h"
#include "HunterComponent.h"
#include "EffectManager.h"
#include "ArcherRange.h"
#include "Stage.h"


br::ArcherComponent::ArcherComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::ArcherComponent;
    super::_resource_path =
        "Resource/sprites/archer/archer.sprite";
}

br::ArcherComponent::~ArcherComponent() {
}

void br::ArcherComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Archer);
    super::_state->SetMoveCount(1);


    const def::Vector2i up = { 0,-2 };
    const def::Vector2i down = { 0,2 };
    const def::Vector2i left = { -2, 0 };
    const def::Vector2i right = { 2, 0 };
    const def::Vector2i direction[] = {
        up,        down,        left,        right,
    };
    auto range = std::vector<def::Vector2i>(std::begin(direction), std::end(direction));
    super::_state->SetAttackRange(range);


    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(20);
    super::_hp->SetHp(20);
    _state->GetStatus()->SetData(8, 3, 0, 5, 90, 5);
}

std::shared_ptr<br::IRangeAlgorithm> br::ArcherComponent::GetRangeAlgorithm(void) {
    return std::make_shared<br::ArcherRange>(super::_owner->GetScene()->GetStage());
}

bool br::ArcherComponent::Fusion(Unit& target) {
    br::UnitJobComponent* c;
    switch (target.GetUnitType()) {
        case br::UnitType::Archer:
            c = new br::SniperComponent(nullptr, super::_priority);
            break;
        case br::UnitType::Cavalry:
            c = new br::LightCavalryComponent(nullptr, super::_priority);
            break;
        case br::UnitType::Hoplite:
            c = new br::HunterComponent(nullptr, super::_priority);
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

bool br::ArcherComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::ArcherComponent::Update(void) {
    return true;
}

bool br::ArcherComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::ArcherComponent::Release(void) {
    return true;
}

br::Component* br::ArcherComponent::Clone(void) {
    auto ptr = new ArcherComponent(nullptr, this->_priority);
    return ptr;
}