#include "AIPatrol.h"

#include "Unit.h"
#include "Tile.h"
#include "UnitAIManager.h"
#include "UnitStateComponent.h"
#include "UnitMoveComponent.h"
#include "UnitAttackComponent.h"
#include "UnitSightComponent.h"
#include "PathComponent.h"
#include "RangeComponent.h"
#include "Stage.h"


br::Tile* br::AIPatrol::Analyze(br::Tile& origin, br::Direction* front) {
    using D = br::Direction;
    int analysis[(int)D::CountMax]; // 各移動方向の評価値
    const auto& a = origin.GetAdjacents();

    // 「道」であれば隣接するタイルであれば評価値を加算
    for (int i = 0; i < (int)D::CountMax; i++) {
        if (!a.at(i)) {
            continue;
        } // if
        if (a.at(i)->GetName() == "road") {
            analysis[i] = 10;
        } // if
        else {
            analysis[i] = 0;
        } // else
    } // for

    int up = static_cast<int>(D::Up);      int down = static_cast<int>(D::Down);
    int left = static_cast<int>(D::Left);  int right = static_cast<int>(D::Right);

    // 方向別に評価値を加算 // 反時計回り
    auto direction = *front;
    if (direction == D::Up) {
        analysis[up] = analysis[up] + 2;
        analysis[down]--;
        analysis[left]++;
        //analysis[right]++;
    } // if
    if (direction == D::Down) {
        analysis[down] = analysis[down] + 2;
        analysis[up]--;
        //analysis[left]++;
        analysis[right]++;
    } // if
    if (direction == D::Left) {
        analysis[left] = analysis[left] + 2;
        analysis[right]--;
        analysis[up]++;
        //analysis[down]++;
    } // if
    if (direction == D::Right) {
        analysis[right] = analysis[right] + 2;
        analysis[left]--;
        //analysis[up]++; 
        analysis[down]++;
    } // if

    // 移動する方向を設定
    int max = 0; int max_index = -1;
    for (int i = 0; i < (int)D::CountMax; i++) {
        if (analysis[i] > max) {
            max = analysis[i];
            max_index = i;
        } // if
    } // for
    *front = (D)max_index;
    return a.at(max_index);
}

br::AIPatrol::AIPatrol(AIComponent* owner) :
    super(owner) {
}

void br::AIPatrol::ParamAddTo(AIParam& param) {
//    param.AddWeight();
}

void br::AIPatrol::Start(void) {
    auto check = [](br::Tile* t) {
        auto u = t->GetOnUnit();
        return u && u->GetTeam() == def::kPlayerTeam;
    };

    super::_owner->GetSight()->ReConputeRange(false);
    auto s = super::_owner->GetSight()->GetRange();
    auto it_s = std::find_if(s->begin(), s->end(), [&check](br::RangeDataPointer p) {
        return check(p->_tile);
    });
    // プレイヤーが視界に入ったら攻撃状態へ
    if (it_s != s->end()) {
        super::_owner->ChangeState("Attack");
    } // if
}

void br::AIPatrol::DecideTarget(br::Unit* out) {
    out = nullptr;
}

void br::AIPatrol::DecideDestination(br::Tile* out) {
    out = this->ConputeDestination();
}

br::Unit* br::AIPatrol::ConputeTarget(void) {
    return nullptr;
}

br::Tile* br::AIPatrol::ConputeDestination(void) {
    auto scene = super::_owner->GetScene();
    auto unit = super::_owner->GetUnit();
    auto pos = ut::ToGridPos(unit->GetPosition());
    br::Direction dir = super::_owner->GetMove()->GetDirection();
    br::Tile* ret = scene->GetStage()->GetTile(pos);

    if (scene->GetStage()->GetTile(pos)->GetName() == "road") {
        for (int i = 0; i < super::_owner->GetUnitState()->GetMoveCount(); i++) {
            ret = this->Analyze(*ret, &dir);
        } // for
    } // if
    else {
        //std::exit(0);
    } // else

    return ret;

 // auto scene = super::_owner->GetScene();
 // auto unit = super::_owner->GetUnit();
 // auto pos = ut::ToGridPos(unit->GetPosition());
 //
 // auto range = super::_owner->GetRange();
 // auto unit_state = super::_owner->GetUnitState();
 // // 現在の移動可能範囲計算 MoveComponentで参照するため計算する
 // range->ConputeRange(scene->GetStage()->GetTile(pos),
 //                     unit_state->GetMoveCount());
 // auto target = super::_owner->GetTargetUnit();
 //
 // return scene->GetStage()->GetTile(pos);
}

const char* br::AIPatrol::GetName() const {
    return "Patrol";
}