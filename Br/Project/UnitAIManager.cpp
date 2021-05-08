#include "UnitAIManager.h"

#include <algorithm>


br::UnitAIManager::UnitAIManager() :
    _players(nullptr),
    _enemies(nullptr) {
}

br::UnitAIManager::~UnitAIManager() {
}

br::UnitAIManager& br::UnitAIManager::GetInstance() {
    static br::UnitAIManager obj;
    return obj;
}

void br::UnitAIManager::SetUnits(std::vector<br::Unit*>* players,
                                 std::vector<br::Unit*>* enemies) {
    this->_players = players;
    this->_enemies = enemies;
}

const std::vector<br::Unit*>* br::UnitAIManager::GetPlayers(void) {
    return this->_players;
}

br::Unit* br::UnitAIManager::SearchPlayerBoss(void) {
    // プレイヤーの大将を探す
    auto it = std::find_if(_players->begin(),
                           _players->end(),
                           [](br::Unit* unit) {
        return
            unit->GetState() == br::ActorState::Active &&
            unit->GetUnitType() == br::UnitType::Lord;
    });
    if (it != _players->end()) {
        return *it;
    } // if
    return nullptr;
}

br::Unit* br::UnitAIManager::SearchNearestPlayer(Mof::CVector2 position) {
    // 生きてるユニット抽出
    std::vector<br::Unit*> work;
    std::copy_if(_players->begin(),
                 _players->end(),
                 std::back_inserter(work),
                 [](br::Unit* u) {
        return
            u->GetTeam() == def::kPlayerTeam &&
            u->GetState() == br::ActorState::Active;
    });
    auto squared = [](Mof::CVector2 a, Mof::CVector2 b) {
        return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    };
    // positionに近い位置にいる生きてるプレイヤーユニットを探す
    auto it = std::min_element(work.begin(), work.end(),
                               [squared, position](br::Unit* a, br::Unit* b) {
        return squared(position, a->GetPosition()) < squared(position, b->GetPosition());
    });

    if (it != work.end()) {
        return *it;
    } // if
    return nullptr;
}

br::Unit* br::UnitAIManager::SearchTargetUnit(br::AIParam& param) {
    br::Unit* ptr;
   
    return ptr;
}

bool br::UnitAIManager::Update(void) {
    _ASSERT_EXPR(_enemies, "エネミーがnullptrです");
    // 整列　
    auto it = std::find_if(_enemies->begin(), _enemies->end(), [](br::Unit* p) {
        return p->IsActive() && p->GetState() != br::ActorState::Dead;
    });
    //std::random_device seed_gen;
    //std::mt19937 engine(seed_gen());
    //std::shuffle(_enemies->begin(), _enemies->end(), engine);
    if (it != _enemies->end()) {
        (*it)->AIStart();
    } // if
    return true;
}

void br::UnitAIManager::PlayerSetTo(br::AIParam& param) {
    // 生きてるユニット抽出
    std::vector<br::Unit*> work;
    std::copy_if(_players->begin(),
                 _players->end(),
                 std::back_inserter(work),
                 [](br::Unit* u) {
        return
            u->GetTeam() == def::kPlayerTeam &&
            u->GetState() == br::ActorState::Active;
    });
    
    for (auto u : work) {
        param.AddUnit(u);
    } // for
}