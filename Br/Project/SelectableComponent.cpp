#include "SelectableComponent.h"

#include "Helper.h"
#include "Unit.h"


br::SelectableComponent::SelectableComponent(Actor* owner, int priority) :
    super(owner, priority),
    _cursor(nullptr),
    _is_select(false),
    _under_cursor(false),
    _is_decide(false) {
    super::_type = ComponentType::SelectableComponent;
}

br::SelectableComponent::~SelectableComponent() {
}

bool br::SelectableComponent::IsSelected(void) {
    return _is_select;
}

bool br::SelectableComponent::IsUnderCursor(void) {
    return _under_cursor;
}

bool br::SelectableComponent::IsDecide(void) {
    return _is_decide;
}

br::Cursor* br::SelectableComponent::GetCursor(void) {
    return this->_cursor;
}
Mof::CVector2 br::SelectableComponent::GetCursorPosition(void) {
    return this->_cursor->GetPosition();
}

bool br::SelectableComponent::Initialize(void) {
    _cursor = super::_owner->GetScene()->GetCursor();
    
    IUnitEvent* sel = dynamic_cast<br::IUnitEvent*>(super::_owner);
    sel->onEnd.Register("SelectEnd", [&]() {
        this->_is_select = false;
        this->_is_decide = false;
        this->_under_cursor = false;
        _cursor->SetSelectUnit(nullptr);
        return false;
    });
    sel->onCancel.Register("SelectCancel", [&]() {
        this->_is_select = false;
        this->_is_decide = false;
        this->_under_cursor = false;
        _cursor->SetSelectUnit(nullptr);
        return false;
    });
    return true;
}

bool br::SelectableComponent::Update(void) {
    auto pos = ut::ToGridPos(super::_owner->GetPosition());
    auto cursor = ut::ToGridPos(_cursor->GetPosition());

    _is_decide = false;
    if (this->IsSelected() && _cursor->IsEnter()) {
        _is_decide = true;
    } // if

    _under_cursor = false;
    if (pos == cursor) {
        _under_cursor = true;
    } // if

    if (_cursor->IsEnter() && _under_cursor) {
        // 選択可能なのはプレイヤーのみ
        auto check = dynamic_cast<br::Unit*>(super::_owner);
        if (check && check->GetTeam() == def::kPlayerTeam) {
            _is_select = true;
        } // if
    } // if
    if (_cursor->IsBack()) {
        _is_select = false;
    } // if
    return true;
}

bool br::SelectableComponent::Render(Mof::CVector2 scroll) {
    return true;
}

br::Component* br::SelectableComponent::Clone(void) {
    auto ptr = new br::SelectableComponent(nullptr, _priority);
    ptr->_cursor = this->_cursor;
    return ptr;
}