#include "UnitSightComponent.h"

#include "SelectableComponent.h"
#include "SightRange.h"
#include "Unit.h"
#include "Tile.h"
#include "Stage.h"


br::UnitSightComponent::UnitSightComponent(Actor* owner, int priority) :
    super(owner, priority),
    _sight_count(7),
    _range(),
    _range_render(nullptr),
    _move(nullptr),
    _attack(nullptr),
    _select(nullptr) {
}

br::UnitSightComponent::~UnitSightComponent() {
}

std::vector<br::RangeDataPointer>* br::UnitSightComponent::GetRange(void) {
    return &this->_range;
}

bool br::UnitSightComponent::Initialize(void) {
    _range_render = _owner->GetComponent<br::RangeRenderComponent>();
    _move = _owner->GetComponent<br::UnitMoveComponent>();
    _attack = _owner->GetComponent<br::UnitAttackComponent>();
    _select = _owner->GetComponent<br::SelectableComponent>();

   // // 各イベント登録
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->onEnd.Register("SightEnd", [&]() {        return this->OnEnd();    });
    return true;
}

bool br::UnitSightComponent::Update(void) {
    if (!_select->IsUnderCursor() && !_select->IsSelected()) {
        _range.clear();
    } // if
    return true;
}

bool br::UnitSightComponent::Render(Mof::CVector2 scroll) {
    return true;
}

bool br::UnitSightComponent::OnCursor(void) {
    return false; // 他のComponentのOnCursorも処理する
}

bool br::UnitSightComponent::OnSelect(void) {
    return false; // 他のComponentのOnCursorも処理する
}

bool br::UnitSightComponent::OnEnter(void) {
    return false; // 他のComponentのOnCursorも処理する
}

bool br::UnitSightComponent::OnCancel(void) {
    return false; // 他のComponentのOnCursorも処理する
}

bool br::UnitSightComponent::OnEnd(void) {
    _range.clear();
    _range_render->SetSightRange(&_range);
    return false; // 他のComponentのOnCursorも処理する
}

br::Component* br::UnitSightComponent::Clone(void) {
    auto ptr = new br::UnitSightComponent(nullptr, _priority);
    return ptr;
}

void br::UnitSightComponent::ReConputeRange(bool remove) {
    _range.clear();
    auto unit = dynamic_cast<br::Unit*>(super::_owner);
    auto stage = super::_owner->GetScene()->GetStage();
    auto tile = stage->GetTile(unit->GetGridPosition());

    br::SightRange ran;
    ran.ConputeRange(tile, _sight_count, _range);

    if (!remove) {
        return;
    } // if

    // 視認可能範囲の中から移動可能範囲に属する地点を取り除く
    auto& r = _move->GetRange(); // 移動可能範囲
    for (auto p : r) {
        auto it = std::find_if(_range.begin(), _range.end(), [&p](br::RangeDataPointer elem) {
            return p->_tile == elem->_tile;
        });
        if (it != _range.end()) {
            _range.erase(it);
        } // if
    } // for
        // 視認可能範囲の中から攻撃可能範囲に属する地点を取り除く
    auto& a = _attack->GetRange(); // 攻撃可能範囲
    for (auto p : a) {
        auto it = std::find_if(_range.begin(), _range.end(), [&p](br::RangeDataPointer elem) {
            return p == elem->_tile;
        });
        if (it != _range.end()) {
            _range.erase(it);
        } // if
    } // for

    _range_render->SetSightRange(&_range);
}