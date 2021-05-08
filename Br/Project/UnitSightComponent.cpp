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

   // // �e�C�x���g�o�^
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
    return false; // ����Component��OnCursor����������
}

bool br::UnitSightComponent::OnSelect(void) {
    return false; // ����Component��OnCursor����������
}

bool br::UnitSightComponent::OnEnter(void) {
    return false; // ����Component��OnCursor����������
}

bool br::UnitSightComponent::OnCancel(void) {
    return false; // ����Component��OnCursor����������
}

bool br::UnitSightComponent::OnEnd(void) {
    _range.clear();
    _range_render->SetSightRange(&_range);
    return false; // ����Component��OnCursor����������
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

    // ���F�\�͈͂̒�����ړ��\�͈͂ɑ�����n�_����菜��
    auto& r = _move->GetRange(); // �ړ��\�͈�
    for (auto p : r) {
        auto it = std::find_if(_range.begin(), _range.end(), [&p](br::RangeDataPointer elem) {
            return p->_tile == elem->_tile;
        });
        if (it != _range.end()) {
            _range.erase(it);
        } // if
    } // for
        // ���F�\�͈͂̒�����U���\�͈͂ɑ�����n�_����菜��
    auto& a = _attack->GetRange(); // �U���\�͈�
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