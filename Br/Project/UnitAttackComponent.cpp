#include "UnitAttackComponent.h"

#include "Helper.h"
#include "Stage.h"
#include "Tile.h"
#include "Unit.h"
#include "Menu.h"
#include "MenuMessenger.h"
#include "UnitCommandMenu.h"
#include "ActorManager.h"
#include "DamageCalculator.h"
#include "UnitCommandMenuMessage.h"
#include "EffectManager.h"
#include "BattleSystem.h"


br::UnitAttackComponent::UnitAttackComponent(Actor* owner, int priority)
    :super(owner, priority),
    _target(nullptr),
    _targets(),
    _select(nullptr),
    _state(nullptr),
    _range_render(nullptr),
    _motion(nullptr),
    _range(),
    _move(nullptr),
    //_is_attack(false),
    _action_count(0),
    _action_count_max(60),
    _prev_position() {
}
br::UnitAttackComponent::~UnitAttackComponent() {
}

void br::UnitAttackComponent::SetTarget(br::Unit* ptr) {
    this->_target = ptr;
}

const std::vector<br::Tile*>& br::UnitAttackComponent::GetRange(void) const {
    return this->_range;
}
/*
bool br::UnitAttackComponent::IsAttack(void) {
    return this->_is_attack;
}
*/

bool br::UnitAttackComponent::Initialize(void) {
    super::Initialize();
    _select = _owner->GetComponent<br::SelectableComponent>();
    _state = _owner->GetComponent<br::UnitStateComponent>();
    _range_render = _owner->GetComponent<br::RangeRenderComponent>();
    _motion = _owner->GetComponent<br::MotionComponent>();
    _move = _owner->GetComponent<br::UnitMoveComponent>();

    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->onCursor.Register("UnderCursorAttack", [&]() {         return this->OnCursor();    });
    return true;
}

bool br::UnitAttackComponent::Update(void) {
    if (!_select->IsUnderCursor() && !_select->IsSelected()) {
        _range.clear();
    } // if
    /*
    if (_is_attack) {
        // 攻撃方向取得
        auto temp = _target->GetPosition() - super::_owner->GetPosition();
        auto dir = Mof::CVector3(temp.x, temp.y, 0.0f);
        dir.Normal(dir);
        float angle = std::atan2(dir.y, dir.x); float degree = MOF_ToDegree(angle);
        auto pos = Mof::CVector2(); float move = 2.0f;
        auto s = (_action_count / 10) % 2 ? -1 : 1;
        // アクション
        if (degree == 0) {
            _motion->SetState("right");
            pos.x += move * s;
        } // if
        else if (degree == 90) {
            _motion->SetState("down");
            pos.y += move * s;
        } // else if
        else if (degree == -90) {
            _motion->SetState("up");
            pos.y -= move * s;
        } // else if
        else if (degree == 180) {
            _motion->SetState("left");
            pos.x -= move * s;
        } // else if

        super::_owner->SetPosition(super::_owner->GetPosition() + pos);

        if (_action_count_max < _action_count++) {
            _action_count = 0;
            auto unit = dynamic_cast<br::Unit*>(super::_owner);
            unit->SetPosition(_prev_position);
            _is_attack = false;
            unit->onEnd();
        } // if
    } // if
    */

    return true;
}

bool br::UnitAttackComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::UnitAttackComponent::OnCursor(void) {
    if (!_state->IsActive()) {
        return false;
    } // if
    if (_select->IsSelected()) {
        return false;
    } // if
    if (_motion->GetState() == "vic") {
        return false;
    } // if

    this->ReConputeRange();
    return true;
}

bool br::UnitAttackComponent::OnEnter(void) {
    _prev_position = super::_owner->GetPosition();
    // 標的は事前に設定する
    // 選択マスのユニットがターゲットにある場合
    if (this->CanAttack(_target)) {
        //_is_attack = true;
        auto battle = dynamic_cast<br::Game*>(super::_owner->GetScene())->GetBattleSystem();
//        auto battle = dynamic_cast<br::Game*>(super::_owner->GetScene())->GetSystem() ->GetBattleSystem();
        battle->Show(dynamic_cast<br::Unit*>(super::_owner), _target);

        //
        //auto unit = dynamic_cast<br::Unit*>(super::_owner);
        //int hit = unit->GetStateComponent()->GetStatus()->GetHit();
        //int avoid = _target->GetStateComponent()->GetStatus()->GetAvoid();
        //
        //// 0から100の範囲で数値を生成しその値が実際の命中よりも低ければ当たる
        //if (ut::GenerateRandom(0, 100) < hit - avoid) {
        //    this->Attack();
        //} // if
        //else {
        //    auto e = super::_owner->GetScene()->GetEffectManager();
        //    e->Start("Resource/sprites/miss_effect/miss_effect.sprite", _target->GetPosition());
        //} // else
        //
        //// 攻撃アクションが終わったらonEndを呼ぶ
        //unit->onEnd();
    } // if
    return false;
}

bool br::UnitAttackComponent::OnCancel(void) {
    //_is_attack = false;

    super::_owner->GetScene()->GetCursor()->SetPosition(super::_owner->GetPosition());
    super::_owner->GetScene()->GetCursor()->ChangeMode(br::Cursor::Mode::Normal, std::vector<Tile*>());

    _range.clear();
    _range_render->SetAttackRange(&_range);

    // メニュー表示
    auto unit = dynamic_cast<br::Unit*>(super::_owner);
    auto e = br::UnitCommandMenuMessage();
    e.target = unit;
    auto m = super::_owner->GetScene()->GetMenu();
    m->Show<br::UnitCommandMenu>(&e);

    //IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    unit->MatchRemoveDelay("Attack");
    unit->MoveRegisterCancel();
    return true;
}
bool br::UnitAttackComponent::OnEnd(void) {
   //_is_attack = false;

    _motion->SetState("wait");
    _state->SetActive(false);
    // 攻撃モード終了
    super::_owner->GetScene()->GetCursor()->ChangeMode(br::Cursor::Mode::Normal, std::vector<Tile*>());

    _range.clear();
    _range_render->SetAttackRange(&_range);

    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->MatchRemoveDelay("Attack");
    return false;
}

void br::UnitAttackComponent::RegisterAttack(void) {
    // 各イベント登録
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->MatchRemove("Move");
    sel->onDecide.Register("AttackEnter", [&]() {
        return this->OnEnter();
    });
    sel->onEnd.Register("AttackEnd", [&]() {
        return this->OnEnd();
    });
    sel->onCancel.Register("AttackCancel", [&]() {
        return this->OnCancel();
    });
}

void br::UnitAttackComponent::AttackRangeClear(void) {
    this->_range.clear();
}

void br::UnitAttackComponent::ToAttackMode(void) {
    //_range.clear();
    _targets.clear();
    auto pos = ut::ToGridPos(super::_owner->GetPosition());
    auto stage = super::_owner->GetScene()->GetStage();

    // 攻撃可能な標的と標的が立っているタイルを設定する
    std::vector<br::Tile*> cursor_range;
    for (auto v : _state->GetAttackRange()) {
        auto tile = stage->GetTile(pos.col + v.x, pos.row + v.y);
        if (auto unit = tile->GetOnUnit(); unit) { // 同チームは攻撃しない
            if (_state->GetTeam() == unit->GetTeam()) {
                continue;
            } // if
            cursor_range.push_back(tile);
            _targets.push_back(unit);
            _range.push_back(tile);
        } // if
    } // for
    _range_render->SetAttackRange(&_range);
    super::_owner->GetScene()->GetCursor()->ChangeMode(br::Cursor::Mode::Limit, std::move(cursor_range));
}

void br::UnitAttackComponent::ReConputeRange(void) {
    // ユニットの攻撃可能な地点を全て取得する
    auto& r = _move->GetRange(); // 移動可能範囲
    // 範囲探索処理の中で移動不可能な地点に隣接している地点を格納
    std::vector<br::RangeDataPointer> work;
    std::copy_if(r.begin(), r.end(),
                 std::back_inserter(work),
                 [](br::RangeDataPointer p) {
        return true;
    });
    _range.clear();

    auto team = dynamic_cast<br::Unit*>(super::_owner)->GetTeam();

    auto stage = super::_owner->GetScene()->GetStage();
    for (auto p : work) {
        //for (auto t : p->_tile->GetAdjacents()) {
        for (auto v : _state->GetAttackRange()) {
            auto pos = p->_tile->GetGridPosition();
            auto t = stage->GetTile(pos.col + v.x, pos.row + v.y);
            if (!t) {
                continue;
            } // if
            if (t->GetOnUnit() && t->GetOnUnit()->GetTeam() == team) { // 味方のいる場所は除く
                continue;
            } // if
            auto it = std::find(_range.begin(), _range.end(), t);
            if (it != _range.end()) {
                continue;
            } // if
            _range.push_back(t);
        } // for
    } // for

    // 攻撃可能範囲の中から移動可能範囲に属する地点を取り除く
    for (auto p : r) {
        auto it = std::find(_range.begin(), _range.end(), p->_tile);
        if (it != _range.end()) {
            _range.erase(it);
        } // if
    } // for
    _range_render->SetAttackRange(&_range);
}

void br::UnitAttackComponent::Start(void) {
    this->ToAttackMode();
    this->RegisterAttack();
}

void br::UnitAttackComponent::Attack(void) {
    br::DamageCalculator c;
    int value = c.Calculation(*dynamic_cast<br::Unit*>(super::_owner), *_target);
    _target->Damege(value);
}

bool br::UnitAttackComponent::CanAttack(br::Unit* target) {
    if (!target) {
        false;
    } // if
    // 選択マスのユニットがターゲットにある場合
    if (std::any_of(_targets.begin(), _targets.end(), [&target](br::Unit* unit) {
        return unit == target;
    })) {
        return true;
    } // if
    return false;
}

br::Component* br::UnitAttackComponent::Clone(void) {
    auto ptr = new br::UnitAttackComponent(nullptr, _priority);
    return ptr;
}