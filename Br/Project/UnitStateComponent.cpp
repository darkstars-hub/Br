#include "UnitStateComponent.h"

#include "UnitMoveComponent.h"
#include "HpComponent.h"
#include "Helper.h"
#include "Stage.h"
#include "AudioSystem.h"
#include "UnitJobComponent.h"


br::UnitStateComponent::UnitStateComponent(Actor* owner, int priority) :
    super(owner, priority),
    _unit_type(),
    _move_count(0),
    _select(nullptr),
    _move(nullptr),
    _team(def::kPlayerTeam),
    _is_active(true),
    _attack_range(),
    _hp(nullptr),
    _status() {
    super::_type = ComponentType::UnitStateComponent;
}

br::UnitStateComponent::~UnitStateComponent() {
}

br::UnitStatus* br::UnitStateComponent::GetStatus(void) {
    return &this->_status;
}

br::Tile* br::UnitStateComponent::GetCurrentTile(void) {
    auto pos = ut::ToGridPos(super::_owner->GetPosition());
    return super::_owner->GetScene()->GetStage()->GetTile(pos.col, pos.row);
}

int br::UnitStateComponent::GetMoveCount(void) const {
    return this->_move_count;
}

std::vector<def::Vector2i>& br::UnitStateComponent::GetAttackRange(void) {
    return this->_attack_range;
}

br::UnitType br::UnitStateComponent::GetUnitType(void) {
    return this->_unit_type;
}

void br::UnitStateComponent::SetUnitType(br::UnitType type) {
    this->_unit_type = type;
}

void br::UnitStateComponent::SetTeam(const char* type) {
    this->_team = type;
}

void br::UnitStateComponent::SetActive(const bool state) {
    this->_is_active = state;
}

void br::UnitStateComponent::SetMoveCount(int count) {
    this->_move_count = count;
}

void br::UnitStateComponent::SetAttackRange(std::vector<def::Vector2i>& range) {
    this->_attack_range = range;
}

const char* br::UnitStateComponent::GetTeam(void) {
    return this->_team;
}

bool br::UnitStateComponent::IsActive(void) const {
    return this->_is_active;
}

br::HpComponent* br::UnitStateComponent::GetHp(void) {
    return this->_hp;
}

bool br::UnitStateComponent::Initialize(void) {
    _select = _owner->GetComponent<br::SelectableComponent>();
    _move = _owner->GetComponent<br::UnitMoveComponent>();
    _hp = _owner->GetComponent<br::HpComponent>();
    _status.SetHp(_hp);
    return true;
}

bool br::UnitStateComponent::Update(void) {
    return true;
}

bool br::UnitStateComponent::Render(Mof::CVector2 scroll) {
    return true;
}

br::Component* br::UnitStateComponent::Clone(void) {
    auto ptr = new br::UnitStateComponent(nullptr, _priority);
    ptr->_team = this->_team;
    ptr->_type = this->_type;
    ptr->_move_count = this->_move_count;
    return ptr;
}