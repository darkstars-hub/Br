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

    // ���E�̒��ɂ���v���C���[���j�b�g
    std::vector<br::Unit*> work;
    work.reserve(players->size());
    // ���E�v�Z
    super::_owner->GetSight()->ReConputeRange(false);
    auto sight = super::_owner->GetSight()->GetRange();
    for (auto p : *sight) {
        // ���E���̃��j�b�g��ǉ�
        if (auto u = p->_tile->GetOnUnit();
            u && u->GetTeam() == def::kPlayerTeam) {
            work.push_back(u);
        } // if
    } // for

    for (auto u : *players) {
        // ���l�͑_��Ȃ�
        if (u->GetState() == br::ActorState::Dead) {
            continue;
        } // if

        int weight = 0;
        // ����͈͓̔��ŏd�݉��Z
        if (std::find(work.begin(), work.end(), u) != work.end()) {
            weight += 10;
        } // if
        br::DamageCalculator cal;
        auto result = cal.CalculationResult(*_owner->GetUnit(), *u);
        // �����L���ŏd�݉��Z
        if (result.effective == br::UnitCompatibility::Effective::SuperEffective) {
            weight += 1;
        } // if
        // ����Ă���Ȃ�d�݉��Z
        if (u->IsPinch()) {
            weight += 2;
        } // if
        // �|����Ȃ�d�݉��Z
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
    if (it_sight == sight->end()) { // �v���C���[�����E�ɂ��Ȃ���Ώ����Ԃ�
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
    // �Ђ�����ǂ�������悤�ɂ���
    auto scene = super::_owner->GetScene();
    auto unit = super::_owner->GetUnit();
    auto pos = ut::ToGridPos(unit->GetPosition());

    auto range = super::_owner->GetRange();
    auto path = super::_owner->GetPath();
    auto unit_state = super::_owner->GetUnitState();
    // ���݂̈ړ��\�͈͌v�Z MoveComponent�ŎQ�Ƃ��邽�ߌv�Z����
    range->ConputeRange(scene->GetStage()->GetTile(pos),
                        unit_state->GetMoveCount());

    auto target = super::_owner->GetTargetUnit();
    if (!target) {
        // �W�I�����Ȃ���Γ����Ȃ�
        auto  tile = scene->GetStage()->GetTile(pos);
        return tile;
    } // if

    // �ړ��͈͂�x�O�������W�I�ւ̍ŒZ�o�H
    path->Conpute(scene->GetStage()->GetTile(pos),
                  scene->GetStage()->GetTile(target->GetGridPosition()));
    auto& r = range->GetRange(); auto it_begin = r.begin(); auto it_end = r.end();
    auto checkTile = [&it_begin, &it_end](br::Tile* t) {
        auto it = std::find_if(it_begin, it_end, [&t](br::RangeDataPointer p) {
            return p->_tile == t;
        }); // tile���ړ��\�͈͓��ɂ����true��Ԃ�
        return it != it_end ? true : false;
    };

    for (auto curr : path->GetPath()) {
        if (!curr->_tile->GetOnUnit() && checkTile(curr->_tile)) {
            return  curr->_tile;
        } // if
        for (auto a : curr->_tile->GetAdjacents()) {
            if (!a) { // �X�e�[�W�̒[�͗אڂ���n�_������
                continue;
            } // if
            if (!a->GetOnUnit() && checkTile(a)) {
                return  a; //�N������Ă��Ȃ��Ĉړ��\�͈͓��ɂ���n�_��ڕW�n�_�Ƃ���
            } // if
        } // for
    } // for
    return scene->GetStage()->GetTile(pos);
}

const char* br::AIAttack::GetName() const {
    return "Attack";
}