#include "UnitMoveComponent.h"

#include "Helper.h"
#include "Stage.h"
#include "Unit.h"
#include "Menu.h"
#include "MenuMessenger.h"
#include "UnitCommandMenu.h"
#include "UnitAttackComponent.h"
#include "UnitSightComponent.h"
#include "UnitCommandMenuMessage.h"


void br::UnitMoveComponent::ReConputeRange(void) {
    // 移動可能範囲取得 
    // 移動可能数
    int move = _state->GetMoveCount();
    auto tile = _state->GetCurrentTile();
    _range->ConputeRange(tile, move);
}

void br::UnitMoveComponent::Move(br::Direction d) {
    switch (static_cast<br::Direction>(d)) {
        case br::Direction::Up:
            _motion->SetState("up");
            _move += def::Vector2i::MofVec2(def::VUp);
            _front_direction = br::Direction::Up;
            break;
        case br::Direction::Down:
            _motion->SetState("down");
            _move += def::Vector2i::MofVec2(def::VDown);
            _front_direction = br::Direction::Down;
            break;
        case br::Direction::Left:
            _motion->SetState("left");
            _move += def::Vector2i::MofVec2(def::VLeft);
            _front_direction = br::Direction::Left;
            break;
        case br::Direction::Right:
            _motion->SetState("right");
            _move += def::Vector2i::MofVec2(def::VRight);
            _front_direction = br::Direction::Right;
            break;
        default:
            break;
    } // switch
}

br::UnitMoveComponent::UnitMoveComponent(Actor* owner, int priority) :
    super(owner, priority),
    _is_move(false),
    _move(),
    _move_no(0),
    _speed(def::kChipSize * 0.25f / 2,
           def::kChipSize * 0.25f / 2),
    _select(nullptr),
    _state(nullptr),
    _motion(nullptr),
    _path(nullptr),
    _range(nullptr),
    _attack(nullptr),
    _sight(nullptr),
    _prev_position(),
    _destination(nullptr),
    _front_direction(br::Direction::Down) {
    super::_type = ComponentType::UnitMoveComponent;
}

br::UnitMoveComponent::~UnitMoveComponent() {
}

void br::UnitMoveComponent::SetDestination(br::Tile* ptr) {
    this->_destination = ptr;
}

const std::vector<br::RangeDataPointer>& br::UnitMoveComponent::GetRange(void) const {
    return _range->GetRange();
}

br::Direction br::UnitMoveComponent::GetDirection(void) const {
    return this->_front_direction;
}

bool br::UnitMoveComponent::IsMove(void) const {
    return this->_is_move;
}

bool br::UnitMoveComponent::IsArrived(void) const {
    return _path->IsArrived(_move_no);
}

void br::UnitMoveComponent::MoveStart(void) {
    auto mp = ut::ToGridPos(super::_owner->GetPosition());
    auto start = super::_owner->GetScene()->GetStage()->GetTile(mp.col, mp.row);
    auto tp = ut::ToGridPos(_destination->GetPosition());
    auto goal = super::_owner->GetScene()->GetStage()->GetTile(tp.col, tp.row);

    // 移動先が移動可能なタイル
    if (_path->CheckTargetTile(_range->GetRange(), goal)) {
        // 移動パス計算
        _is_move = true;
        _move_no = 0;
        _path->Conpute(goal, start);

        //もう決定先を変えれないようにするため移動先の決定関数を削除
        IDecide* sel = dynamic_cast<br::IDecide*>(super::_owner);
        sel->onDecide -= "MoveEnter";
    } // if
}

bool br::UnitMoveComponent::Initialize(void) {
    super::Initialize();
    _select = _owner->GetComponent<br::SelectableComponent>();
    _state = _owner->GetComponent<br::UnitStateComponent>();
    _path = _owner->GetComponent<br::PathComponent>();
    _range = _owner->GetComponent<br::RangeComponent>();
    _motion = _owner->GetComponent<br::MotionComponent>();
    _attack = _owner->GetComponent<br::UnitAttackComponent>();
    _sight = _owner->GetComponent<br::UnitSightComponent>();

    // 各イベント登録
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->onCursor.Register("UnderCursor", [&]() {         return this->OnCursor();    });
    sel->onSelect.Register("UnitSelect", [&]() {        return this->OnSelect();    });
    return true;
}

bool br::UnitMoveComponent::OnCursor(void) {
    if (!_state->IsActive()) {
        return false;
    } // if
    if (_select->IsSelected()) {
        return false;
    } // if
    if (_motion->GetState() == "vic") {
        return false;
    } // if
    // 移動可能数
    auto unit = dynamic_cast<br::Unit*>(super::_owner);
    // 敵であってもカーソルを合わせるとアピールしてくれる
    _motion->SetState("vic");
    this->ReConputeRange();
    _attack->ReConputeRange();
    _sight->ReConputeRange();
    return true;
}

bool br::UnitMoveComponent::OnSelect(void) {
    if (!_state->IsActive()) {
        return false;
    } // if
    _prev_position = super::_owner->GetPosition();
    _motion->SetState("down");
    this->ReConputeRange();

    // 移動先の決定やキャンセルの関数を登録
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->onDecide.Register("MoveEnter", [&]() {        return this->OnEnter();    });
    sel->onEnd.Register("MoveEnd", [&]() {        return this->OnEnd();    });
    sel->onCancel.Register("MoveCancel", [&]() {        return this->OnCancel();    });
    return true;
}

bool br::UnitMoveComponent::OnEnter(void) {
    this->MoveStart();
    return true;
}

bool br::UnitMoveComponent::OnCancel(void) {
    super::_owner->SetPosition(_prev_position);
    super::_owner->GetScene()->GetCursor()->SetPosition(_prev_position);
    _motion->SetState("wait");

    this->ReConputeRange();
    _path->Clear();
    _move_no = 0;
    _is_move = false;

    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->MatchRemoveDelay("Move");
    return true;
}

bool br::UnitMoveComponent::OnEnd(void) {
    super::_owner->GetScene()->GetCursor()->ChangeMode(br::Cursor::Mode::Normal, std::vector<Tile*>());
    _motion->SetState("wait");
    _range->Clear();
    _path->Clear();
    _attack->AttackRangeClear();
    _state->SetActive(false);
    _is_move = false;
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->MatchRemoveDelay("Move");
    return false;
}

void br::UnitMoveComponent::RegisterCancel(void) {
    // キャンセルの関数を登録
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->onEnd.Register("MoveEnd", [&]() {        return this->OnEnd();    });
    sel->onCancel.Register("MoveCancel", [&]() {        return this->OnCancel();    });
}

bool br::UnitMoveComponent::Update(void) {
    auto pos = super::_owner->GetPosition();
    ut::Zero(_move);

    if (!_select->IsUnderCursor() && !_select->IsSelected()) {
        if (!_is_move) {
            _range->Clear();
            _path->Clear();
            _motion->SetState("wait");
        } // if
    } // if

    if (_is_move) { // 今いる地点の次の地点へ
        if (auto next = _path->GetElement(_move_no)->parent.lock()) {
            auto target = next->_tile->GetPosition();
            if ((int)pos.x == (int)target.x && (int)pos.y == (int)target.y) {
                _move_no++;
            } // if

            int i = 0; // 移動方向取得
            for (auto adjacent : _path->GetElement(_move_no)->_tile->GetAdjacents()) {
                if (adjacent && adjacent->Equal(next->_tile)) {
                    break;
                } // if
                i++;
            } // for
            // 移動
            this->Move(static_cast<br::Direction>(i));
        } // if
        if (this->IsArrived()) {
            _is_move = false;
            // メニューを表示
            // メニューが消えたらendEvent
            auto unit = dynamic_cast<br::Unit*>(super::_owner);
            if (unit->GetTeam() == def::kPlayerTeam) {
                auto e = br::UnitCommandMenuMessage();
                e.target = unit;
                auto m = super::_owner->GetScene()->GetMenu();
                m->Show<br::UnitCommandMenu>(&e);
            } // if
        } // if
    }

    _move *= _speed;
    pos += _move;
    super::_owner->SetPosition(pos);
    return true;
}

bool br::UnitMoveComponent::Render(Mof::CVector2 scroll) {
    return true;
}

br::Component* br::UnitMoveComponent::Clone(void) {
    auto ptr = new br::UnitMoveComponent(nullptr, _priority);
    return ptr;
}