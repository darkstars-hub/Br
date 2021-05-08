#include "BattleSystemUnitInfomation.h"

#include <string>


br::BattleSystemUnitInfomation::BattleSystemUnitInfomation()
    :_position(),
    _size(Mof::CVector2(300.0f, 180.0f)),
    _unit(nullptr) {
}

br::BattleSystemUnitInfomation::~BattleSystemUnitInfomation() {
}

void br::BattleSystemUnitInfomation::SetUnit(br::BattleSystemUnit* ptr) {
    this->_unit = ptr;
}

void br::BattleSystemUnitInfomation::SetPosition(Mof::CVector2 position) {
    this->_position = position;
}

Mof::CVector2 br::BattleSystemUnitInfomation::GetSize(void) {
    return this->_size;
}

void br::BattleSystemUnitInfomation::Render(void) {
    auto rect = Mof::CRectangle(
        _position.x,
        _position.y,
        _position.x + _size.x,
        _position.y + _size.y);
    ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(200, 0, 200, 200));

    using namespace std;
    auto u = _unit->GetUnit();
    auto status = u->GetStateComponent()->GetStatus();
    auto text = string();
    auto add = [&text](const char* state, int value) {
        text += state; text += std::to_string(value);
    };
    text += u->GetName(); text += "\n";
    add("hp      : ", status->GetHp()); 
    add("/"         , status->GetHpMax());   text += "\n";
    add("attack  : ", status->GetAttack());  text += "\n";
    add("defence : ", status->GetDefence()); text += "\n";
    add("magic attack  : ", status->GetMagicAttack());  text += "\n";
    add("magic defence : ", status->GetMagicDefence()); text += "\n";
    add("hit     : ", status->GetHit());     text += "\n";
    add("avoid   : ", status->GetAvoid());   text += "\n";
    ::CGraphicsUtilities::RenderString(
        _position.x,
        _position.y,
        text.c_str());
}