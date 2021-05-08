#include "UnitStatus.h"

#include "HpComponent.h"


br::UnitStatus::UnitStatus() :
    _attack(0),
    _defence(0),
    _magic_attack(0),
    _magic_defence(0),
    _hit(0),
    _avoid(0),
    _hp(nullptr) {
}

br::UnitStatus::~UnitStatus() {
}

void br::UnitStatus::SetData(int attack, int defence, int magic_attack, int magic_defence, int hit, int avoid) {
    this->_attack = attack;
    this->_defence = defence;
    this->_magic_attack= magic_attack;
    this->_magic_defence = magic_defence;
    this->_hit = hit;
    this->_avoid = avoid;
}

void br::UnitStatus::SetHp(HpComponent* component) {
    _hp = component;
}

int br::UnitStatus::GetHpMax(void) {
    return _hp->GetMaxValue();
}

int br::UnitStatus::GetHp(void) {
    return _hp->GetValue();
}

int br::UnitStatus::GetAttack(void) {
    return this->_attack;
}

int br::UnitStatus::GetDefence(void) {
    return this->_defence;
}

int br::UnitStatus::GetMagicAttack(void) {
    return this->_magic_attack;
}

int br::UnitStatus::GetMagicDefence(void) {
    return this->_magic_defence;
}

int br::UnitStatus::GetHit(void) {
    return this->_hit;
}

int br::UnitStatus::GetAvoid(void) {
    return this->_avoid;
}