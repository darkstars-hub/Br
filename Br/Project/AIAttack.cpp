#include "AIAttack.h"

#include "UnitAIManager.h"
#include "UnitStateComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"
#include "UnitSightComponent.h"
#include "PathComponent.h"
#include "RangeComponent.h"
#include "Tile.h"
#include "Stage.h"
#include "Unit.h"
#include "AIParam.h"
#include "DamageCalculator.h"


br::AIAttack::AIAttack(AIComponent* owner) :
    super(owner) {
}

void br::AIAttack::ParamAddTo(AIParam& param) {
    using M = br::UnitAIManager;
    auto players = M::GetInstance().GetPlayers();

    // 視界の中にいるプレイヤーユニット
    std::vector<br::Unit*> work;
    work.reserve(players->size());
    // 視界計算
    super::_owner->GetSight()->ReConputeRange(false);
    auto sight = super::_owner->GetSight()->GetRange();
    for (auto p : *sight) {
        // 視界内のユニットを追加
        if (auto u = p->_tile->GetOnUnit();
            u && u->GetTeam() == def::kPlayerTeam) {
            work.push_back(u);
        } // if
    } // for

    for (auto u : *players) {
        // 死人は狙わない
        if (u->GetState() == br::ActorState::Dead) {
            continue;
        } // if

        int weight = 0;
        // 視野の範囲内で重み加算
        if (std::find(work.begin(), work.end(), u) != work.end()) {
            weight += 10;
        } // if
        br::DamageCalculator cal;
        auto result = cal.CalculationResult(*_owner->GetUnit(), *u);
        // 相性有利で重み加算
        if (result.effective == br::UnitCompatibility::Effective::SuperEffective) {
            weight += 1;
        } // if
        // 弱っているなら重み加算
        if (u->IsPinch()) {
            weight += 2;
        } // if
        // 倒せるなら重み加算
        if (u->GetStateComponent()->GetHp()->GetValue() <= result.value) {
            weight += 3;
        } // if
        param.AddWeight(u, weight);
    } // for
}

br::Unit* br::AIAttack::ConputeTarget(br::AIParam& param) {
    return param.GetTargetUnit();
}

void br::AIAttack::Start(void) {
    auto check = [](br::Tile* t) {
        auto u = t->GetOnUnit();
        return u && u->GetTeam() == def::kPlayerTeam;
    };

    super::_owner->GetSight()->ReConputeRange(false);
    auto sight = super::_owner->GetSight()->GetRange();
    auto it_sight = std::find_if(sight->begin(),
                                 sight->end(),
                                 [&check](br::RangeDataPointer p) {
        auto u = p->_tile->GetOnUnit();
        return u && u->GetTeam() == def::kPlayerTeam;
    });
    if (it_sight == sight->end()) { // プレイヤーが視界にいなければ巡回状態へ
        super::_owner->ChangeState("Patrol");
    } // if
}

void br::AIAttack::DecideTarget(Unit* out) {
    out = this->ConputeTarget();
}

void br::AIAttack::DecideDestination(Tile* out) {
    out = this->ConputeDestination();
}

br::Unit* br::AIAttack::ConputeTarget(void) {
  //  auto ret = br::UnitAIManager::GetInstance().SearchPlayerBoss();
    auto pos = super::_owner->GetUnit()->GetPosition();
    auto ret = br::UnitAIManager::GetInstance().SearchNearestPlayer(pos);
    if (!ret) {
        auto pos = super::_owner->GetUnit()->GetPosition();
        ret = br::UnitAIManager::GetInstance().SearchNearestPlayer(pos);
    } // if
    return ret;
}

br::Tile* br::AIAttack::ConputeDestination(void) {
    // ひたすら追いかけるようにする
    auto scene = super::_owner->GetScene();
    auto unit = super::_owner->GetUnit();
    auto pos = ut::ToGridPos(unit->GetPosition());

    auto range = super::_owner->GetRange();
    auto path = super::_owner->GetPath();
    auto unit_state = super::_owner->GetUnitState();
    // 現在の移動可能範囲計算 MoveComponentで参照するため計算する
    range->ConputeRange(scene->GetStage()->GetTile(pos),
                        unit_state->GetMoveCount());

    auto target = super::_owner->GetTargetUnit();
    if (!target) {
        // 標的がいなければ動かない
        auto  tile = scene->GetStage()->GetTile(pos);
        return tile;
    } // if

    // 移動範囲を度外視した標的への最短経路
    path->Conpute(scene->GetStage()->GetTile(pos),
                  scene->GetStage()->GetTile(target->GetGridPosition()));
    auto& r = range->GetRange(); auto it_begin = r.begin(); auto it_end = r.end();
    auto checkTile = [&it_begin, &it_end](br::Tile* t) {
        auto it = std::find_if(it_begin, it_end, [&t](br::RangeDataPointer p) {
            return p->_tile == t;
        }); // tileが移動可能範囲内にあればtrueを返す
        return it != it_end ? true : false;
    };

    for (auto curr : path->GetPath()) {
        if (!curr->_tile->GetOnUnit() && checkTile(curr->_tile)) {
            return  curr->_tile;
        } // if
        for (auto a : curr->_tile->GetAdjacents()) {
            if (!a) { // ステージの端は隣接する地点が無い
                continue;
            } // if
            if (!a->GetOnUnit() && checkTile(a)) {
                return  a; //誰も乗っていなくて移動可能範囲内にある地点を目標地点とする
            } // if
        } // for
    } // for
    return scene->GetStage()->GetTile(pos);
}

const char* br::AIAttack::GetName() const {
    return "Attack";
}