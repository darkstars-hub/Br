#include "UnitManager.h"
#include "Game.h"

#include "UnitAIManager.h"


br::UnitManager::UnitManager(br::Scene* scene) :
    _scene(scene),
    _game(dynamic_cast<br::Game*>(scene)),
    _units(),
    _reverse_guage(nullptr){
}

br::UnitManager::~UnitManager() {
}
/*
void br::UnitManager::SetReverseGuage(br::ReverseGuage* ptr) {
    this->_reverse_guage = ptr;
}
*/

br::Unit* br::UnitManager::GetUnit(def::Vector2i pos) {
    return this->GetUnit(pos.col, pos.row);
}

br::Unit* br::UnitManager::GetUnit(int col, int row) {
    // 死んでいるものは除く
    for (auto unit : _units) {
        if (unit->GetState() == br::ActorState::Dead) {
            continue;
        } // if
        auto pos = ut::ToGridPos(unit->GetPosition());
        if (pos.col == col && pos.row == row) {
            return unit;
        } // if
    } // for
    return nullptr;
}

bool br::UnitManager::IsPlayerBossDead(void) {
    // プレイヤーの大将を探す
    auto it = std::find_if(_players.begin(),
                           _players.end(),
                           [](br::Unit* unit) {
        return unit->GetUnitType() == br::UnitType::Lord;
    });
    // 死んでいるならをtrue返す
    if ((*it)->GetState() == br::ActorState::Dead) {
        return true;
    } // if
    return false;
}

bool br::UnitManager::IsAllEnemyDead(void) {
    // 全ての敵が死んでいる状態ならtrueを返す
    for (auto e : _enemies) {
        if (e->GetState() != br::ActorState::Dead) {
            return false;
        } // if
    } // for
    return true;
}

void br::UnitManager::AddUnit(br::Unit* unit) {
    _units.push_back(unit);

    // チーム別仕分け
    auto type = unit->GetTeam();
    if (type == def::kPlayerTeam) {
        _players.push_back(unit);
    } // if
    else if (type == def::kEnemyTeam) {
        _enemies.push_back(unit);
    } // if
}

void br::UnitManager::AllPlayerEnd(void) {
    for (auto u : _players) {
        u->SetActive(false);
    } // for
}

std::vector<br::Unit*>& br::UnitManager::GetUnits(void) {
    return this->_units;
}

int br::UnitManager::GetPlayerIndex(br::Unit* unit) {
    int i = 0;
    while (i < _players.size()) {
        if (_players.at(i) == unit) {
            return i;
        } // if
    } // while
    return -1;
}

br::Unit* br::UnitManager::GetUnitAtIndex(size_t index) {
    auto unit = _players.at(index);
    if (unit->GetState() == br::ActorState::Dead) {
        return nullptr;
    } // if
    return unit;
}

size_t br::UnitManager::GetPlayerUnitSize(void) {
    return _players.size();
}

bool br::UnitManager::Input(void) {
    return true;
}

bool br::UnitManager::Initialize(void) {
    br::UnitAIManager::GetInstance().SetUnits(&_players, &_enemies);
    this->_reverse_guage = dynamic_cast<br::Game*>(_scene)->GetReverseGuage();


    for (auto unit : _units) {
        // チーム別仕分け
        auto type = unit->GetTeam();
        if (type == def::kPlayerTeam) {
            auto it = std::find(_players.begin(), _players.end(), unit);
            if (it == _players.end()) {
                _players.push_back(unit);
            } // if
        } // if
        else if (type == def::kEnemyTeam) {
            auto it = std::find(_enemies.begin(), _enemies.end(), unit);
            if (it == _enemies.end()) {
                _enemies.push_back(unit);
            } // if
        } // if
    } // for

    return true;
}

bool br::UnitManager::Update(void) {
    auto turn = _game->GetTurn();
    if (turn == def::kEnemyTeam) {
        br::UnitAIManager::GetInstance().Update();
    } // if
    // 行動可能なユニットが居なくなったらターン変更
    if (std::none_of(_units.begin(), _units.end(), [&turn](br::Unit* unit) {
        return unit->GetTeam() == turn && unit->IsActive() &&
            unit->GetState() != br::ActorState::Dead;
    })) {
        if (turn == def::kEnemyTeam) {
            _game->ChangeTurn(def::kPlayerTeam);
            _reverse_guage->Add(10);
            
            for (auto unit : _enemies) {
                unit->SetActive(true);
            } // for

            // ターン開始でカーソルを味方リーダーに合わせる
            auto cursor = _scene->GetCursor();
            if (auto u = br::UnitAIManager::GetInstance().SearchPlayerBoss(); u) {
                cursor->SetPosition(u->GetPosition());
            } // if
        } // if
        else if (turn == def::kPlayerTeam) {
            _game->ChangeTurn(def::kEnemyTeam);
            for (auto unit : _players) {
                unit->SetActive(true);
            } // for
        } // else if
    } // if

    for (auto actor : _units) {

        actor->Update();
    } // for




    // select
    // 敵は選べない
    auto pos = _scene->GetCursor()->GetPosition();
    auto cursor = _scene->GetCursor();
    int size = def::kChipSize;
    for (auto unit : _units) {
        int x = unit->GetPosition().x;
        int y = unit->GetPosition().y;
        if (cursor->IsEnter() &&
            cursor->CanSelect() &&
            _game->GetTurn() == def::kPlayerTeam &&
            unit->GetTeam() == def::kPlayerTeam &&
            pos.x / size == x / size &&
            pos.y / size == y / size) {
            cursor->SetSelectUnit(unit);
            break;
        } // if
    } // for
    return true;
}

bool br::UnitManager::Render(Mof::CVector2 scroll) {
    for (auto actor : _units) {
        actor->Render(scroll);
    } // for
    return true;
}

bool br::UnitManager::Release(void) {
    _enemies.clear();
    _players.clear();
    for (auto unit : _units) {
        unit->Release();
        MOF_SAFE_DELETE(unit);
    } // for
    _units.clear();
    return true;
}