#include "CursorMoveComponent.h"

#include "Helper.h"
#include "AudioSystem.h"
#include "Stage.h"
#include "Unit.h"
#include "Game.h"
#include "BattleSystemForecast.h"


void br::CursorMoveComponent::Move(const def::Vector2i m, Mof::CVector2& pos) {
    auto scene = super::_owner->GetScene();
    pos.x += def::kChipSize * m.x;
    pos.y += def::kChipSize * m.y;
    scene->GetAudioSystem()->Play("Resource/sound/se_maoudamashii_system27.mp3");
    // クリッピング
    auto x = scene->GetStage()->GetTileCount().x;
    auto y = scene->GetStage()->GetTileCount().y;
    pos.x = std::clamp((int)pos.x,
                       0 + def::kPadding,
                       (int)x * def::kChipSize - def::kChipSize - def::kPadding);
    pos.y = std::clamp((int)pos.y,
                       0 + def::kPadding,
                       (int)y * def::kChipSize - def::kChipSize - def::kPadding);
}

void br::CursorMoveComponent::Move(br::Direction dir, Mof::CVector2& pos) {
    auto tile = this->GetSelectedTile(super::_owner, super::_owner->GetScene());
    auto next = tile->GetAdjacents().at((size_t)dir);
    if (!_stop) {
        this->Move(def::VDirection[(size_t)dir], pos);
    } // if
    // ユニット選択時は移動先が攻撃可能地点、敵がいる地点であれば引っかかる
    if (_cursor->GetSelectUnit() &&
        (_cursor->InAttackRange(next) ||
        (next && next->GetOnUnit() && next->GetOnUnit()->GetTeam() != def::kPlayerTeam))) {
        _stop = true;
    } // if
}

void br::CursorMoveComponent::MoveOnAttackMode(Mof::CVector2& pos) {
    auto& range = _cursor->GetLimitRange();
    br::Tile* current; auto p = ut::ToGridPos(pos);
    for (auto t : range) {
        if (t == super::_owner->GetScene()->GetStage()->GetTile(p.col, p.row)) {
            current = t;
            break;
        } // if
    } // for

    std::vector<br::Tile*> work;
    auto it = work.end();
    if (_wait->up >= _wait->max) { // 今より上側にあるものだけ集める
        std::copy_if(range.begin(), range.end(), std::back_inserter(work), [&current](br::Tile* tile) {
            return current->GetGridPosition().row > tile->GetGridPosition().row;
        }); // 動いたときの移動量が最小のものを選ぶ
        it = std::min_element(work.begin(), work.end(), [](br::Tile* a, br::Tile* b) {
            return a->GetGridPosition().row < b->GetGridPosition().row;
        });
        if (it != work.end()) { // 位置をそこにする
            pos = (*it)->GetPosition();
        } // if

        _wait->up = 0;
    } // if
    else if (_wait->down >= _wait->max) { // 今より下側にあるものだけ集める
        std::copy_if(range.begin(), range.end(), std::back_inserter(work), [&current](br::Tile* tile) {
            return current->GetGridPosition().row < tile->GetGridPosition().row;
        }); // 動いたときの移動量が最小のものを選ぶ
        auto it = std::min_element(work.begin(), work.end(), [](br::Tile* a, br::Tile* b) {
            return a->GetGridPosition().row < b->GetGridPosition().row;
        });
        if (it != work.end()) { // 位置をそこにする
            pos = (*it)->GetPosition();
        } // if

        _wait->down = 0;
    } // else if
    if (_wait->left >= _wait->max) { // 今より左側にあるものだけ集める
        std::copy_if(range.begin(), range.end(), std::back_inserter(work), [&current](br::Tile* tile) {
            return current->GetGridPosition().col > tile->GetGridPosition().col;
        }); // 動いたときの移動量が最小のものを選ぶ
        auto it = std::min_element(work.begin(), work.end(), [](br::Tile* a, br::Tile* b) {
            return a->GetGridPosition().col < b->GetGridPosition().col;
        });
        if (it != work.end()) { // 位置をそこにする
            pos = (*it)->GetPosition();
        } // if

        _wait->left = 0;
    } // if
    else if (_wait->right >= _wait->max) { // 今より右側にあるものだけ集める
        std::copy_if(range.begin(), range.end(), std::back_inserter(work), [&current](br::Tile* tile) {
            return current->GetGridPosition().col < tile->GetGridPosition().col;
        }); // 動いたときの移動量が最小のものを選ぶ
        auto it = std::min_element(work.begin(), work.end(), [](br::Tile* a, br::Tile* b) {
            return a->GetGridPosition().col < b->GetGridPosition().col;
        });
        if (it != work.end()) { // 位置をそこにする
            pos = (*it)->GetPosition();
        } // if

        _wait->right = 0;
    } // else if

    auto battle_forecast = dynamic_cast<br::Game*>(super::_owner->GetScene())->
        GetBattleSystemForeCast();
    // 戦闘予想が表示中であれば必要な情報を入れてやる
    if (battle_forecast->IsShow()) {
        auto pos = super::_owner->GetPosition();
        auto stage = super::_owner->GetScene()->GetStage();
        auto tile = stage->GetTile(pos.x / def::kChipSize,
                                   pos.y / def::kChipSize);
        // ちょっとずらす
        pos += Mof::CVector2(def::kChipSize*2, def::kChipSize * 2);
        battle_forecast->SetTarget(tile->GetOnUnit());
        battle_forecast->SetPosition(pos);
    } // if
}

br::Tile* br::CursorMoveComponent::GetSelectedTile(br::Actor* actor, br::Scene* scene) {
    auto pos = super::_owner->GetPosition();
    auto stage = super::_owner->GetScene()->GetStage();
    auto tile = stage->GetTile(pos.x / def::kChipSize,
                               pos.y / def::kChipSize);
    return tile;
}

br::CursorMoveComponent::CursorMoveComponent(Actor* owner, int priority) :
    super(owner, priority),
    _cursor(nullptr),
    _wait(),
    _stop(false) {
    super::_type = ComponentType::CursorMoveComponent;
}

br::CursorMoveComponent::~CursorMoveComponent() {
}

void br::CursorMoveComponent::SetCursor(br::Cursor* ptr) {
    this->_cursor = ptr;
}

void br::CursorMoveComponent::SetStop(bool b) {
    this->_stop = b;
}

void br::CursorMoveComponent::RegisterWait(DirectionWait* wait) {
    this->_wait = wait;
}

bool br::CursorMoveComponent::Update(void) {
    auto pos = super::_owner->GetPosition();
    auto size = def::kChipSize;

    // 移動可能範囲を制限しているとき
    if (_cursor->GetMode() == br::Cursor::Mode::Limit) {
        this->MoveOnAttackMode(pos);
    } // if

    // 方向別移動処理（通常）
    if (_cursor->GetMode() == br::Cursor::Mode::Normal) {

        if (_wait->up >= _wait->max) {
            _wait->up = 0;
            Move(Direction::Up, pos);
        } // if
        else if (_wait->down >= _wait->max) {
            _wait->down = 0;
            Move(Direction::Down, pos);
        } // else if
        if (_wait->left >= _wait->max) {
            _wait->left = 0;
            Move(Direction::Left, pos);
        } // if
        else if (_wait->right >= _wait->max) {
            _wait->right = 0;
            Move(Direction::Right, pos);
        } // else if
    } // if

    super::_owner->SetPosition(pos);
    return true;
}

bool br::CursorMoveComponent::Render(Mof::CVector2 scroll) {
    return true;
}

br::Component* br::CursorMoveComponent::Clone(void) {
    return nullptr;
}