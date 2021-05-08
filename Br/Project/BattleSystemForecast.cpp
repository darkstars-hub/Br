#include "BattleSystemForecast.h"

#include <Mof.h>
#include "Unit.h"
#include "UnitCompatibility.h"
#include "DamageCalculator.h"


br::BattleSystemForecast::BattleSystemForecast() :
    _is_show(false),
    _attacker(nullptr),
    _target(nullptr),
    _position() {
}

br::BattleSystemForecast::~BattleSystemForecast() {
}

void br::BattleSystemForecast::SetTarget(Unit* ptr) {
    this->_target = ptr;
}

void br::BattleSystemForecast::SetPosition(Mof::CVector2 position) {
    this->_position = position;
}

bool br::BattleSystemForecast::IsShow(void) {
    return this->_is_show;
}

void br::BattleSystemForecast::Render(void) {
    if (!_is_show) {
        return;
    } // if
    auto rect = Mof::CRectangle(0.0f, 0.0f,
                                def::kChipSize * 18,
                                def::kChipSize * 13);
    rect.Translation(_position);
    ::CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(255, 0, 0, 0));


    if (_attacker && _target) {
        auto r = br::DamageCalculator().CalculationResult(*_attacker, *_target);
        const char* text = "";
        switch (r.effective) {
            case br::UnitCompatibility::Effective::NormalEffective:
//                text = "こうかはいまひとつのようだ";
                break;
            case br::UnitCompatibility::Effective::SuperEffective:
                text = "こうかはバツグンだ";
                break;
            case br::UnitCompatibility::Effective::NotVeryEffective:
                text = "こうかはいまひとつのようだ";
                break;
            default:
                break;
        } // switch
        auto y = rect.GetCenter().y;
        auto s0 = _attacker->GetStateComponent()->GetStatus();
        auto s1 = _target->GetStateComponent()->GetStatus();
        
        ::CGraphicsUtilities::RenderString(rect.Left, y,
                                           "%s", _attacker->GetName());
        ::CGraphicsUtilities::RenderString(rect.GetCenter().x, y,
                                           "%s", _target->GetName());
        y += 30.0f;

        ::CGraphicsUtilities::RenderString(rect.Left, y,
                                           "HP  %d / %d", s0->GetHp(), s0->GetHpMax());
        ::CGraphicsUtilities::RenderString(rect.GetCenter().x, y,
                                           "HP  %d / %d", s1->GetHp(), s1->GetHpMax());


        y += 60.0f;
        ::CGraphicsUtilities::RenderString(rect.Left, y,
                                           "戦闘結果");
        y += 30.0f;
        ::CGraphicsUtilities::RenderString(rect.Left, y,
                                           "ダメージ  %d", r.value);
        y += 30.0f;
        ::CGraphicsUtilities::RenderString(rect.Left, y,
                                           "実効命中  %d", r.hit);
        y += 30.0f;
        ::CGraphicsUtilities::RenderString(rect.Left, y,
                                           "%s", text);
    } // if
}

void br::BattleSystemForecast::Show(class Unit* attacker, class Unit* target) {
    this->_is_show = true;

    _attacker = attacker;
    _target = target;
}
void br::BattleSystemForecast::Hide(void) {
    this->_is_show = false;
}