#include "UnitHealComponent.h"

#include "Unit.h"
#include "Stage.h"
#include "Tile.h"
#include "Menu.h"
#include "ActorManager.h"
#include "UnitManager.h"
#include "LightCavalryComponent.h"
#include "MenuMessenger.h"
#include "UnitCommandMenu.h"
#include "UnitCommandMenuMessage.h"


br::UnitHealComponent::UnitHealComponent(Actor* owner, int priority) :
    super(owner, priority),
    _select(nullptr),
    _state(nullptr),
    _range_render(nullptr),
    _motion(nullptr),
    _range() {
}

br::UnitHealComponent::~UnitHealComponent() {
}

bool br::UnitHealComponent::Initialize(void) {
    super::Initialize();
    _select = _owner->GetComponent<br::SelectableComponent>();
    _state = _owner->GetComponent<br::UnitStateComponent>();
    _range_render = _owner->GetComponent<br::RangeRenderComponent>();
    _motion = _owner->GetComponent<br::MotionComponent>();
    return true;
}

bool br::UnitHealComponent::Update(void) {
    return true;
}
bool br::UnitHealComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::UnitHealComponent::OnEnter(void) {
    // 選択マスのユニット取得
    auto tp = ut::ToGridPos(_select->GetCursorPosition());
    auto tu = super::_owner->GetScene()->GetActorManager()->GetUnitManager()->GetUnit(tp.col, tp.row);

    // 選択マスのユニットがターゲットにある場合
    if (this->CanHeal(tu)) {
//        auto fusion = dynamic_cast<br::Game*>(super::_owner->GetScene())->GetFusionSystem();
  //      fusion->Show(dynamic_cast<br::Unit*>(super::_owner), tu);

        //this->Fusion(*tu);
        //
        auto unit = dynamic_cast<br::Unit*>(super::_owner);
    
        this->Heal(*tu);

        unit->onEnd();
    } // if
    return true;
}

bool br::UnitHealComponent::OnCancel(void) {
    super::_owner->GetScene()->GetCursor()->SetPosition(super::_owner->GetPosition());
    super::_owner->GetScene()->GetCursor()->ChangeMode(br::Cursor::Mode::Normal, std::vector<Tile*>());

    _range.clear();
    _range_render->SetFusionRange(&_range);
    auto unit = dynamic_cast<br::Unit*>(super::_owner);
    unit->MoveRegisterCancel();
//    super::_owner->GetScene()->GetMenu()->Show(unit);
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->MatchRemoveDelay("Heal");

    auto e = br::UnitCommandMenuMessage();
    e.target = unit;
    auto m = super::_owner->GetScene()->GetMenu();
    m->Show<br::UnitCommandMenu>(&e);
    return true;
}

bool br::UnitHealComponent::OnEnd(void) {
    super::_owner->GetScene()->GetCursor()->ChangeMode(br::Cursor::Mode::Normal, std::vector<Tile*>());

    _range.clear();
    _range_render->SetFusionRange(&_range);
    _motion->SetState("wait");
    _state->SetActive(false);
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->MatchRemoveDelay("Heal");
    return true;
}

void br::UnitHealComponent::Start(void) {
    _range.clear();
    _targets.clear();
    auto pos = ut::ToGridPos(super::_owner->GetPosition());
    auto stage = super::_owner->GetScene()->GetStage();

    std::vector<br::Tile*> cursor_range;
    // 回復範囲は隣接マス
    for (const auto& v : def::VDirection) {
        auto tile = stage->GetTile(pos.col + v.x, pos.row + v.y);
        if (auto unit = tile->GetOnUnit(); unit) {
            if (_state->GetTeam() == unit->GetTeam()) {
                cursor_range.push_back(tile);
                _targets.push_back(unit);
                _range.push_back(tile);
            } // if
        } // if
    } // for
    _range_render->SetFusionRange(&_range);
    super::_owner->GetScene()->GetCursor()->ChangeMode(br::Cursor::Mode::Limit, std::move(cursor_range));


    // 各イベント登録
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->MatchRemove("Move");
    sel->onDecide.Register("HealEnter", [&]() {
        return this->OnEnter();
    });
    sel->onEnd.Register("HealEnd", [&]() {
        return this->OnEnd();
    });
    sel->onCancel.Register("HealCancel", [&]() {
        return this->OnCancel();
    });
}

bool br::UnitHealComponent::CanHeal(br::Unit* target) {
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

bool br::UnitHealComponent::Heal(br::Unit& target) {
    target.Heal(10);
    return true;
}

br::Component* br::UnitHealComponent::Clone(void) {
    auto ptr = new br::UnitHealComponent(nullptr, _priority);
    return ptr;
}