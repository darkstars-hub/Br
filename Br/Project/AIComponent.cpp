#include "AIComponent.h"

#include "Helper.h"
#include "Stage.h"
#include "Tile.h"
#include "Unit.h"
#include "Game.h"
#include "ActorManager.h"
#include "UnitManager.h"
#include "UnitAIManager.h"
#include "AIPatrol.h"
#include "AIAttack.h"


bool br::AIComponent::IsExcute(void) {
    if (_state->GetTeam() != def::kEnemyTeam) {
        return false; // AIが機能するのはエネミーのみ
    } // if
    auto _game = dynamic_cast<br::Game*>(super::_owner->GetScene());
    auto str = _game->GetTurn();
    if (str != def::kEnemyTeam) {
        return false; // 敵のターンでないと考えない
    } // if
    if (!_state->IsActive()) {
        return false; // 行動済みなら処理しない
    } // if
    if (!_input) {
        return false; // 入力フラグが立っていないなら処理しない
    } // if
    return true;
}

br::AIComponent::AIComponent(Actor* owner, int priority) :
    super(owner, priority),
    _input(false),
    _target(nullptr),
    _target_tile(nullptr),
    _state(nullptr),
    _move(nullptr),
    _attack(nullptr),
    _sight(nullptr),
    _path(nullptr),
    _range(nullptr),
    _move_flag(false),
    _attack_flag(false),
    _end_flag(false),
    _state_map(),
    _current_state(nullptr),
    _ai_param() {
}

br::AIComponent::~AIComponent() {
}

void br::AIComponent::Start(void) {
    // このユニットに対してAIが入力中である
    _input = true;

    // ユニットの選択イベント実行
    auto unit = this->GetUnit();
    unit->onSelect();



    // 現在のAIStateの開始（更新）
    _current_state->Start();

    using M = br::UnitAIManager;
    M::GetInstance().PlayerSetTo(_ai_param);
    _current_state->ParamAddTo(_ai_param);

    // 標的の設定
    //_target = _current_state->ConputeTarget();
    _target = _current_state->ConputeTarget(_ai_param);
    //_target = nullptr;
    // 移動先の設定（基本的には標的に近づくような移動をする）
    _target_tile = _current_state->ConputeDestination();

    // 各フラグ初期化
    _move_flag = true;
    _attack_flag = false;
    _end_flag = false;
}

void br::AIComponent::End(void) {
    // もう入力する情報がないことを示す
    this->_end_flag = true;
    this->_input = false;
}

bool br::AIComponent::IsInput(void) const {
    return this->_input;
}

br::Scene* br::AIComponent::GetScene(void) {
    return super::_owner->GetScene();
}

br::Unit* br::AIComponent::GetUnit(void) {
    return dynamic_cast<br::Unit*>(this->_owner);
}

br::Unit* br::AIComponent::GetTargetUnit(void) {
    return this->_target;
}

br::UnitStateComponent* br::AIComponent::GetUnitState(void) {
    return this->_state;
}

br::PathComponent* br::AIComponent::GetPath(void) {
    return this->_path;
}

br::RangeComponent* br::AIComponent::GetRange(void) {
    return this->_range;
}

br::UnitMoveComponent* br::AIComponent::GetMove(void) {
    return this->_move;
}

br::UnitAttackComponent* br::AIComponent::GetAttack(void) {
    return this->_attack;
}

br::UnitSightComponent* br::AIComponent::GetSight(void) {
    return this->_sight;
}

void br::AIComponent::ChangeState(const std::string& name) {
    // 状態遷移
    auto iter = _state_map.find(name);
    if (iter != _state_map.end()) {
        _current_state = iter->second;
    } // if
    else {
        _current_state = nullptr;
    } // else
}

bool br::AIComponent::Initialize(void) {
    // メンバ初期化
    _state = _owner->GetComponent<br::UnitStateComponent>();
    _move = _owner->GetComponent<br::UnitMoveComponent>();
    _attack = _owner->GetComponent<br::UnitAttackComponent>();
    _sight = _owner->GetComponent<br::UnitSightComponent>();
    _path = _owner->GetComponent<br::PathComponent>();
    _range = _owner->GetComponent<br::RangeComponent>();
    _input = (false);

    // 遷移先設定
    _state_map.emplace("Patrol", new br::AIPatrol(this));
    _state_map.emplace("Attack", new br::AIAttack(this));
    //this->ChangeState("Attack");
    this->ChangeState("Patrol");

    //_ai_param.Initialize();
    return true;
}
bool br::AIComponent::Update(void) {
    if (!this->IsExcute()) {
        return false;
    } // if

    // 移動開始
    if (_move_flag) {
        _move_flag = false;
        _move->SetDestination(_target_tile);
        auto unit = this->GetUnit();
        unit->onDecide();
    } // if
    // 目的地に着いたら攻撃するよ
    if (_move->IsArrived()) {
        _attack_flag = true;
    } // if

    // 攻撃する
    if (_attack_flag) {
        auto unit = this->GetUnit();
        unit->AttackStart();
        _attack->SetTarget(_target);
        unit->onDecide();
        _end_flag = true;
    } // if

    // 入力処理終了
    if (_end_flag) {
        this->GetUnit()->onEnd();
        _input = false;
        return true;
    } // if

    // 処理中のユニットにカーソルを合わせる
    if (_target_tile) {
        _owner->GetScene()->GetCursor()->SetPosition(_owner->GetPosition());
    } // if
    return true;
}

bool br::AIComponent::Render(Mof::CVector2 scroll) {
    return false;
}

bool br::AIComponent::Release(void) {
    for (auto& e : _state_map) {
        MOF_SAFE_DELETE(e.second);
    } // for
    return true;
}

br::Component* br::AIComponent::Clone(void) {
    auto ptr = new br::AIComponent(nullptr, _priority);
    return ptr;
}