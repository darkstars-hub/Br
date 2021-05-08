#include "Cursor.h"

#include "Helper.h"
#include "ActorManager.h"
#include "UnitManager.h"
#include "Stage.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "CursorMoveComponent.h"
#include "Unit.h"
#include "Menu.h"
#include "Range.h"
#include "Menu.h"
#include "MenuMessenger.h"
#include "GameMenu.h"
#include "GameMenuMessage.h"


void br::Cursor::WaitCountIncrementGamePad(Mof::LPGamePad pad) {
    if (!pad) {
        return;
    } // if
}

void br::Cursor::WaitCountIncrement(void) {
    // 選択しているユニットが動いているなら操作できない
    if (_select_unit && _select_unit->GetMoveComponent()->IsMove()) {
        return;
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_UP)) {
        _wait.up = _wait.max;
        _wait.hold = _wait.max_hold;
        super::GetComponent<br::CursorMoveComponent>()->SetStop(false);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_DOWN)) {
        _wait.down = _wait.max;
        _wait.hold = _wait.max_hold;
        super::GetComponent<br::CursorMoveComponent>()->SetStop(false);
    } // else if
    if (::g_pInput->IsKeyPush(MOFKEY_LEFT)) {
        _wait.left = _wait.max;
        _wait.hold = _wait.max_hold;
        super::GetComponent<br::CursorMoveComponent>()->SetStop(false);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_RIGHT)) {
        _wait.right = _wait.max;
        _wait.hold = _wait.max_hold;
        super::GetComponent<br::CursorMoveComponent>()->SetStop(false);
    } // else if
    _wait.hold = std::clamp(--_wait.hold, 0, _wait.max_hold);

    if (_wait.hold == 0) {
        if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
            _wait.up++;
        } // if
        else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
            _wait.down++;
        } // else if
        if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
            _wait.left++;
        } // if
        else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
            _wait.right++;
        } // else if
    } // if
}

br::Cursor::Cursor(br::Scene* scene, Mof::CVector2* scroll) :
    super(scene),
    _wait(),
    _is_enter(false),
    _is_back(false),
    _select_unit(nullptr),
    _limit_range(),
    _mode(br::Cursor::Mode::Normal) {

    auto tex = new br::TextureComponent(this, 80);
    tex->SetTexture(_scene->GetResourceManager()->
                    GetTexture("Resource/textures/cursor.png"));
    auto move = new br::CursorMoveComponent(this, 40);
    move->RegisterWait(&_wait);
    move->SetCursor(this);
}

br::Cursor::~Cursor() {
}

br::ActorState br::Cursor::GetState(void) const {
    return super::_base.state;
}

Mof::CVector2 br::Cursor::GetPosition(void) const {
    return super::_base.position;
}

void br::Cursor::SetSelectUnit(br::Actor* unit) {
    if (!unit) {
        this->_select_unit = nullptr;
        return;
    } // if
    if (this->_select_unit != nullptr) {
        return;
    } // if
    auto u = dynamic_cast<br::Unit*>(unit);
    if (!u->IsActive()) {
        return;
    } // if

    //ユニットの選択用関数実行
    this->_select_unit = u;
    this->_select_unit->onSelect();

    this->_select_unit->onEnd.Register("CursorCancel", [&]() {
        this->_select_unit = nullptr;
        return false;
    });
}

bool br::Cursor::IsEnter(void) const {
    return this->_is_enter;
}

bool br::Cursor::IsBack(void) const {
    return this->_is_back;
}

bool br::Cursor::CanSelect(void) const {
    if (!_select_unit) {
        return true;
    } // if
    // 選択しているユニットが動いているならfalseを返す
    return !_select_unit->GetMoveComponent()->IsMove();
}

bool br::Cursor::InMovableRange(br::Tile* tile) const {
    // 受け取った位置にあるタイルが
    if (_select_unit == nullptr) {
        return true;
    } // if
    if (tile == nullptr) {
        return false;
    } // if

    // 選択しているユニットの移動可能範囲内にあればtrueを返す
    auto& r = _select_unit->GetMoveComponent()->GetRange();
    for (auto t : r) {
        if (t->_tile->Equal(tile)) {
            return true;
        } // if
    } // for
    return false;
}

bool br::Cursor::InAttackRange(br::Tile* tile) const {
        // 受け取った位置にあるタイルが
    if (_select_unit == nullptr) {
        return false;
    } // if
    if (tile == nullptr) {
        return false;
    } // if

    // 選択しているユニットの移動可能範囲内にあればtrueを返す
    auto& r = _select_unit->GetAttackComponent()->GetRange();
    for (auto t : r) {
        if (t->Equal(tile)) {
            return true;
        } // if
    } // for
    return false;
}

br::Unit* br::Cursor::GetSelectUnit(void) {
    return this->_select_unit;
}

br::Unit* br::Cursor::GetUnderUnit(void) {
    auto tp = ut::ToGridPos(this->GetPosition());
    auto tu = super::GetScene()->GetActorManager()->GetUnitManager()->GetUnit(tp.col, tp.row);
    if (tu) {
        return tu;
    } // if
    return nullptr;
}

br::Cursor::Mode br::Cursor::GetMode(void) {
    return this->_mode;
}

std::vector<br::Tile*>& br::Cursor::GetLimitRange(void) {
    return this->_limit_range;
}

void br::Cursor::ChangeMode(br::Cursor::Mode mode, std::vector<br::Tile*>& range) {
    this->_mode = mode;
    this->_limit_range = range;
    if (!range.empty() && mode == br::Cursor::Mode::Limit) {
        super::SetPosition((*range.begin())->GetPosition());
    } // if
}

bool br::Cursor::Input(void) {
    _is_enter = false;
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        _is_enter = true;
        // 選択ユニットの確定イベント実施
        if (_select_unit) {
            auto stage = super::GetScene()->GetStage();
            auto t = stage->GetTile(ut::ToGridPos(this->GetPosition()));
            _select_unit->SetMoveDestination(t);
            if (t->GetOnUnit()) {
                _select_unit->SetAttackTarget(t->GetOnUnit());
            } // if
            _select_unit->onDecide();

            // 戦闘結果予想はもう不要なので非表示に
            if (dynamic_cast<br::Game*>(_scene)->GetBattleSystemForeCast()->IsShow()) {
                dynamic_cast<br::Game*>(_scene)->GetBattleSystemForeCast()->Hide();
            } // if
        } // if
    } // if
    _is_back = false;
    if (::g_pInput->IsKeyPush(MOFKEY_BACK)) {
        _is_back = true;
        // 選択ユニットのキャンセルイベント実施
        if (_select_unit) {
            _select_unit->onCancel();
        } // if

        // 戦闘結果予想はもう不要なので非表示に
        if (dynamic_cast<br::Game*>(_scene)->GetBattleSystemForeCast()->IsShow()) {
            dynamic_cast<br::Game*>(_scene)->GetBattleSystemForeCast()->Hide();
        } // if
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_M) || ::g_pInput->IsKeyPush(MOFKEY_Z)) {
        auto m = super::GetScene()->GetMenu();
        auto mm = br::GameMenuMessage();
        mm.game = dynamic_cast<br::Game*>(super::_scene);
        mm.actor_manager = super::_scene->GetActorManager();
        mm.stage = super::_scene->GetStage();
        mm.cursor = this;
        m->Show<br::GameMenu>(&mm);
    } // if
    

    this->WaitCountIncrement();
    auto pad = ::g_pInput->GetGamePad(0);
    this->WaitCountIncrementGamePad(pad);
    return true;
}

bool br::Cursor::Update(void) {
    super::Update();
    if (!_select_unit) {
        auto pos = ut::ToGridPos(this->GetPosition());
        auto um = super::GetScene()->GetActorManager()->GetUnitManager();
        if (auto unit = um->GetUnit(pos); unit) {
            unit->onCursor();
            if (unit->GetTeam() == def::kPlayerTeam) {
            } // if
        } // if
    } // if
    return true;
}

bool br::Cursor::Render(Mof::CVector2 scroll) {
    super::Render(scroll);
//
//auto pos = super::_base.position;
//::CGraphicsUtilities::RenderString(
//    0.0f, 100.0f,
//    "cursor x = %f : cursor y = %f", pos.x, pos.y);
    return true;
}