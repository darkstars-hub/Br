#include "HealerComponent.h"

#include "Unit.h"
#include "EffectManager.h"


br::HealerComponent::HealerComponent(Actor* owner, int priority) :
    super(owner, priority) {
    super::_type = ComponentType::HealerComponent;
    super::_resource_path =
        "Resource/sprites/healer/healer.sprite";
}

br::HealerComponent::~HealerComponent() {
}

void br::HealerComponent::RegisterType(void) {
    auto r = super::_owner->GetScene()->GetResourceManager();
    super::_state->SetUnitType(br::UnitType::Healer);
    super::_state->SetMoveCount(4);
//    super::_state->SetAttackRange(std::vector<def::Vector2i>(std::begin(def::VDirection), std::end(def::VDirection)));
    super::_state->SetAttackRange(std::vector<def::Vector2i>());
    super::_motion->MakeAnimation(r, super::_resource_path);
    super::_texture->SetTexture(r->GetSpritePart(super::_resource_path)->GetTexture());
    super::_hp->SetMaxHp(20);
    super::_hp->SetHp(20);
    _state->GetStatus()->SetData(10, 5, 0, 5, 100, 10);

}
bool br::HealerComponent::Fusion(Unit& target) {
    return false;
}
bool br::HealerComponent::Initialize(void) {
    super::Initialize();
    super::_unit->SetJobComponent(this);
    return true;
}

bool br::HealerComponent::Update(void) {
    return true;
}

bool br::HealerComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::HealerComponent::Release(void) {
    return true;
}

br::Component* br::HealerComponent::Clone(void) {
    auto ptr = new HealerComponent(nullptr, this->_priority);
    return ptr;
}