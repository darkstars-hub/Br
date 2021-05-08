#include "Unit.h"

#include "Helper.h"
#include "ResourceManager.h"
#include "CavalryComponent.h"
#include "UnitHealComponent.h"
#include "Stage.h"


br::Unit::Unit(br::Scene* scene) :
    super(scene),
    //_unit_type(br::UnitType::Lord),
    _state(nullptr),
    _move(nullptr),
    _attack(nullptr),
    _fusion(nullptr),
    _ai(nullptr),
    _hp(nullptr),
    _job(nullptr) {
}

br::Unit::~Unit() {
}

br::ActorState br::Unit::GetState(void) const {
    return super::_base.state;
}

Mof::CVector2 br::Unit::GetPosition(void) const {
    return super::_base.position;
}

void br::Unit::SetTeam(const char* type) {
    this->_state->SetTeam(type);
}

br::UnitType br::Unit::GetUnitType(void)const {
    return this->_state->GetUnitType();
}

def::Vector2i br::Unit::GetGridPosition(void) {
    return ut::ToGridPos(this->GetPosition());
}

const char* br::Unit::GetName(void) const {
    return super::_base.name;
}

const char* br::Unit::GetTeam(void) {
    return this->_state->GetTeam();
}

bool br::Unit::IsActive(void) {
    return this->_state->IsActive();
}

void br::Unit::SetActive(const bool state) {
    this->_state->SetActive(state);
}

br::UnitMoveComponent* br::Unit::GetMoveComponent(void) const {
    return this->_move;
}

br::UnitAttackComponent* br::Unit::GetAttackComponent(void) const {
    return this->_attack;
}

br::UnitJobComponent* br::Unit::GetJobComponent(void) const {
    return this->_job;
}

br::UnitStateComponent* br::Unit::GetStateComponent(void)  const {
    return this->_state;
}

void br::Unit::SetMoveDestination(br::Tile* ptr) {
    _move->SetDestination(ptr);
}

void br::Unit::SetAttackTarget(br::Unit* ptr) {
    this->_attack->SetTarget(ptr);
}

void br::Unit::MoveRegisterCancel(void) {
    this->_move->RegisterCancel();
}

void br::Unit::AttackStart(void) {
    this->_attack->Start();
}

void br::Unit::FusionStart(void) {
    this->_fusion->Start();
}

void br::Unit::HealStart(void) {
    auto com = super::GetComponent<br::UnitHealComponent>();
    if (!com) {
        return;
    } // if
    com->Start();
}

void br::Unit::AIStart(void) {
    if (_ai->IsInput()) {
        return;
    } // if
    this->_ai->Start();
}

bool br::Unit::IsAIInput(void) {
    return this->_ai->IsInput();
}

void br::Unit::SetJobComponent(br::UnitJobComponent* sub) {
    this->_job = sub;
}

void br::Unit::Damege(int damage) {
    // 死ぬ
    _hp->Damege(damage);
    if (_hp->GetValue() <= 0) {
        super::_base.state = br::ActorState::Dead;
    } // if
}

void br::Unit::Heal(int value) {
    // 回復
    _hp->Heal(value);
//    if (_hp->GetValue() <= 0) {
//    } // if
}

bool br::Unit::AdjacentPinchUnit(void) {
    auto stage = super::GetScene()->GetStage();
    auto team = this->GetTeam();
    for (auto t : stage->GetTile(this->GetGridPosition())->GetAdjacents()) {
        if (t && t->GetOnUnit() && t->GetOnUnit()->GetTeam() == team && t->GetOnUnit()->IsPinch()) {
            return true;
        } // if
    } // for
    return false;
}

bool br::Unit::CanAttackEnemy(void) {
    auto stage = super::GetScene()->GetStage();
    auto pos = this->GetGridPosition();
    auto team = this->GetTeam();
    for (auto v : _state->GetAttackRange()) {
        auto t = stage->GetTile(pos.col + v.x, pos.row + v.y);
        if (t && t->GetOnUnit() && t->GetOnUnit()->GetTeam() != team) {
            return true;
        } // if
    } // if
    return false;
}

bool br::Unit::IsPinch(void) {
    // HP半分でピンチ　（現在のHPがHPの最大値の半分より少なければピンチ）
    int value = _hp->GetValue();
    int max = _hp->GetMaxValue();
    return value < max * 0.5f;
}

bool br::Unit::Initialize(const br::ActorBaseState& state) {
    super::Initialize(state);
    _state = super::GetComponent<br::UnitStateComponent>();
    _move = super::GetComponent<br::UnitMoveComponent>();
    _attack = super::GetComponent<br::UnitAttackComponent>();
    _fusion = super::GetComponent<br::UnitFusionComponent>();
    _ai = super::GetComponent<br::AIComponent>();
    _hp = super::GetComponent<br::HpComponent>();
    //_job = super::GetComponent<br::UnitJobComponent>();
    return true;
}

bool br::Unit::Update(void) {
    if (this->GetState() == br::ActorState::Dead) {
        return false;
    } // if
    super::Update();
    doRemove();
    return true;
}

bool br::Unit::Render(Mof::CVector2 scroll) {
    if (this->GetState() == br::ActorState::Dead) {
        return false;
    } // if
    super::Render(scroll);
    return true;
}